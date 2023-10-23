#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include "message.h"
#include "interface.h"
#include "communicator.h"

class ClientApp : public QApplication
{
    Q_OBJECT

    Communicator *comm;
    Interface    *interface;

public:
    ClientApp(int, char**);

public slots:
    void fromCommunicator(QByteArray);
    void toCommunicator(Message);

};

#endif // APPLICATION_H
