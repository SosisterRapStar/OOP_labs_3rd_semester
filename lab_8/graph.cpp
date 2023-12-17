#include "graph.h"
#include <QStringList>
#include <QString>
#include "matrix.h"

using namespace std;
Graph::Graph()
{
    matrix = new Matrix<int>(1,1);
    size = 1;
}

int* Graph::getNeighbours(int NodeNum){
    int *n = matrix->getRow(NodeNum);
    return n;
}

int Graph::getSize(){
    return size;
}


bool Graph::setGraphByString(QString fileContent){


    QStringList strMatrix = fileContent.split("|");
    QStringList strRow;
    size = strMatrix[0].split(" ").size();


    int** array = new int *[size];
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    if ((size) != strMatrix.size() - 1){
        return false;
    }



    for(int row = 0; row < size; row++){
        strRow = strMatrix[row].split(" ");
        if (strRow.size() != size){
            return false;
        }
        for(int column = 0; column < size; column++){
            bool ok;
            int digit = strRow[column].toInt(&ok, 10);
            if(!ok){
                return false;
            }
            array[row][column] = digit;
        }
    }

    matrix = new Matrix<int> (size, size);
    matrix->setMatrixByArray(array);

    for (int i = 0; i < size; i++){
        delete [] array[i];
    }
    delete [] array;
    return true;
}


