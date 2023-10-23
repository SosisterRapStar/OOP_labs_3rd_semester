#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>
#include <QCoreApplication>
#include "number.h"

#include "communicator.h"

class ServerApp : public QCoreApplication
{
    Q_OBJECT

    Communicator *comm;
    QString** matrixStr;
    number parseFromQString(QString str);
    int size;

public:
    number** parseMatrixBody(QString body);
    ServerApp(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif
