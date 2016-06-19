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

void MainWindow::createCharacterActions(QString* characterNames)
{
    QAction* characterNameAction;
    // Loop and add an action for each non-empty item in characterNames
    for (int i = 0; i < characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
        characterNameAction = new QAction(characterNames[i]);
        this->findChild<QMenu*>("menuLoad_Character")->addAction(characterNameAction);
    }
}
