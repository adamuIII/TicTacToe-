#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    gameplay(new Gameplay)
{

    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);
    m_server = new QTcpServer();

    connect_socket = new QTcpSocket(this);



}

Game::~Game()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();

    }

    m_server->close();
    m_server->deleteLater();
    delete ui;
//    delete &connection_set;
}

void Game::on_start_server_button_clicked()
{
    if(m_server->listen(QHostAddress::Any, ui->port_nr_create_edit->text().toInt()))
    {
        connect(this, &Game::newMessage, this, &Game::displayMessage);
        connect(m_server, &QTcpServer::newConnection, this, &Game::newConnection);
        ui->server_status_list_event->append("Server has started, waiting for players to join");
        QMessageBox::information(this, "QTcpServer",QString("Server has started, waiting for players to join"));

    }else{
        ui->server_status_list_event->append("Unable to start server, change port or restart application and try again");
        QMessageBox::critical(this, "QTcpServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}

void Game::on_connect_to_server_button_clicked()
{
    connect(this, &Game::newMessage, this, &Game::displayMessage);
    connect(connect_socket, &QTcpSocket::readyRead, this, &Game::readSocket);
    connect(connect_socket, &QTcpSocket::disconnected, this, &Game::discardSocket);
    connect(connect_socket, &QAbstractSocket::errorOccurred, this, &Game::displayError);

    //connecting to server
    connect_socket->connectToHost(ui->ip_address_edit->text(),ui->port_nr_connect_edit->text().toInt());

    if(connect_socket->waitForConnected()){
        ui->server_status_list_event->append("Successfully joined server! The game has began");
        QMessageBox::information(this, "Tic Tac Toe Thread Controller",QString("Successfully joined server!"));
    }else{
        ui->server_status_list_event->append("Unable to join to server! Check the notification for more details");
        QMessageBox::critical(this, "Tic Tac Toe Thread Controller",QString("Unable to join the server: %1.").arg(connect_socket->errorString()));
    }

}



void Game::connected_to_server(){
    const QString newUsername = QInputDialog::getText(this, tr("Choose Username"),tr("Username"));
    if (newUsername.isEmpty()){
        //if the user clicked cancel or typed noting, we just disconnect from the server
        return connect_socket->disconnectFromHost();
    }

}

void Game::newConnection()
{
    while(m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());

}

void Game::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &Game::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &Game::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Game::displayError);
    displayMessage(QString("INFO :: Client with socketID: %1 has just joined the room").arg(socket->socketDescriptor()));

}

void Game::readSocket()
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

void Game::discardSocket()
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


void Game::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
        case QAbstractSocket::ProxyConnectionClosedError:
            return; // handled by disconnectedFromServer
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::critical(this, tr("Error"), tr("The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct."));
            break;
        case QAbstractSocket::ProxyConnectionRefusedError:
            QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
            break;
        case QAbstractSocket::ProxyNotFoundError:
            QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::critical(this, tr("Error"), tr("The host was not found. Please check the host name and port settings."));
            break;
        case QAbstractSocket::SocketAccessError:
            QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
            break;
        case QAbstractSocket::SocketResourceError:
            QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
            break;
        case QAbstractSocket::SocketTimeoutError:
            QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
            return;
        case QAbstractSocket::ProxyConnectionTimeoutError:
            QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
            break;
        case QAbstractSocket::NetworkError:
            QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
            break;
        case QAbstractSocket::UnknownSocketError:
            QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
            break;
        case QAbstractSocket::UnsupportedSocketOperationError:
            QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
            break;
        case QAbstractSocket::ProxyAuthenticationRequiredError:
            QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
            break;
        case QAbstractSocket::ProxyProtocolError:
            QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
            break;
        case QAbstractSocket::TemporaryError:
        case QAbstractSocket::OperationError:
            QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
            return;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
            break;
    }
}


void Game::displayMessage(const QString& str)
{
    ui->server_status_list_event->append(str);

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


void Game::on_back_btn1_clicked()
{
    emit HomeClicked();
}






