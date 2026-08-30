#include "FlowWorker.h"
#include "FlowEngine.h"
#include "FlowModel.h"
#include "IFlowNode.h"
#include "INodeData.h"
#include <QElapsedTimer>
#include <QMutexLocker>
#include <QDebug>

FlowWorker::FlowWorker(FlowEngine* engine, QObject* parent)
	: QObject(parent), m_engine(engine)
{
}

void FlowWorker::runFlow()
{
	FlowModel* model = m_engine->model();

	// 1. 快照节点 ID（运行期间 GUI 不修改模型，锁内读取）
	QVector<QString> ids;
	{
		QMutexLocker locker(&model->mutex);
		const int count = model->nodeCountUnlocked();
		for (int i = 0; i < count; ++i)
			ids.push_back(model->nodeIdAtUnlocked(i));
	}

	if (ids.isEmpty()) {
		emit flowFinished(true);
		return;
	}

	// 2. 线性执行：节点 i 的输入端口 j ← 节点 i-1 的输出端口 j（类型匹配时）
	bool overallOk = true;
	QVector<std::shared_ptr<INodeData>> upstream;   // 上游节点的输出端口缓存

	for (int i = 0; i < ids.size(); ++i) {
		if (m_engine->isStopRequested()) {
			overallOk = false;
			break;
		}

		FlowNodeItem* item = nullptr;
		{
			QMutexLocker locker(&model->mutex);
			item = model->itemUnlocked(ids[i]);
		}
		if (!item) {
			overallOk = false;
			break;
		}

		emit nodeStarted(ids[i], i);

		// --- 数据搬运（线性自动串联）---
		const QVector<FlowPort> inputs = item->impl->inputPorts();
		for (int j = 0; j < inputs.size(); ++j) {
			if (j < upstream.size() && upstream[j])
				item->impl->setInput(j, upstream[j]);
			else
				item->impl->setInput(j, nullptr);
		}

		// --- 执行算法 ---
		QElapsedTimer timer;
		timer.start();
		const bool ok = item->impl->process();
		const qint64 ms = timer.elapsed();
		item->impl->setRunTime(ms);

		// --- 收集输出，供下游使用 ---
		upstream.clear();
		const QVector<FlowPort> outputs = item->impl->outputPorts();
		for (int j = 0; j < outputs.size(); ++j)
			upstream.push_back(item->impl->getOutput(j));

		emit nodeFinished(ids[i], i, ok, ms);

		if (!ok) {
			overallOk = false;
			break;
		}
	}

	emit flowFinished(overallOk);
}
