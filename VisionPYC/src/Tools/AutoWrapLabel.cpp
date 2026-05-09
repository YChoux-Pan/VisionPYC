#include "AutoWrapLabel.h"

AutoWrapLabel::AutoWrapLabel(QWidget* parent) : QLabel(parent)
{
	// 1. 基础设置
	this->setWordWrap(true);                   // 开启自动换行
	this->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 左对齐，垂直居中

	// 如果希望它像输入框一样有固定的最小高度
	this->setMinimumHeight(24);

	// 允许 Label 接收鼠标事件，否则 :hover 伪状态在禁用状态下可能不灵敏
	this->setAttribute(Qt::WA_Hover);

	// 2. 加载内置 QSS 样式
	// 注意：我们将原本的 QLineEdit 替换成了 AutoWrapLabel (类名选择器)
	this->setStyleSheet(R"(
        AutoWrapLabel {
            background-color: #1e1e1e;
            border: 1px solid #3a3a3a;
            color: #cccccc;
            padding: 2px 5px;
            border-radius: 0px;
        }

        /* 正常启用状态下的悬停 */
        AutoWrapLabel:enabled:hover {
            border: 1px solid #555555;
        }

        /* 默认/禁用状态 */
        AutoWrapLabel:disabled {
            background-color: #252526;
            border: 1px solid #555555;
            color: #888888;
        }

        /* 禁用状态下的悬停 */
        AutoWrapLabel:disabled:hover {
            border: 1px solid #3a3a3a;
            background-color: #282829;
        }

        /* 焦点/选中状态 (对于Label通常通过外部逻辑触发，这里预留) */
        AutoWrapLabel:focus {
            border: 1px solid #00CC66;
        }
    )");
}