#ifndef TICTACTOESERVER_H
#define TICTACTOESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "tictactoemainwindow.h"

class TicTacToeMainWindow;

class TicTacToeServer : public QTcpServer
{
    Q_OBJECT

public:
    TicTacToeServer(TicTacToeMainWindow* pHelloServer,QObject *parent=0);

    explicit TicTacToeServer(QObject *parent = nullptr);

    TicTacToeMainWindow* m_pMainWindow;

    TicTacToeServer* m_pBoxServer;



private:

    QSet<QTcpSocket*> clients;

protected:

    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;

private slots:

    void readyRead();

    void disconnected();

};

#endif // TICTACTOESERVER_H
