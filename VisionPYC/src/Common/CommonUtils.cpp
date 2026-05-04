#include "CommonUtils.h"
#include <QUuid>

QString CommonUtils::generateUUID() {
	// 使用 Qt 内置的 QUuid 生成唯一标识符
	// toString() 会生成类似 "{123e4567-e89b-12d3-a456-426614174000}" 的字符串
	// 我们通常去掉大括号方便管理
	return QUuid::createUuid().toString(QUuid::WithoutBraces);
}