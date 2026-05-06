#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>
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
    MainWindow window;

   
   // loadStyleSheet(":/style.qss");


    window.showMaximized();
    window.show();
    return app.exec();
}
