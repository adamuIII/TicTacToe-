#include "gameserver.h"


GameServer::GameServer(QWidget *parent)
{
    m_server = new QTcpServer();
    if(m_server->listen(QHostAddress::Any, 8080))
    {
        connect(this, &GameServer::newMessage, this, &GameServer::displayMessage);
        connect(m_server, &QTcpServer::newConnection, this, &GameServer::newConnection);

    }else{
        QMessageBox::critical(this, "QTcpServer",QString("Unable to starte the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }

}


GameServer::~GameServer()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();

    }

    m_server->close();
    m_server->deleteLater();

}

void GameServer::newConnection()
{
    while(m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());

}

void GameServer::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &GameServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &GameServer::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &GameServer::displayError);
    displayMessage(QString("INFO :: Client with socketID:%1 has just joined the room").arg(socket->socketDescriptor()));

}

void GameServer::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_4);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come ...").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);


    if(fileType=="message"){
        QString message = QString("%1 :: %2 ").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    }

}

void GameServer::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end())
    {
        displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        connection_set.remove(*it);
    }
    socket->deleteLater();
}


void GameServer::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
            break;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
            break;
    }
}


void GameServer::displayMessage(const QString& str)
{

}

