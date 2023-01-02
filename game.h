#ifndef GAME_H
#define GAME_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QSet>
#include <QInputDialog>
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
    void makeMove(int row, int column, int player);

    void newConnection();
    void on_back_button_clicked();


    void appendToSocketList(QTcpSocket* socket);
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);

//    void sendMessage(QTcpSocket* socket);


    void on_start_server_button_clicked();


    void on_back_btn1_clicked();

    void on_connect_to_server_button_clicked();

    void connected_to_server();

private:
    Ui::Game *ui;
    Gameplay *gameplay; 
    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;
    void updateScreen();
    QTcpSocket* connect_socket;

signals:
    void HomeClicked();
    void newMessage(QString);
};

#endif // GAME_H
