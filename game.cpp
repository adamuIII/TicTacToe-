#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    gameplay(new Gameplay)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);


}

Game::~Game()
{
    delete ui;
}
void Game::updateScreen(){
    if(!ui->pushButton_00->text().isEmpty() &&ui->pushButton_00->text()==ui->pushButton_01->text() && ui->pushButton_00->text()==ui->pushButton_02->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_10->text().isEmpty() && ui->pushButton_10->text()==ui->pushButton_11->text() && ui->pushButton_10->text()==ui->pushButton_12->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_20->text().isEmpty() &&ui->pushButton_20->text()==ui->pushButton_21->text() && ui->pushButton_20->text()==ui->pushButton_22->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_00->text().isEmpty() &&ui->pushButton_00->text()==ui->pushButton_10->text() && ui->pushButton_00->text()==ui->pushButton_20->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_01->text().isEmpty() &&ui->pushButton_01->text()==ui->pushButton_11->text() && ui->pushButton_00->text()==ui->pushButton_21->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_02->text().isEmpty() &&ui->pushButton_02->text()==ui->pushButton_12->text() && ui->pushButton_02->text()==ui->pushButton_22->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_00->text().isEmpty() &&ui->pushButton_00->text()==ui->pushButton_11->text() && ui->pushButton_00->text()==ui->pushButton_22->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(!ui->pushButton_20->text().isEmpty() &&ui->pushButton_20->text()==ui->pushButton_11->text() && ui->pushButton_20->text()==ui->pushButton_02->text()){
        ui->stackedWidget->setCurrentIndex(1);
    }


}

void Game::on_back_button_game_choose_clicked()
{
    emit HomeClicked();
}


void Game::on_pushButton_00_clicked()
{

    updateScreen();
    ui->pushButton_00->setText(gameplay->getWhosTurn());

}


void Game::on_pushButton_01_clicked()
{
    gameplay->put(0,1);
    ui->pushButton_01->setText(gameplay->getWhosTurn());
    updateScreen();

}


void Game::on_pushButton_02_clicked()
{
    gameplay->put(0,2);
    ui->pushButton_02->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_pushButton_10_clicked()
{
        gameplay->put(1,0);
        ui->pushButton_10->setText(gameplay->getWhosTurn());
        updateScreen();
}


void Game::on_pushButton_11_clicked()
{
    gameplay->put(1,1);
    ui->pushButton_11->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_pushButton_12_clicked()
{
    gameplay->put(1,2);
    ui->pushButton_12->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_pushButton_20_clicked()
{
    gameplay->put(2,0);
    ui->pushButton_20->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_pushButton_21_clicked()
{
    gameplay->put(2,1);
    ui->pushButton_21->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_pushButton_22_clicked()
{
    gameplay->put(2,2);
    ui->pushButton_22->setText(gameplay->getWhosTurn());
    updateScreen();
}


void Game::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void Game::on_start_server_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Game::on_connect_to_server_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

