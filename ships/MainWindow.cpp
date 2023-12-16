#include "MainWindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    game(new Game)
{   
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
    delete game;
}

void MainWindow::on_pushButton_clicked() {

    game->count = 1;
    game->show();

    close();
}
void MainWindow::on_pushButton_2_clicked() {
    
    game->count = 2;
    game->show();

    close();
}