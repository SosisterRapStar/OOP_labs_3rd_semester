#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

struct connectionParams  // структура описывающая параметры подключения
{
    QHostAddress recHost;
    quint16      recPort;
    QHostAddress sendHost;
    quint16      sendPort;
};




class Communicator : public QUdpSocket
{
    Q_OBJECT
    bool         ready;
    connectionParams  params;
public:
    Communicator(connectionParams&, QObject *parent = nullptr);
    bool isReady();

signals:
    void recieved(QByteArray);
public slots:
    void send(QByteArray);
    void recieve();
};

#endif // COMMUNICATOR_H
