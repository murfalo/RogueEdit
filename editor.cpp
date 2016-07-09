#include "editor.h"

Editor::Editor()
{
    // Allocate memory
    this->characterValues = new std::unordered_map<std::string, QString>;
    this->inventory = new int[Items::NUM_INVENTORY_SLOTS];
    this->itemSettings = new ItemSettings[Items::NUM_INVENTORY_SLOTS];
    this->combatChips = new int[Items::NUM_COMBAT_CHIP_SLOTS];

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
    delete[] this->inventory;
    delete[] this->combatChips;
    delete[] this->itemSettings;
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

void Editor::loadCharacterValues()
{
    /* Loads the settings and stats of the character specified by ID. */
    std::string val;

    // Load and store the name and experience
    (*this->characterValues)[Strings::nameSpecifier] = QString::fromStdString(this->loadValue(this->currentID + Strings::nameSpecifier));
    (*this->characterValues)[Strings::characterExperienceSpecifier] = QString::fromStdString(this->loadValue(this->currentID + Strings::characterExperienceSpecifier));

    // Load comboBoxes
    for (int i = 0; i < Strings::CHARACTER_TAB_NUM_COMBOBOXES; i++)
    {
        val = this->loadValue(this->currentID + Strings::cComboBoxSpecifiers[i]);
        (*this->characterValues)[Strings::cComboBoxSpecifiers[i]] = QString::fromStdString(val);
    }

    // Load spinBoxes
    for (int i = 0; i < Strings::CHARACTER_TAB_NUM_SPINBOXES; i++)
        (*this->characterValues)[Strings::cSpinBoxSpecifiers[i]] = QString::fromStdString(this->loadValue(this->currentID + Strings::cSpinBoxSpecifiers[i]));
}

void Editor::loadCharacterItemBrowser()
{
    /* Loads the combat chips and inventory of the character specified by ID*/
    ItemSettings setting;
    std::string specifierPrefix;

    // Load the inventory of the character specified by ID into this->inventory */
    for (int i = 0; i < Items::NUM_INVENTORY_SLOTS; i++)
        this->inventory[i] = std::stoi(this->loadValue(this->currentID + std::to_string(i) + Strings::idSpecifier));

    // Load in item settings
    for (int i = 0; i < Items::NUM_INVENTORY_SLOTS; i++)
    {
        specifierPrefix = this->currentID + std::to_string(i);
        setting.exp = this->loadValue(specifierPrefix + Strings::itemExperienceSpecifier);
        setting.quantity = this->loadValue(specifierPrefix + Strings::itemQuantitySpecifier);
        setting.rarity = Strings::rarities[std::stoi(this->loadValue(specifierPrefix + Strings::itemRaritySpecifier))];
        this->itemSettings[i] = setting;
    }

    // Load the combat chips of the character specified by ID into this->combatChips */
    for (int i = 0; i < Items::NUM_COMBAT_CHIP_SLOTS; i++)
        this->combatChips[i] = std::stoi(this->loadValue(this->currentID + Strings::combatChipSpecifier + std::to_string(i)));
}
