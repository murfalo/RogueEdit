#pragma once
#include <QtCore>
#include <QMenu>
#include <fstream>

class Editor
{
public:
    Editor();
    ~Editor();

    void restart(); // Return playerDataStream to the beginning of PlayerData.txt

    // Loads a value from fstream
    template<typename T> T Editor::loadValue(std::string specifier);

    void setValue(std::string specifier); // Sets a value in fstream
    QString* Editor::loadCharacterNames(); // Load in characters from playerData.txt

private:
    std::string playerDataLocation; // Location of PlayerData.txt
    std::string tmpLocation; // Location to store temporary changes
    std::fstream playerDataStream; // Used to load and edit PlayerData.txt
    const int MAX_CHARACTERS = 6; // Maximum number of characters allowed by RogueLands
};
