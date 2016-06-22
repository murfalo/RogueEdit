#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "strings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->e = new Editor();
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->e;
}

void MainWindow::createCharacterActions()
{
    /* Creates a dropdown to load characters and an option to save changes on
     * the main tool bar. */
    QAction* characterNameAction;
    QString* characterNames = this->e->loadCharacterNames(); // Load character names from file
    if (characterNames->size() == 0) std::abort();           // Abort if no characters were found
    QToolBar* mainToolBar = this->findChild<QToolBar*>(Strings::toolbarObjectName);
    QMenu* characterMenu = new QMenu(Strings::characterMenuObjectName);

    // Add an action to characterMenu for each non-empty item in characterNames
    for (int i = 0; i < characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
        characterNameAction = new QAction(characterNames[i], this);
        characterNameAction->setObjectName(characterNames[i]);

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

    // TODO: this->e.loadCharacter(characterName)
}

void MainWindow::saveCharacterHandler()
{
    this->e->save();
}
