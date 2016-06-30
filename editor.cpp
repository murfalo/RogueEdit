#pragma once
#include "editor.h"

Editor::Editor()
{
    // Allocate memory for characterValues
    this->characterValues = new std::unordered_map<std::string, QString>;

    // Determine the username
    QString username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");

    // The location of the save file is different on Windows and Mac
    this->_playerDataLocation = Strings::playerDataPrefix + username.toStdString() + Strings::playerDataSuffix;
    this->_tmpDataLocation = Strings::playerDataPrefix + username.toStdString() + Strings::tmpDataSuffix;

    // Open a stream and load contents into memory
    std::ifstream playerDataStream(this->_playerDataLocation);
    if (playerDataStream.fail()) std::abort(); // TODO: Implement more graceful exception handling.
    this->_playerData = new std::string((std::istreambuf_iterator<char>(playerDataStream)),
                                       std::istreambuf_iterator<char>());

    // The space is semi-important, treasure it always
    *this->_playerData = " " + *this->_playerData;
    playerDataStream.close();
}

Editor::~Editor()
{
    delete this->characterValues;
    delete this->_playerData;
}

std::string Editor::loadValue(std::string specifier)
{
    /* Returns the value assigned to specifier. */
    std::string value = "";

    // Create a stringstream and set it's contents to playerData
    std::stringstream playerDataStream(*(this->_playerData));

    std::string word;

    // Search the file up to the specifier
    while (playerDataStream >> word)
        if (word == specifier) break;

    // Find the value
    while(playerDataStream >> word && word != Strings::terminator)
    {
        if (word != Strings::separator && word != Strings::intSpecifier && word != Strings::stringSpecifier)
            value = value.empty() ? word : value + " " + word;
    }

    return value;
}

void Editor::replaceValue(std::string specifier, std::string oldValue, std::string newValue)
{
    /* Replaces oldValue with newValue in this->playerData. */
    std::string oldString = " " + specifier + Strings::paddedSeperator + oldValue; // String to be replaced
    std::string newString = " " + specifier + Strings::paddedSeperator + newValue; // String to be inserted

    // Find the location at which to replace
    std::size_t position = this->_playerData->find(oldString);

    // Erase oldString at position from playerData
    this->_playerData->erase(position, oldString.length());

    // Insert newString into playerData at position
    this->_playerData->insert(position, newString);
}

void Editor::save()
{
    /* This function is called when the user clicks on Save Character. First it outputs
     * its Editor's playerData member to a temporary file.  If this was successful, it overwrites
     * the original PlayerPrefs.txt with the temporary file. */

    // First, output the edited playerData into tmpDataLocation
    std::ofstream saveStream(this->_tmpDataLocation);
    saveStream << this->_playerData->substr(1, this->_playerData->size() - 1);  // Ignore the extra space at the beginning
    if (saveStream.fail()) std::abort();
    saveStream.close();

    // Next, overwrite the original playerData and replace it with the new playerData
    std::remove(this->_playerDataLocation.c_str());
    std::rename(this->_tmpDataLocation.c_str(), (const char*) this->_playerDataLocation.c_str());
}

QString* Editor::loadCharacterNames()
{
    /* This function searches playerData.txt for all character names and adds seperators to
     * the "Load Player" section in the menu bar of w. Type can either be System.String or
     * System.Int32. */
    std::string characterName;
    std::string specifier;
    QString* characterNames = new QString[this->MAX_CHARACTERS];

    /* In PlayerData.txt, character names are specified by their number, ranging from
     * 0 to MAX_CHARACTERS, followed by "name" (e.g. "0name : Smurfalicious"). */
    for (int i = 0; i < this->MAX_CHARACTERS; i++)
    {
        // Load the name and store it in characterNames
        specifier = std::to_string(i) + Strings::nameSpecifier;
        characterName = this->loadValue(specifier);
        characterNames[i] = QString::fromStdString(characterName);
    }

    return characterNames;
}

void Editor::loadCharacterValues(std::string ID)
{
    /* Loads the settings and stats of the character specified by ID. */
    std::string val;
    this->currentID = ID;  // Update the current ID to the new ID

    // Load and store the name and experience
    (*characterValues)[Strings::nameSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::nameSpecifier));
    (*characterValues)[Strings::characterExperienceSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::characterExperienceSpecifier));

    // Load comboBoxes
    for (int i = 0; i < Strings::NUM_COMBOBOXES; i++)
    {
        val = this->loadValue(ID + Strings::comboBoxSpecifiers[i]);
        (*characterValues)[Strings::comboBoxSpecifiers[i]] = QString::fromStdString(val);
    }

    // Load spinBoxes
    for (int i = 0; i < Strings::NUM_SPINBOXES; i++)
        (*characterValues)[Strings::spinBoxSpecifiers[i]] = QString::fromStdString(this->loadValue(ID + Strings::spinBoxSpecifiers[i]));
}
