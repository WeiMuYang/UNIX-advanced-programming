#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <valgrind/memcheck.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int *p = new int[20];
    *p = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
