#include "clientapp.h"
#include <QByteArray>

ClientApp::ClientApp(int argc, char *argv[])
    : QApplication(argc,argv)
{
    connectionParams pars = { QHostAddress("127.0.0.1"), 10001,
                             QHostAddress("127.0.0.1"), 10000};
    comm = new Communicator(pars, this);

    interface = new Interface();
    interface->show();

    connect(comm,SIGNAL(recieved(QByteArray)),this,
            SLOT(fromCommunicator(QByteArray)));
    connect(interface,SIGNAL(request(Message)),
            this,SLOT(toCommunicator(Message)));

}

void ClientApp::fromCommunicator(QByteArray msg)
{
    Message msgFromCom(msg);
    interface->answer(msgFromCom);
}

void ClientApp::toCommunicator(Message msg)
{
    comm->send(msg.toQByteArray());
}
