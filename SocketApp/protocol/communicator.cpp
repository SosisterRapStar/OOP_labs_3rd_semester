#include "communicator.h"

Communicator::Communicator(connectionParams& pars, QObject *parent) : QUdpSocket(parent)
{
    params = pars;
    ready = bind(params.recHost, params.recPort,
                 QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (ready) connect(this,SIGNAL(readyRead()),this,SLOT(recieve()));
}

bool Communicator::isReady()
{
    return ready;
}

void Communicator::send(QByteArray msg)     // отправка данных
{
    if (ready)
    {
        writeDatagram(msg, params.sendHost, params.sendPort);  // отправка данных на другой коммуникатор
        qDebug()<<"sended"<<msg;
    }
}

void Communicator::recieve()
{
    if (hasPendingDatagrams()) // проверка, если ли пришедшие данные
    {

        quint64 size = pendingDatagramSize(); // измерение размера пришедших данных
        QByteArray msg(size,'\0');
        readDatagram(msg.data(), size);  // считывание данных
        qDebug()<<"recieved"<<msg;
        emit recieved(msg); // вызов сигнала
    }
}
