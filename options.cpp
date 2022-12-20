#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{
    delete ui;
}




void Options::on_back_button_clicked()
{
    emit HomeClicked();
}

