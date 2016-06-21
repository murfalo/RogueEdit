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
    // Create an option for each character under "Load Character" in the menu bar
    void MainWindow::createCharacterActions();
    ~MainWindow();

public slots:
    void characterNameActionHandler();

private:
    Editor* e;
    Ui::MainWindow *ui;
};
