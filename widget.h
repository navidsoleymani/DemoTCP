#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QtDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static int numberOfObjects;
public slots:
    void toggleTcpServerClicked();
    void toggleTcpClientClicked();
    void sendDataClicked();
    void newConnection();
    void readyReadSlot();
    void readyReadSlotClient();
private:
    void mSetupLayout();
    void mSetupSignalSlots();
    QPushButton *toggleTcpServer;// = new QPushButton("Start Server");
    QLineEdit *serverIP;// = new QLineEdit();
    QLineEdit *serverPort;// = new QLineEdit();

    QPushButton *toggleTcpClient ;//= new QPushButton("Connect to Server");
    QLineEdit *clientIP ;//= new QLineEdit();
    QLineEdit *clientPort ;//= new QLineEdit();

    QPushButton *sendData;
    QLineEdit *dataInput;
    QTcpServer *tcpServer;
    QTcpSocket *tcpClient;
    QTcpSocket *newTcpConnection;
};
#endif // WIDGET_H
