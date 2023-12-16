#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "resources.h"
#include "Game.h"

class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui:: MainWindow ui;
    Game* game;
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
