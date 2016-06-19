#ifndef EDITOR_H
#define EDITOR_H

#pragma once
#include <QtCore>
#include <QMenu>
#include <fstream>
#include "mainwindow.h"

class Editor
{
public:
    Editor();
    ~Editor();
    template<typename T> T Editor::loadValue(std::fstream &f);  // Loads a value from fstream
    void setValue(std::fstream &f); // Sets a value in fstream
    QString* Editor::loadCharacterNames(); // Load in characters from playerData.txt

private:
    std::string playerDataLocation; // Location of PlayerData.txt
    std::string tmpLocation; // Location to store temporary changes
    std::fstream playerDataStream; // Used to load and edit PlayerData.txt
    const int MAX_CHARACTERS = 6; // Maximum number of characters allowed by RogueLands
};

#endif // EDITOR_H
