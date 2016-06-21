#pragma once
#include <QtCore>
#include <QMenu>
#include <fstream>
#include <sstream>
#include "strings.h"

// Define an item as an object with an ID and a name
struct Item { int ID; std::string name; };

class Editor
{
public:
    Editor();
    ~Editor();

    template<typename T> T loadValue(std::string specifier); // Loads a value from file
    void Editor::replaceValue(std::string specifier,         // Replaces a value in file
                              std::string oldValue,
                              std::string newValue);
    QString* Editor::loadCharacterNames();                   // Load in characters from file

private:
    std::string playerDataLocation;    // Location of file
    std::string* playerData;           // Pointer to contents of file in memory
    int numCharacters = 0;             // Number of characters in file
    const int MAX_CHARACTERS = 6;      // Maximum number of characters allowed by RogueLands
};
