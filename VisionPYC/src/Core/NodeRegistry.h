#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <QString>

class IFlowNode;

// 算子注册表：新增算子只需在源文件末尾调用 REGISTER_NODE 宏一次，
// 旧代码零改动即可被左侧算子库自动发现。
class NodeRegistry {
public:
	struct Meta {
		QString typeKey;      // 注册键（拖拽 mimeData / 序列化用）
		QString category;     // 分类
		QString displayName;  // 显示名
		std::function<std::unique_ptr<IFlowNode>(const QString& typeKey)> creator;
	};

	static bool registerNode(const Meta& meta);
	static std::unique_ptr<IFlowNode> create(const QString& typeKey);
	static std::vector<Meta> all();
	static const Meta* find(const QString& typeKey);

private:
	static std::map<QString, Meta>& registry();
};

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

// 注册宏：约定算子构造函数签名形式为 explicit Class(QString typeKey)
#define REGISTER_NODE(Class, Key, Cat, Name)                                \
	static bool CONCAT(reg_, __LINE__) = NodeRegistry::registerNode({        \
		QStringLiteral(Key),                                                \
		QStringLiteral(Cat),                                                \
		QStringLiteral(Name),                                               \
		[](const QString& typeKey) -> std::unique_ptr<IFlowNode> {          \
			return std::make_unique<Class>(typeKey);                        \
		}                                                                   \
	});
