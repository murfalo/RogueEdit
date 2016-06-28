#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QToolButton>
#include <algorithm>
#include "editor.h"
#include "strings.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void createCharacterActions();  // Create character actions in toolbar
    void updateCharacterValues();
    ~MainWindow();

private slots:
    void characterNameActionHandler();
    void saveCharacterHandler();
    void on_lineEditName_editingFinished();
    void on_comboBoxDifficultyEdit_currentTextChanged(const QString& arg1);
    void on_comboBoxRaceEdit_currentTextChanged(const QString& arg1);
    void on_comboBoxClassEdit_currentTextChanged(const QString &arg1);

private:
    Editor* _e;
    Ui::MainWindow *_ui;
};
#endif
