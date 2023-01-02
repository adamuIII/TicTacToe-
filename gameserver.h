#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QSet>

namespace Ui {
class GameServer;
}



class GameServer : public QWidget
{
    Q_OBJECT


public:
    explicit GameServer(QWidget *parent = nullptr);
    ~GameServer();


signals:
    void newMessage(QString);
private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);
    void sendMessage(QTcpSocket* socket);
    void sendAttachment(QTcpSocket* socket, QString filePath);

//    void on_pushButton_sendMessage_clicked();
//    void on_pushButton_sendAttachment_clicked();

private:
    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

};

#endif // GAMESERVER_H
