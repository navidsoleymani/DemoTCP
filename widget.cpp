#include "widget.h"

int Widget::numberOfObjects = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    numberOfObjects++;
    toggleTcpServer = new QPushButton("Start Server");
    serverIP = new QLineEdit("127.0.0.1");
    serverPort = new QLineEdit("2323");

    toggleTcpClient = new QPushButton("Connect to Server");
    clientIP = new QLineEdit("127.0.0.1");
    clientPort = new QLineEdit("2323");

    sendData = new QPushButton("Send");
    dataInput = new QLineEdit("Hi!");
    tcpServer = new QTcpServer();
    tcpClient = new QTcpSocket();
    mSetupLayout();
    mSetupSignalSlots();
}

Widget::~Widget()
{
}

void Widget::toggleTcpServerClicked()
{
    if (tcpServer->isListening()){
        tcpServer->close();
        toggleTcpServer->setText("Start Server");
    }else{
        toggleTcpServer->setText("Stop Server");
        QHostAddress address;
        address.setAddress(serverIP->text());
        tcpServer->listen(address, static_cast<quint16>(serverPort->text().toInt()));
    }
    qDebug() << Q_FUNC_INFO << QString(": %1:%2").arg(serverIP->text()).arg(serverPort->text());
}

void Widget::toggleTcpClientClicked()
{
    if(tcpClient->isOpen()) {
        tcpClient->close();
        toggleTcpClient->setText("Connect to Server");
    } else {
        tcpClient->connectToHost(clientIP->text(), static_cast<quint16>(clientPort->text().toUInt()));
        toggleTcpClient->setText("Disconnect from Server");
    }
    // qDebug() << Q_FUNC_INFO << QString(": %1:%2").arg(clientIP->text()).arg(clientPort->text());
}

void Widget::sendDataClicked()
{
    if(!tcpClient->isOpen())
        return;
    tcpClient->write(dataInput->text().toUtf8());
}

void Widget::newConnection()
{
    qDebug() << "new connection";
    newTcpConnection = tcpServer->nextPendingConnection();
    connect(newTcpConnection, &QTcpSocket::readyRead, this, &Widget::readyReadSlot);
}

void Widget::readyReadSlot()
{
    QByteArray readed = newTcpConnection->readAll();
    qDebug()<< Q_FUNC_INFO << ": " << readed;
    newTcpConnection->write(readed.prepend("From ServeR: "));
}

void Widget::readyReadSlotClient()
{
    QByteArray readed = tcpClient->readAll();
    qDebug()<< Q_FUNC_INFO << ": " << readed;
}

void Widget::mSetupLayout()
{
    QHBoxLayout *serverLayout = new QHBoxLayout();
    QHBoxLayout *clientLayout = new QHBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();

    serverLayout->addWidget(serverIP, 4);
    serverLayout->addWidget(serverPort, 2);
    serverLayout->addWidget(toggleTcpServer, 2);

    clientLayout->addWidget(clientIP, 4);
    clientLayout->addWidget(clientPort, 2);
    clientLayout->addWidget(toggleTcpClient, 2);

    inputLayout->addWidget(dataInput, 5);
    inputLayout->addWidget(sendData, 1);
    QVBoxLayout *masterLayout=new QVBoxLayout();
    masterLayout->addLayout(serverLayout);
    masterLayout->addLayout(clientLayout);
    masterLayout->addLayout(inputLayout);
    this->setLayout(masterLayout);
}

void Widget::mSetupSignalSlots()
{
    connect(toggleTcpServer, &QPushButton::clicked,this, &Widget::toggleTcpServerClicked);
    connect(toggleTcpClient, &QPushButton::clicked,this, &Widget::toggleTcpClientClicked);
    connect(sendData, &QPushButton::clicked,this, &Widget::sendDataClicked);
    connect(tcpServer, &QTcpServer::newConnection, this, &Widget::newConnection);
    connect(tcpClient, &QTcpSocket::readyRead, this, &Widget::readyReadSlotClient);
}

