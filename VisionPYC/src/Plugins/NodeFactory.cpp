#include "NodeFactory.h"
#include "ImageFilterNode.h" // 包含所有具体的插件头文件

BaseAlgorithmNode* NodeFactory::createNode(const QString& typeName) {
	if (typeName == "GaussianBlur") {
		return new ImageFilterNode();
	}
	// else if (typeName == "Camera") { return new CameraNode(); }

	return nullptr;
}