#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(ui->page);
    ui->stackedWidget->setCurrentIndex(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::go_back()
{
    ui->stackedWidget->setCurrentWidget(0);
}

void MainWindow::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_settings_button_clicked()
{
    ui->stackedWidget->addWidget(ui->settings_screen);
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_quit_button_clicked()
{
    this->close();
}

