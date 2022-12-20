#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
//    ui->stackedWidget->addWidget(ui->page);
//    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->insertWidget(1, &GameChoose);
    ui->stackedWidget->insertWidget(2, &Settings);

    connect(&Settings, SIGNAL(HomeClicked()), this, SLOT(moveHome()));
}

Application::~Application()
{
    delete ui;
}

void Application::on_play_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Application::on_options_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Application::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Application::on_quit_button_clicked()
{
    this->close();
}
