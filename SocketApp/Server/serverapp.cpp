#include "serverapp.h"
#include "complex.h"
#include"real.h"
#include "rational.h"
#include "message.h"

ServerApp::ServerApp(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    connectionParams pars = { QHostAddress("127.0.0.1"), 10000,
                             QHostAddress("127.0.0.1"), 10001};
    comm = new Communicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}


void ServerApp::setMatrixStrArr(QStringList list){
    matrixStr = new QString* [size];
    for(int row =0; row < size; row++){
        QStringList rowList = list[row + 1].split(" ");
        matrixStr[row] = new QString[size];
        for(int col = 0; col < size; col++){
            matrixStr[row][col] = rowList[col];
        }
    }
}


void ServerApp::recieve(QByteArray message)
{
    Message msg(message);
    QStringList list = msg.body.split(MATRIX_SEPARATOR);
    size = list[0].toInt();
    QString ans;
    switch(msg.type){
    case REAL:
    {

        ans = manageResponse<real>(list, msg.method);
        break;
    }
    case COMPLEX:
    {
        ans = manageResponse<complex>(list, msg.method);
        break;
    }
    case RATIONAL:
        {
        ans = manageResponse<Rational>(list, msg.method);
        break;


        }
    }

    Message responseMsg(RESPONSE, ANSWER, msg.type, ans);
    comm->send(responseMsg.toQByteArray());


}





























