
#pragma once
#include "BaseAlgorithmNode.h"

class _3DProcessNode : public BaseAlgorithmNode {
public:
	explicit _3DProcessNode(QString subType);

	QString category() const override { return "3D检测"; }
	QString modelName() const override { return m_subType; }

	void process() override;
	QWidget* getConfigWidget() override;

private:
	QString m_subType;
	QWidget* m_cachedWidget = nullptr;
};