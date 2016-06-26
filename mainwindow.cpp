#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    for (int i = 0; i < characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
        characterNameAction = new QAction(characterNames[i], this);
        // Set the object name to the ID of the character
        characterNameAction->setObjectName(QString::fromStdString(std::to_string(i)));

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

/*** Handlers ***/

void MainWindow::characterNameActionHandler()
{
    /* This function occurs when a player name is clicked in the loadCharacterDropdown.
     * Currently, it is very basic and functionality will be added in the future. */
    // Determine the name of the character that was clicked
    QString characterName = QObject::sender()->objectName();

    // Locate loadCharacterDropdown and determine which characterNameAction is sender
    QToolButton* loadCharacterDropdown = this->findChild<QToolButton*>(Strings::loadCharacterDropdownObjectName);
    QAction* sender = this->findChild<QAction*>(characterName);
    loadCharacterDropdown->setDefaultAction(sender);

    /* Load the character's values and update the UI */
    // First load in the values
    std::unordered_map<std::string, QString>* characterValues = this->_e->loadCharacterValues((sender->objectName()).toStdString());

    // Update settings
    QLineEdit* name = this->findChild<QLineEdit*>(Strings::nameEditObjectName);
    name->setText((*characterValues)[Strings::nameSpecifier]);
    QComboBox* difficulty = this->findChild<QComboBox*>(Strings::difficultyEditObjectName);
    difficulty->setCurrentIndex(difficulty->findText((*characterValues)[Strings::difficultySpecifier]));
    QComboBox* race = this->findChild<QComboBox*>(Strings::raceEditObjectName);
    race->setCurrentIndex(race->findText((*characterValues)[Strings::raceSpecifier]));
    QComboBox* statClass = this->findChild<QComboBox*>(Strings::classEditObjectName);
    statClass->setCurrentIndex(statClass->findText((*characterValues)[Strings::classSpecifier]));
    QComboBox* variant = this->findChild<QComboBox*>(Strings::variantEditObjectName);
    variant->setCurrentIndex(variant->findText((*characterValues)[Strings::variantSpecifier]));
    QComboBox* uniform = this->findChild<QComboBox*>(Strings::uniformEditObjectName);
    uniform->setCurrentIndex(uniform->findText((*characterValues)[Strings::uniformSpecifier]));
    QComboBox* augment = this->findChild<QComboBox*>(Strings::augmentEditObjectName);
    augment->setCurrentIndex(augment->findText((*characterValues)[Strings::augmentSpecifier]));

    // Update stats
    QSpinBox* vitality = this->findChild<QSpinBox*>(Strings::vitalityEditObjectName);
    vitality->setValue((*characterValues)[Strings::vitalitySpecifier].toInt());
    QSpinBox* dexterity = this->findChild<QSpinBox*>(Strings::dexterityEditObjectName);
    dexterity->setValue((*characterValues)[Strings::dexteritySpecifier].toInt());
    QSpinBox* magic = this->findChild<QSpinBox*>(Strings::magicEditObjectName);
    magic->setValue((*characterValues)[Strings::magicSpecifier].toInt());
    QSpinBox* strength = this->findChild<QSpinBox*>(Strings::strengthEditObjectName);
    strength->setValue((*characterValues)[Strings::strengthSpecifier].toInt());
    QSpinBox* tech = this->findChild<QSpinBox*>(Strings::techEditObjectName);
    tech->setValue((*characterValues)[Strings::techSpecifier].toInt());
    QSpinBox* faith = this->findChild<QSpinBox*>(Strings::faithEditObjectName);
    faith->setValue((*characterValues)[Strings::faithSpecifier].toInt());
    QSpinBox* characterLevel = this->findChild<QSpinBox*>(Strings::characterLevelObjectName);
    characterLevel->setValue((*characterValues)[Strings::characterLevelSpecifier].toInt());
    QSpinBox* allegianceLevel = this->findChild<QSpinBox*>(Strings::allegianceLevelObjectName);
    allegianceLevel->setValue((*characterValues)[Strings::allegianceLevelSpecifier].toInt());

    // Enable interaction
    this->findChild<QTabWidget*>(Strings::navigationObjectName)->setDisabled(false);
}

void MainWindow::saveCharacterHandler()
{
    /* Saves information to file when "Save Character" is clicked. */
    this->_e->save();
}
