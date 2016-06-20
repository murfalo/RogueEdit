#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createCharacterActions()
{
    QAction* characterNameAction;
    QString* characterNames = this->e.loadCharacterNames(); // Load character names from file
    QToolBar* mainToolBar = this->findChild<QToolBar*>("mainToolBar");

    // Create a new dropdown menu
    QMenu* characterMenu = new QMenu;

    // Add an action to characterMenu for each non-empty item in characterNames
    for (int i = 0; i < characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
        characterNameAction = new QAction(characterNames[i], this);
        characterMenu->addAction(characterNameAction);
    }

    // Create a dropdown and assign characterMenu to it
    QToolButton* loadCharacterDropdown = new QToolButton;
    loadCharacterDropdown->setText("Load Character");
    loadCharacterDropdown->setToolButtonStyle(Qt::ToolButtonTextOnly);
    loadCharacterDropdown->setPopupMode(QToolButton::MenuButtonPopup);
    loadCharacterDropdown->setMenu(characterMenu);

    // Create a save character action
    QAction* saveCharacterAction = new QAction("Save Character", this);

    // Add the dropdown and a save character action to mainToolBar
    mainToolBar->addWidget(loadCharacterDropdown);
    mainToolBar->addAction(saveCharacterAction);
}
