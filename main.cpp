#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QSplitter>
int main(int argc, char **argv)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
