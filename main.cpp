#include "mainwindow.h"
#include "editor.h"
#include "strings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Add character names from PlayerData.txt to menu bar under "Load Character"
    w.createCharacterActions();

    w.setWindowTitle(Strings::appTitle);
    w.show();

    return a.exec();
}
