#pragma once
#include "mainwindow.h"
#include "editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Add character names from PlayerData.txt to menu bar under "Load Character"
    w.createCharacterActions();

    w.setWindowTitle("RogueEdit");
    w.show();

    return a.exec();
}
