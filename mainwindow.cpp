#pragma once
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    this->_e = new Editor();

    // Forcefully make item browser pretty
    this->findChild<QTreeWidget*>(Strings::itemBrowserObjectName)->setColumnWidth(2,30);
    this->findChild<QTreeWidget*>(Strings::itemBrowserObjectName)->setColumnHidden(2,true);

    this->_itemCompleter = new QCompleter(Items::itemList, this);
    this->_itemCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    this->_combatChipCompleter = new QCompleter(Items::combatChipsList, this);
    this->_combatChipCompleter->setCaseSensitivity(Qt::CaseInsensitive);
}

MainWindow::~MainWindow()
{
    delete this->_ui;
    delete this->_e;
}

void MainWindow::createCharacterActions()
{
    /* Creates a dropdown to load characters and an option to save changes on
     * the main tool bar. */
    QAction* characterNameAction;
    QString* characterNames = this->_e->loadCharacterNames(); // Load character names from file
    QToolBar* mainToolBar = this->findChild<QToolBar*>(Strings::toolbarObjectName);
    QMenu* characterMenu = new QMenu(Strings::characterMenuObjectName);

    // Add an action to characterMenu for each non-empty item in characterNames
    for (int i = 0; i < this->_e->MAX_CHARACTERS; i++)
    {
        if (characterNames[i].isEmpty()) continue;
        characterNameAction = new QAction(characterNames[i], this);

        // Set the object name to the ID of the character
        characterNameAction->setObjectName(QString::number(i));
        characterNameAction->setToolTip("Load " + characterNames[i]);

        // Connect characterNameAction to a handler
        QObject::connect(characterNameAction, SIGNAL(triggered()), this, SLOT(characterNameActionHandler()));

        characterMenu->addAction(characterNameAction);
    }

    // Kludge in a dropdown inside the toolbar
    QToolButton* loadCharacterDropdown = new QToolButton;
    loadCharacterDropdown->setObjectName(Strings::loadCharacterDropdownObjectName);
    loadCharacterDropdown->setToolButtonStyle(Qt::ToolButtonTextOnly);
    loadCharacterDropdown->setPopupMode(QToolButton::MenuButtonPopup);
    loadCharacterDropdown->setMenu(characterMenu);
    loadCharacterDropdown->setDefaultAction(characterMenu->actions()[0]);

    // Create a save character action and connect a handler
    QAction* saveCharacterAction = new QAction(Strings::saveCharacterActionText, this);
    QObject::connect(saveCharacterAction, SIGNAL(triggered()), this, SLOT(saveCharacterHandler()));

    // Add the dropdown and a save character action to mainToolBar
    mainToolBar->addWidget(loadCharacterDropdown);
    mainToolBar->addAction(saveCharacterAction);
}

void MainWindow::updateCharacterValues()
{
    QComboBox* comboBox;
    QString comboText;
    QSpinBox* spinBox;

    // Update name
    QLineEdit* name = this->findChild<QLineEdit*>(Strings::nameEditObjectName);
    name->setText((*(this->_e->characterValues))[Strings::nameSpecifier]);

    // Update comboBoxes
    for (int i = 0; i < Strings::CHARACTER_TAB_NUM_COMBOBOXES; i++)
    {
        comboBox = this->findChild<QComboBox*>(Strings::cComboBoxObjectNames[i]);
        comboText = QString::fromStdString(Strings::cComboBoxArrays[i][(*this->_e->characterValues)[Strings::cComboBoxSpecifiers[i]].toInt()]);
        comboBox->setCurrentIndex(comboBox->findText(comboText));
    }

    // Update spinBoxes
    for (int i = 0; i < Strings::CHARACTER_TAB_NUM_SPINBOXES; i++)
    {
        spinBox = this->findChild<QSpinBox*>(Strings::cSpinBoxObjectNames[i]);
        spinBox->setValue((*this->_e->characterValues)[Strings::cSpinBoxSpecifiers[i]].toInt());
    }
}

void MainWindow::updateCharacterItemBrowser()
{
    /* Updates the Item Browser with inventory and combat chips */
    // Identify the item browser
    QTreeWidget* itemBrowser = this->findChild<QTreeWidget*>(Strings::itemBrowserObjectName);

    // Load values!
    // Currently only loads the first six combat chips
    this->loadTopLevelChildren(itemBrowser, Strings::itemBrowserCombatChipsIndex, 0, Items::HOTBAR_END, Strings::combatChipSpecifier);
    this->loadTopLevelChildren(itemBrowser, Strings::itemBrowserDronesIndex, Items::DRONE_BEGIN, Items::DRONE_END);
    this->loadTopLevelChildren(itemBrowser, Strings::itemBrowserEquippedIndex, Items::EQUIPPED_BEGIN, Items::EQUIPPED_END);
    this->loadTopLevelChildren(itemBrowser, Strings::itemBrowserInventoryIndex, Items::HOTBAR_BEGIN, Items::INVENTORY_STORAGE_END);

    // Update the LineEdit if an item is already selected
    if (itemBrowser->currentItem())
        this->findChild<QLineEdit*>(Strings::itemNameEditObjectName)->setText(itemBrowser->currentItem()->text(0));
}

void MainWindow::loadTopLevelChildren(QTreeWidget* itemBrowser,
                                      int topLevelIndex,
                                      const int beginIndex,
                                      const int endIndex,
                                      std::string type)
{
    /* Loads the children of topLevelIndex in itemBrowser from beginIndex to endIndex.
     * Input type as "" for most cases. */
    QTreeWidgetItem* topLevelItem = itemBrowser->topLevelItem(topLevelIndex);

    // Stuff changes slightly when we're working on combat chips rather than standard items
    int* itemIDArray = (type == Strings::combatChipSpecifier) ? &this->_e->combatChips[0] : &this->_e->inventory[0];
    const std::string* itemNamesArray = (type == Strings::combatChipSpecifier) ? &Items::combatChips[0] : &Items::items[0];

    QTreeWidgetItem* child;
    std::string value;

    for (int i = beginIndex; i < endIndex; i++)
    {
        // Load the ID and the corresponding item string
        value = itemNamesArray[itemIDArray[i]];
        if (value.empty()) value = "None";

        // Update the text in the item browser
        child = topLevelItem->child((beginIndex == 0) ? i : i % beginIndex); // Avoid accidentally doing modulo 0
        child->setText(0, QString::fromStdString(value));
    }
}

void MainWindow::simpleComboBoxChangedHandler(const QString& newValue,
                                              const std::string specifier,
                                              const std::string* arrayBasePointer,
                                              const int arraySize)
{
    /* Updates the value specified by specifier stored in the editor member's playerData. New value is the value
     * to update to, arrayBasePointer is the pointer to the first element of the array of values.  Array size is
     * the number of elements in the aforementioned array. */
    std::string oldValue = (*this->_e->characterValues)[specifier].toStdString();

    // Find the index of the new string
    int newIndex;
    for (newIndex = 0; newIndex < arraySize; newIndex++)
        if (arrayBasePointer[newIndex] == newValue.toStdString()) break;

    // Update the editor
    this->_e->replaceValue(this->_e->currentID + specifier, oldValue, std::to_string(newIndex));

    (*this->_e->characterValues)[specifier] = QString::number(newIndex);
}

void MainWindow::simpleSpinBoxChangedHandler(const QString& newValue, const std::string specifier)
{
    /* Updates the value specified by specifier to newValue. */
    std::string oldValue = (*this->_e->characterValues)[specifier].toStdString();
    this->_e->replaceValue(this->_e->currentID + specifier, oldValue, newValue.toStdString());
    (*this->_e->characterValues)[specifier] = newValue;
}

/*** Handlers ***/

void MainWindow::characterNameActionHandler()
{
    /* This function occurs when a player name is clicked in the loadCharacterDropdown.
     * Currently, it is very basic and functionality will be added in the future. */
    // Temporarily disable interaction
    this->setEnabled(false);

    // Determine the name of the character that was clicked and set the editor's current ID accordingly
    QString characterID = QObject::sender()->objectName();

    // Locate loadCharacterDropdown and determine which characterNameAction is sender
    QToolButton* loadCharacterDropdown = this->findChild<QToolButton*>(Strings::loadCharacterDropdownObjectName);
    QAction* sender = this->findChild<QAction*>(characterID);
    loadCharacterDropdown->setDefaultAction(sender);

    /* Load the character's values and update the UI */
    this->_e->currentID = (sender->objectName()).toStdString();
    this->_e->loadCharacterValues();
    this->_e->loadCharacterItemBrowser();
    this->updateCharacterValues();
    this->updateCharacterItemBrowser();

    // Enable interaction
    this->setEnabled(true);
    this->findChild<QTabWidget*>(Strings::navigationObjectName)->setEnabled(true);
}

void MainWindow::saveCharacterHandler()
{
    /* Saves information to file when "Save Character" is clicked. */
    this->_e->save();
}

void MainWindow::on_lineEditName_editingFinished()
{
    /* Updates the name stored in the editor member's playerData. */
    QString newValue = this->findChild<QLineEdit*>(Strings::nameEditObjectName)->displayText();

    // Grab the old value and update _e->characterValues
    std::string oldValue = (*this->_e->characterValues)[Strings::nameSpecifier].toStdString();
    (*this->_e->characterValues)[Strings::nameSpecifier] = newValue;

    // Update the character name in the dropdown
    QAction* characterNameAction = this->findChild<QAction*>(QString::fromStdString(_e->currentID));
    characterNameAction->setText(this->findChild<QLineEdit*>(Strings::nameEditObjectName)->displayText());

    // Update the value in playerData
    this->_e->replaceValue(this->_e->currentID + Strings::nameSpecifier, oldValue, newValue.toStdString());
}

void MainWindow::on_comboBoxDifficultyEdit_currentTextChanged(const QString& newDifficulty)
{
    this->simpleComboBoxChangedHandler(newDifficulty, Strings::difficultySpecifier, &Strings::difficulties[0], Strings::NUM_DIFFICULTIES);
}

void MainWindow::on_comboBoxRaceEdit_currentTextChanged(const QString& newRace)
{
    this->simpleComboBoxChangedHandler(newRace, Strings::raceSpecifier, &Strings::races[0], Strings::NUM_RACES);
}

void MainWindow::on_comboBoxVariantEdit_currentIndexChanged(const QString& newVariant)
{
    this->simpleComboBoxChangedHandler(newVariant, Strings::variantSpecifier, &Strings::variants[0], Strings::NUM_VARIANTS);
}

void MainWindow::on_comboBoxUniformEdit_currentIndexChanged(const QString& newUniform)
{
    this->simpleComboBoxChangedHandler(newUniform, Strings::uniformSpecifier, &Strings::uniforms[0], Strings::NUM_UNIFORMS);
}

void MainWindow::on_comboBoxAugmentEdit_currentIndexChanged(const QString& newAugment)
{
    this->simpleComboBoxChangedHandler(newAugment, Strings::augmentSpecifier, &Strings::augments[0], Strings::NUM_AUGMENTS);
}

void MainWindow::on_comboBoxAllegianceEdit_currentIndexChanged(const QString& newAllegiance)
{
    this->simpleComboBoxChangedHandler(newAllegiance, Strings::allegianceSpecifier, &Strings::allegiances[0], Strings::NUM_ALLEGIANCES);
}

void MainWindow::on_comboBoxClassEdit_currentTextChanged(const QString& newClass)
{
    /* Updates the class stored in the editor member's playerData. */

    // Load the primary stats of the character
    std::string oldStat1 = this->_e->loadValue(this->_e->currentID + Strings::primaryStat1);
    std::string oldStat2 = this->_e->loadValue(this->_e->currentID + Strings::primaryStat2);
    std::string oldClass = (*this->_e->characterValues)[Strings::classSpecifier].toStdString();

    // Find the index of the new string
    int newValue;
    for (newValue = 0; newValue < Strings::NUM_CLASSES; newValue++)
        if (Strings::classes[newValue] == newClass.toStdString()) break;

    // Find new primary stat indices
    int* indices = new int[2];
    for (indices[0] = 0; indices[0] < Strings::NUM_STATS; indices[0]++)
        for (indices[1] = 0; indices[1] < Strings::NUM_STATS; indices[1]++)
            if (Strings::statCombos[indices[0]][indices[1]] == newClass.toStdString()) goto done;

done:
    // Replace the old primary stats with the new ones
    this->_e->replaceValue(this->_e->currentID + Strings::primaryStat1, oldStat1, std::to_string(indices[0]));
    this->_e->replaceValue(this->_e->currentID + Strings::primaryStat2, oldStat2, std::to_string(indices[1]));
    this->_e->replaceValue(this->_e->currentID + Strings::classSpecifier, oldClass, std::to_string(newValue));
    (*this->_e->characterValues)[Strings::classSpecifier] = QString::number(newValue);

}

void MainWindow::on_spinBoxVitVal_valueChanged(const QString& newVit)
{
    this->simpleSpinBoxChangedHandler(newVit, Strings::vitalitySpecifier);
}

void MainWindow::on_spinBoxDexVal_valueChanged(const QString& newDex)
{
    this->simpleSpinBoxChangedHandler(newDex, Strings::dexteritySpecifier);
}

void MainWindow::on_spinBoxMagVal_valueChanged(const QString& newMag)
{
    this->simpleSpinBoxChangedHandler(newMag, Strings::magicSpecifier);
}

void MainWindow::on_spinBoxStrVal_valueChanged(const QString& newStr)
{
    this->simpleSpinBoxChangedHandler(newStr, Strings::strengthSpecifier);
}

void MainWindow::on_spinBoxTecVal_valueChanged(const QString& newTec)
{
    this->simpleSpinBoxChangedHandler(newTec, Strings::techSpecifier);
}

void MainWindow::on_spinBoxFaiVal_valueChanged(const QString& newFai)
{
    this->simpleSpinBoxChangedHandler(newFai, Strings::faithSpecifier);
}

void MainWindow::on_spinBoxLevelVal_valueChanged(const QString& newCharacterLevel)
{
    this->simpleSpinBoxChangedHandler(newCharacterLevel, Strings::characterLevelSpecifier);

    // Calculate experience
    int level = newCharacterLevel.toInt();
    int requiredExperience = 36;
    int previousExperienceGain = 26;

    // Don't ask me why the experience formula is so odd
    if (level == 1) requiredExperience = 0;
    else if (level == 2) requiredExperience = 10;
    else
    {
        for (int i = 3; i < level; i++)
        {
            previousExperienceGain += 3 * i;
            requiredExperience += previousExperienceGain;
        }
    }

    this->simpleSpinBoxChangedHandler(QString::number(requiredExperience), Strings::characterExperienceSpecifier);
}

void MainWindow::on_spinBoxAllegianceLevelVal_valueChanged(const QString& newAllegianceLevel)
{
    this->simpleSpinBoxChangedHandler(newAllegianceLevel, Strings::allegianceLevelSpecifier);
}

void MainWindow::on_treeWidgetItemBrowser_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    /* Handles on-click for the item browser! */
    QGroupBox* itemEditor = this->findChild<QGroupBox*>(Strings::itemEditorObjectName);

    // Disable editor if user clicks on a top-level item
    if (current->parent() == NULL) {
        itemEditor->setEnabled(false);
        return;
    }

    // Otherwise enable the editor!
    itemEditor->setEnabled(true);

    // Load in relevant fields
    QLineEdit* itemNameEdit = itemEditor->findChild<QLineEdit*>(Strings::itemNameEditObjectName);
    QSpinBox* spinBox;
    QComboBox* comboBox;

    // Check if the item under the combat chips top-level item (i.e. is the item a combat chip?)
    if (current->parent()->text(0) == Strings::itemBrowserCombatChipsTitle)
    {
        itemNameEdit->setCompleter(this->_combatChipCompleter);

        // Combat chips do not have any editable attributes besides name/ID
        // Disable comboBoxes
        for (int i = 0; i < Strings::ITEM_TAB_NUM_COMBOBOXES; i++)
        {
            comboBox = itemEditor->findChild<QComboBox*>(Strings::iComboBoxObjectNames[i]);
            comboBox->setEnabled(false);
        }
        // Disable spinBoxes
        for (int i = 0; i < Strings::ITEM_TAB_NUM_SPINBOXES; i++)
        {
            spinBox = itemEditor->findChild<QSpinBox*>(Strings::iSpinBoxObjectNames[i]);
            spinBox->setEnabled(false);
        }
    }
    else // The item is a normal item with editable attributes
    {
        itemNameEdit->setCompleter(this->_itemCompleter);
        // Enable comboBoxes
        for (int i = 0; i < Strings::ITEM_TAB_NUM_COMBOBOXES; i++)
        {
            comboBox = itemEditor->findChild<QComboBox*>(Strings::iComboBoxObjectNames[i]);
            comboBox->setEnabled(true);
        }
        // Enable spinBoxes
        for (int i = 0; i < Strings::ITEM_TAB_NUM_SPINBOXES; i++)
        {
            spinBox = itemEditor->findChild<QSpinBox*>(Strings::iSpinBoxObjectNames[i]);
            spinBox->setEnabled(true);
        }
    }
    // Update the Line Edit's text
    itemNameEdit->setText(current->text(0));
}

/* Item name edit handler */
void MainWindow::on_lineEditItemName_editingFinished()
{
    // Determine whether a combat chip or normal item is being edited
    QTreeWidgetItem* current = this->findChild<QTreeWidget*>(Strings::itemBrowserObjectName)->currentItem();
    QString parentName = current->parent()->text(0);

    // Determine which structures to use based on whether or not item is a combat chip
    bool isCombatChip = parentName == Strings::itemBrowserCombatChipsTitle;
    int* itemIDArray = isCombatChip ? &this->_e->combatChips[0] : &this->_e->inventory[0];
    const QString* itemNameArray = isCombatChip ? &Items::combatChipsList[0] : &Items::itemList[0];
    const int maxSize = isCombatChip ? Items::LARGEST_COMBAT_CHIP : Items::LARGEST_ID;

    // Determine the new value
    int newValue = NULL;
    QString newName = this->findChild<QLineEdit*>(Strings::itemNameEditObjectName)->displayText();
    for (int i = 0; i < maxSize; i++)
    {
        if (itemNameArray[i] == newName)
        {
            newValue = i;
            break;
        }
    }

    if (newValue == NULL) return;  // Stop if the new name does not correspond to an item

    // Determine the old value
    std::string index = current->text(2).toStdString();
    std::string oldValue = std::to_string(itemIDArray[std::stoi(index)]);  // Item indexes are stored in column 2

    // Determine the specifier
    std::string specifier = isCombatChip ? this->_e->currentID + Strings::combatChipSpecifier + index:
                                           this->_e->currentID + index + Strings::idSpecifier;

    // Update the user interface and itemIDArray
    current->setText(0, newName);
    itemIDArray[std::stoi(index)] = newValue;


    // Replace the old value with the new value
    this->_e->replaceValue(specifier, oldValue, std::to_string(newValue));
}
