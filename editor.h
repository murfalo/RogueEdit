#ifndef EDITOR_H
#define EDITOR_H

#pragma once
#include <QtCore>
#include <QMenu>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <regex>
#include "strings.h"

// Define an item as an object with an ID and a name
struct Item { int ID; std::string name; };

class Editor
{
public:
    Editor();
    ~Editor();

    std::string loadValue(std::string specifier); // Loads a value from file
    void replaceValue(std::string specifier,                 // Replaces a value in file
                              std::string oldValue,
                              std::string newValue);
    void save();                               // Save playerData to file
    QString* loadCharacterNames();             // Load in characters from file
    void loadCharacterValues(std::string ID);  // Load character settings and stats

    const int MAX_CHARACTERS = 6;                               // Maximum number of characters allowed by RogueLands
    const int NUM_CHARACTER_VALUES = 20;                        // Number of settings and stats per character
    std::string currentID;                                      // ID of the current character
    std::unordered_map<std::string, QString>* characterValues;  // Maps a specifier string to the character's associated value in QString form

private:
    std::string _playerDataLocation;    // Location of file
    std::string _tmpDataLocation;       // Location to store temporary data when saving
    std::string* _playerData;           // Pointer to contents of file in memory
};

#endif
