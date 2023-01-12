#include "tictactoeserver.h"
#include "tictactoemainwindow.h"
#include <QTcpSocket>

TicTacToeServer::TicTacToeServer(TicTacToeMainWindow* pHelloServer,QObject *parent): QTcpServer{parent}
{
    m_pMainWindow=pHelloServer;
}

void TicTacToeServer::incomingConnection(qintptr socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    m_pMainWindow->DisplayStatusMessage("New client from: "+client->peerAddress().toString());

   connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
   connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}
void TicTacToeServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    QString line;


    while(client->canReadLine())
    {
        line = QString::fromUtf8(client->readLine()).trimmed();
        m_pMainWindow->DisplayRemotePCMessage(line);

    }
}

void TicTacToeServer::disconnected(){
    QTcpSocket *client = (QTcpSocket*)sender();
     m_pMainWindow->DisplayStatusMessage("Client disconnected: "+client->peerAddress().toString());
    clients.remove(client);
}
