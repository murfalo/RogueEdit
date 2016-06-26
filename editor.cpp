#pragma once
#include "editor.h"

Editor::Editor()
{
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
    playerDataStream.close();
}

Editor::~Editor()
{
    delete this->_playerData;
}

std::string Editor::loadValue(std::string specifier)
{
    /* Returns the value assigned to specifier. */
    std::string value;

    // Create a stringstream and set it's contents to playerData
    std::stringstream playerDataStream;
    playerDataStream.str(*(this->_playerData));

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
    saveStream << *(this->_playerData);
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
        characterName = loadValue(specifier);
        characterNames[i] = QString::fromStdString(characterName);
    }

    return characterNames;
}

std::unordered_map<std::string, QString>* Editor::loadCharacterValues(std::string ID)
{
    /* Loads the settings and stats of the character specified by ID. */
    std::unordered_map<std::string, QString>* characterValues = new std::unordered_map<std::string, QString>;
    std::string val;

    /*** Settings ***/
    (*characterValues)[Strings::nameSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::nameSpecifier));
    val = this->loadValue(ID + Strings::difficultySpecifier);
    (*characterValues)[Strings::difficultySpecifier] = QString::fromStdString(Strings::difficulties[std::stoi(val)]);
    val = this->loadValue(ID + Strings::raceSpecifier);
    (*characterValues)[Strings::raceSpecifier] = QString::fromStdString(Strings::races[std::stoi(val)]);
    val = this->loadValue(ID + Strings::variantSpecifier);
    (*characterValues)[Strings::variantSpecifier] = QString::fromStdString(Strings::variants[std::stoi(val)]);
    val = this->loadValue(ID + Strings::uniformSpecifier);
    (*characterValues)[Strings::uniformSpecifier] = QString::fromStdString(Strings::uniforms[std::stoi(val)]);
    val = this->loadValue(ID + Strings::augmentSpecifier);
    (*characterValues)[Strings::augmentSpecifier] = QString::fromStdString(Strings::augments[std::stoi(val)]);

    /*** Stats ***/
    (*characterValues)[Strings::vitalitySpecifier] = QString::fromStdString(this->loadValue(ID + Strings::vitalitySpecifier));
    (*characterValues)[Strings::dexteritySpecifier] = QString::fromStdString(this->loadValue(ID + Strings::dexteritySpecifier));
    (*characterValues)[Strings::magicSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::magicSpecifier));
    (*characterValues)[Strings::strengthSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::strengthSpecifier));
    (*characterValues)[Strings::techSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::techSpecifier));
    (*characterValues)[Strings::faithSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::faithSpecifier));
    (*characterValues)[Strings::characterLevelSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::characterLevelSpecifier));
    (*characterValues)[Strings::allegianceLevelSpecifier] = QString::fromStdString(this->loadValue(ID + Strings::allegianceLevelSpecifier));


    /* Class is a little more complicated because of how it is stored.  First, determine the primary stats
     * of the character.  Then, use these values to access the array defined in strings.h to determine
     * the name of the character's class and store it in characterValues as a QString. */
    int i, j;
    i = std::stoi(loadValue(ID + Strings::primaryStat1));
    j = std::stoi(loadValue(ID + Strings::primaryStat2));
    (*characterValues)[Strings::classSpecifier] = QString::fromStdString(Strings::classes[i][j]);

    // TODO: Health, stamina, mana, max health, max mana, max stamina

    return characterValues;
}
