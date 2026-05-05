#pragma once
#include <QString>
#include <memory>


class BaseAlgorithmNode;

class NodeFactory {
public:
	// 根据字符串名称创建对应的节点实例
	static BaseAlgorithmNode* createNode(const QString& typeName);
};