#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "Global.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <QAbstractNativeEventFilter>
#include <QWindow>
// 定义全局系统样式过滤器
class SystemStyleFilter : public QObject {
public:
	bool eventFilter(QObject* obj, QEvent* event) override {
		// 监听窗口显示事件
		if (event->type() == QEvent::Show) {
			QWidget* widget = qobject_cast<QWidget*>(obj);

			// 确保是顶级窗口（如 MainWindow 或 Dialog），排除普通子控件
			if (widget && widget->isWindow()) {
				HWND hwnd = (HWND)widget->winId();
				if (hwnd) {
					// 定义你的墨绿色
					COLORREF moLvColor = RGB(0, 77, 64);
					COLORREF frameColor = RGB(0, 120, 40);

					// 1. 设置边框颜色为墨绿 (DWMWA_BORDER_COLOR = 34)
					DwmSetWindowAttribute(hwnd, 34, &frameColor, sizeof(frameColor));

					// 2. 设置标题栏（顶部状态栏区域）颜色为墨绿 (DWMWA_CAPTION_COLOR = 35)
					// 这会让整个窗口顶部由原来的黑色/白色变为墨绿色
					DwmSetWindowAttribute(hwnd, 35, &moLvColor, sizeof(moLvColor));

					// 3. 设置标题文字颜色 (DWMWA_TEXT_COLOR = 36)
					// 既然背景是墨绿，文字建议设为白色，清晰度更高
					COLORREF textColor = RGB(255, 255, 255);
					DwmSetWindowAttribute(hwnd, 36, &textColor, sizeof(textColor));

					// 4. 保持强制直角 (DWMWA_WINDOW_CORNER_PREFERENCE = 33)
					int cornerPreference = 1;
					DwmSetWindowAttribute(hwnd, 33, &cornerPreference, sizeof(cornerPreference));
				}
			}
		}
		return QObject::eventFilter(obj, event);
	}
};

void loadStyleSheet(const QString& path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        //读取QSS
        QString styleSheet = QLatin1String(file.readAll());
        //应用到程序
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	// 安装全局过滤器
	SystemStyleFilter filter;
	app.installEventFilter(&filter);

    MainWindow window;

    //获取全局路径
    QString exePath = QCoreApplication::applicationDirPath();
    g_pathexe = exePath.toUtf8().toStdString();

	

    window.showMaximized();

    window.show();
    return app.exec();
}
