#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QObject>
#include <QCoreApplication>
#include <QList>
#include <message.h>
#include "communicator.h"
#include "squarematrix.h"

class ServerApp : public QCoreApplication
{
    Q_OBJECT

    Communicator *comm;
    QString** matrixStr;
    int size;

    void setMatrixStrArr(QStringList list);
    template<class number>
    QString manageResponse(QStringList list, int method);

public:
    ServerApp(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};


template<class number>
QString ServerApp::manageResponse(QStringList list, int method){
    QString ans;
    setMatrixStrArr(list);
    number** matrixArr = new number* [size];

    for(int i = 0; i < size; i++){
        matrixArr[i] = new number [size];
    }
    for (int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            QString str = matrixStr[row][col];
            matrixArr[row][col] = str;
        }
    }

    SquareMatrix<number>* matrix = new SquareMatrix<number>(size);
    matrix->setMatrixByArray(matrixArr);

    for(int i = 0; i < size; i++){
        delete [] matrixArr[i];
    }
    delete [] matrixArr;

    for(int i = 0; i < size; i++){
        delete [] matrixStr[i];
    }
    delete [] matrixStr;

    switch(method){
        case RANK:
            {
                int rank = matrix->getRank();
                ans = "RANK =" + QString().setNum(rank);
                break;
            }
        case DETERMINANT:
            {
                number det = matrix->getDet();
                ans = "Determinant = ";
                ans << det;
                break;
            }
    }
    delete matrix;
    return ans;
}

#endif
