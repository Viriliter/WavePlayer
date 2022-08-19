#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyle("fusion");
    a.setWindowIcon(QIcon("./resources/logo.png"));
    a.setApplicationName("WavePlayer");
    a.setApplicationVersion("0.1");

    w.show();
    return a.exec();
}
