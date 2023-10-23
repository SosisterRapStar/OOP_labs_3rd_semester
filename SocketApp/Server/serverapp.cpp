#include "serverapp.h"
#include "matrix.h"
#include "message.h"

ServerApp::ServerApp(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    connectionParams pars = { QHostAddress("127.0.0.1"), 10000,
                             QHostAddress("127.0.0.1"), 10001};
    comm = new Communicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void ServerApp::recieve(QByteArray message)
{
    Message msg(message);
    switch(msg.method){
    case RANK:
    {

        number** matrixArr = parseMatrixBody(msg.body);
        Matrix* matrix = new Matrix(size);
        matrix->setMatrixByArray(matrixArr);
        int rank = matrix->getRank();
        delete matrix;
        for(int i = 0; i < size; i++){
            delete [] matrixArr[i];
        }
        delete [] matrixArr;
        QString responseString = "RANK =" + QString().setNum(rank);
        Message responseMsg(RESPONSE, ANSWER, responseString);
        comm->send(responseMsg.toQByteArray());
        break;
    }
    case DETERMINANT:
    {
        number** matrixArr = parseMatrixBody(msg.body);
        Matrix* matrix = new Matrix(size);
        matrix->setMatrixByArray(matrixArr);
        number det = matrix->getDet();
        delete matrix;
        for(int i = 0; i < size; i++){
            delete [] matrixArr[i];
        }
        delete [] matrixArr;
        QString s("Determinant = ");
        s<<det;
        Message responseMsg(RESPONSE, ANSWER, s);
        comm->send(responseMsg.toQByteArray());
        break;
    }

    }


}






number** ServerApp::parseMatrixBody(QString body){
    QStringList list = body.split(MATRIX_SEPARATOR);
    size = list[0].toInt();
    matrixStr = new QString* [size];
    for(int row =0; row < size; row++){
        QStringList rowList = list[row + 1].split(" ");
        matrixStr[row] = new QString[size];
        for(int col = 0; col < size; col++){
            matrixStr[row][col] = rowList[col];
        }
    }
    number** valueArray = new number* [size];
    for(int i = 0; i < size; i++){
        valueArray[i] = new number [size];
    }
    for (int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            valueArray[row][col] = parseFromQString(matrixStr[row][col]);
        }
    }
    return valueArray;
}




number ServerApp::parseFromQString(QString str){
    bool haveRationalView = false;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == RATIONAL_SEPARATOR){
            haveRationalView = true;
            break;
        }
    }
    if(haveRationalView){
        QStringList strList = str.split(RATIONAL_SEPARATOR);
        int up = strList[0].toInt();
        int down = strList[1].toInt();
        number rational(up, down);
        return rational;
    }
    number rational(str.toInt());
    return rational;
}



