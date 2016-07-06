#include "mainwindow.h"
#include "editor.h"
#include "strings.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Add character names from PlayerData.txt to menu bar under "Load Character"
    w.createCharacterActions();

    qDebug() << QStyleFactory::keys();
    w.show();

    a.setStyle(Strings::appStyle);
    return a.exec();
}
