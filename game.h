#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "gameplay.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_pushButton_00_clicked();

    void on_pushButton_01_clicked();

    void on_pushButton_02_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_21_clicked();

private:
    Ui::Game *ui;
    Gameplay *gameplay;

    void updateScreen();
};

#endif // GAME_H
