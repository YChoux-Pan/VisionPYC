#include "NodeFactory.h"
#include "ImageFilterNode.h"
#include "_3DProcessNode.h"
BaseAlgorithmNode* NodeFactory::createNode(const QString& typeName) {
	QStringList imageList = { "图像预处理", "ROI设置" ,"采集图像"};
	if (imageList.contains(typeName)) {
		return new ImageFilterNode(typeName);
	}

	// 3D 大类列表
	QStringList threeDList = { "高度检测", "平面度检测" };
	if (threeDList.contains(typeName)) {
		return new _3DProcessNode(typeName);
	}
	

	return nullptr;
}