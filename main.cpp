#include "mainwindow.h"
#include "editor.h"
#include "strings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Add character names from PlayerData.txt to menu bar under "Load Character"
    w.createCharacterActions();
    w.setWindowTitle(Strings::appTitle);

    a.setStyle(Strings::appStyle);
    a.setStyleSheet(Strings::appStyleSheet);

    w.show();
    return a.exec();
}
