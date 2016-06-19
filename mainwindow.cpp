#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
    QString* characterNames = this->e.loadCharacterNames();

    // Loop and add an action for each non-empty item in characterNames
    for (int i = 0; i < characterNames->size(); i++)
    {
        if (characterNames[i].isEmpty()) break;
        characterNameAction = new QAction(characterNames[i]);
        this->findChild<QMenu*>("menuLoad_Character")->addAction(characterNameAction);
    }
}

void MainWindow::on_actionCharacter_triggered() {}

void MainWindow::on_actionEquipped_triggered() {}

void MainWindow::on_actionInventory_triggered() {}

void MainWindow::on_actionStorage_triggered() {}

void MainWindow::on_actionCombat_Chips_triggered() {}

void MainWindow::on_actionShip_Droids_triggered() {}
