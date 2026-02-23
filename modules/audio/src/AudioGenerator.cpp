#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::Dots_array()
{
    for(int i = 0 ; i < count ; i++)
    {
        Y = cos(3*X)*sin(X) - cos(0.5*X)*sin(2*X);
        dots[i] = Y;
        X+=0.1  ;
    }
}
