#pragma once
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    this->_e = new Editor();
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
    if (characterNames->size() == 0) std::abort();           // Abort if no characters were found
    QToolBar* mainToolBar = this->findChild<QToolBar*>(Strings::toolbarObjectName);
    QMenu* characterMenu = new QMenu(Strings::characterMenuObjectName);

    // Add an action to characterMenu for each non-empty item in characterNames
    for (int i = 0; i <= characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
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
    QSpinBox* spinBox;

    // Update name
    QLineEdit* name = this->findChild<QLineEdit*>(Strings::nameEditObjectName);
    name->setText((*(this->_e->characterValues))[Strings::nameSpecifier]);

    // Update comboBoxes
    for (int i = 0; i < Strings::NUM_COMBOBOXES; i++)
    {
        comboBox = this->findChild<QComboBox*>(Strings::comboBoxObjectNames[i]);
        comboBox->setCurrentIndex(comboBox->findText((*this->_e->characterValues)[Strings::comboBoxSpecifiers[i]]));
    }

    // Update spinBoxes
    for (int i = 0; i < Strings::NUM_SPINBOXES; i++)
    {
        spinBox = this->findChild<QSpinBox*>(Strings::spinBoxObjectNames[i]);
        spinBox->setValue((*this->_e->characterValues)[Strings::spinBoxSpecifiers[i]].toInt());
    }
}

/*** Handlers ***/

void MainWindow::characterNameActionHandler()
{
    /* This function occurs when a player name is clicked in the loadCharacterDropdown.
     * Currently, it is very basic and functionality will be added in the future. */
    // Determine the name of the character that was clicked and set the editor's current ID accordingly
    QString characterID = QObject::sender()->objectName();

    // Locate loadCharacterDropdown and determine which characterNameAction is sender
    QToolButton* loadCharacterDropdown = this->findChild<QToolButton*>(Strings::loadCharacterDropdownObjectName);
    QAction* sender = this->findChild<QAction*>(characterID);
    loadCharacterDropdown->setDefaultAction(sender);

    /* Load the character's values and update the UI */
    this->_e->loadCharacterValues((sender->objectName()).toStdString());
    this->updateCharacterValues();

    // Enable interaction
    this->findChild<QTabWidget*>(Strings::navigationObjectName)->setDisabled(false);
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

    // Update the character name in the dropdown
    QAction* characterNameAction = this->findChild<QAction*>(QString::fromStdString(_e->currentID));
    std::string oldValue = characterNameAction->text().toStdString();
    characterNameAction->setText(this->findChild<QLineEdit*>(Strings::nameEditObjectName)->displayText());

    // Update the value in playerData
    this->_e->replaceValue(Strings::nameSpecifier, oldValue, newValue.toStdString());
}

void MainWindow::on_comboBoxDifficultyEdit_currentTextChanged(const QString& newDifficulty)
{
    /* Updates the difficulty stored in the editor member's playerData. */
    std::string oldValue = this->_e->loadValue(this->_e->currentID + Strings::difficultySpecifier);
    int newValue;

    // Find the index of the new string
    for (newValue = 0; newValue < Strings::NUM_DIFFICULTIES; newValue++)
        if (Strings::difficulties[newValue] == newDifficulty.toStdString()) break;
    this->_e->replaceValue(this->_e->currentID + Strings::difficultySpecifier, oldValue, std::to_string(newValue));
}

void MainWindow::on_comboBoxRaceEdit_currentTextChanged(const QString& newRace)
{
    /* Updates the difficulty stored in the editor member's playerData. */
    std::string oldValue = this->_e->loadValue(this->_e->currentID + Strings::raceSpecifier);
    int newValue;

    // Find the index of the new string
    for (newValue = 0; newValue < Strings::NUM_RACES; newValue++)
        if (Strings::races[newValue] == newRace.toStdString()) break;
    this->_e->replaceValue(this->_e->currentID + Strings::raceSpecifier, oldValue, std::to_string(newValue));
}

void MainWindow::on_comboBoxClassEdit_currentTextChanged(const QString& newClass)
{
    /* Updates the class stored in the editor member's playerData. */

    // Load the primary stats of the character
    std::string oldStat1 = this->_e->loadValue(this->_e->currentID + Strings::primaryStat1);
    std::string oldStat2 = this->_e->loadValue(this->_e->currentID + Strings::primaryStat2);
    std::string oldClass = this->_e->loadValue(this->_e->currentID + Strings::classSpecifier);

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
}
