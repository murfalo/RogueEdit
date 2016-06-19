#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include "editor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // Create an option for each character under "Load Character" in the menu bar
    void MainWindow::createCharacterActions();
    ~MainWindow();

private slots:
    void on_actionCharacter_triggered();

    void on_actionEquipped_triggered();

    void on_actionInventory_triggered();

    void on_actionStorage_triggered();

    void on_actionCombat_Chips_triggered();

    void on_actionShip_Droids_triggered();

private:
    Editor e;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
