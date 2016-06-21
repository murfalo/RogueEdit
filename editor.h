#pragma once
#include <QtCore>
#include <QMenu>
#include <fstream>
#include "character.h"

class Editor
{
public:
    Editor();
    ~Editor();

    void restart();                                          // Return playerDataStream to the beginning of a file
    template<typename T> T loadValue(std::string specifier); // Loads a value from fstream
    void setValue(std::string specifier);                    // Sets a value in fstream
    QString* Editor::loadCharacterNames();                   // Load in characters from file

private:
    std::string playerDataLocation;    // Location of file
    std::fstream playerDataStream;     // Used to load and edit file
    int numCharacters = 0;             // Number of characters in file
    const int MAX_CHARACTERS = 6;      // Maximum number of characters allowed by RogueLands
    Character* characters;             // Array storing different character info
};
