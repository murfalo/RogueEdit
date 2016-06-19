#include "mainwindow.h"
#include "editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Editor e;
    w.setWindowTitle("RogueEdit");
    w.show();

    return a.exec();
}
