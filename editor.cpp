#pragma once
#include "editor.h"

Editor::Editor()
{
    // Determine the username
    QString username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");

    // The location of the save file is different on Windows and Mac
    this->playerDataLocation = Strings::playerDataPrefix + username.toStdString() + Strings::playerDataSuffix;
    this->tmpDataLocation = Strings::playerDataPrefix + username.toStdString() + Strings::tmpDataSuffix;

    // Open a stream and load contents into memory
    std::ifstream playerDataStream(this->playerDataLocation);
    if (playerDataStream.fail()) std::abort(); // TODO: Implement more graceful exception handling.
    this->playerData = new std::string((std::istreambuf_iterator<char>(playerDataStream)),
                                       std::istreambuf_iterator<char>());
    playerDataStream.close();
}

Editor::~Editor()
{
    delete this->playerData;
}

template<typename T> T Editor::loadValue(std::string specifier)
{
    /* Returns the value assigned to specifier. */
    T value;
    // Create a stringstream and set it's contents to playerData
    std::stringstream playerDataStream;
    playerDataStream.str(*(this->playerData));

    std::string word;

    // Search the file up to the specifier
    while (playerDataStream >> word)
        if (word == specifier) break;

    // Find the value
    while(playerDataStream >> word && word != Strings::terminator)
    {
        if (word != Strings::separator && word != Strings::intSpecifier && word != Strings::stringSpecifier)
            value = word;
    }

    return value;
}

void Editor::replaceValue(std::string specifier, std::string oldValue, std::string newValue)
{
    /* Replaces oldValue with newValue in this->playerData. */
    std::string oldString = specifier + Strings::paddedSeperator + oldValue; // String to be replaced
    std::string newString = specifier + Strings::paddedSeperator + newValue; // String to be inserted

    // Find the location at which to replace
    std::size_t position = this->playerData->find(oldString);

    // Erase oldString at position from playerData
    this->playerData->erase(position, oldString.length());

    // Insert newString into playerData at position
    this->playerData->insert(position, newString);
}

void Editor::save()
{
    /* This function is called when the user clicks on Save Character. First it outputs
     * its Editor's playerData member to a temporary file.  If this was successful, it overwrites
     * the original PlayerPrefs.txt with the temporary file. */

    // First, output the edited playerData into tmpDataLocation
    std::ofstream saveStream(this->tmpDataLocation);
    saveStream << *(this->playerData);
    if (saveStream.fail()) std::abort();
    saveStream.close();

    // Next, overwrite the original playerData and replace it with the new playerData
    std::remove(this->playerDataLocation.c_str());
    std::rename(this->tmpDataLocation.c_str(), (const char*) this->playerDataLocation.c_str());
}

QString* Editor::loadCharacterNames()
{
    /* This function searches playerData.txt for all character names and adds seperators to
     * the "Load Player" section in the menu bar of w. Type can either be System.String or
     * System.Int32. */
    std::string characterName;
    std::string specifier;
    QString* characterNames = new QString[this->MAX_CHARACTERS];
    int i;

    /* In PlayerData.txt, character names are specified by their number, ranging from
     * 0 to MAX_CHARACTERS, followed by "name" (e.g. "0name : Smurfalicious"). */
    for (i = 0; i < this->MAX_CHARACTERS; i++)
    {
        // Load the name and store it in characterNames
        specifier = std::to_string(i) + Strings::nameSpecifier;
        characterName = loadValue<std::string>(specifier);
        characterNames[i] = QString::fromStdString(characterName);
    }

    this->numCharacters = i; // Update numCharacters to store the number of characters loaded

    return characterNames;
}
