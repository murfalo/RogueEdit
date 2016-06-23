#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QToolButton>
#include "editor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void MainWindow::createCharacterActions();  // Create character actions in toolbar
    ~MainWindow();

public slots:
    void characterNameActionHandler();
    void saveCharacterHandler();

private:
    Editor* e;
    Ui::MainWindow *ui;
};
#endif
