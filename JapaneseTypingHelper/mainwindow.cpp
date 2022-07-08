#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindowClass())
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}
