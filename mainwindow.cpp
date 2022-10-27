#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(&options);
    ui->stackedWidget->addWidget(&game);
    connect(&options, SIGNAL(BackClicked()), this, SLOT(moveHome()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
    qApp->exit();
}

void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

