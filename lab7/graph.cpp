#include "graph.h"
#include <QStringList>
#include <QString>
#include "matrix.h"

using namespace std;
Graph::Graph(QString str)
{
    this->fileContent = str;


    QStringList strMatrix = fileContent.split("|");
    QStringList strRow;
    size = strMatrix[0].split(" ").size();



    int** array = new int *[size];
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    if ((size * size) != strMatrix.size()){
        // ошибка
    }

    for(int row = 0; row < size; row++){
        strRow = strMatrix[row].split(" ");
        if (strRow.size() != size){
            // ошибка
        }
        for(int column = 0; column < size; column++){
            bool ok;
            int digit = strRow[column].toInt(&ok, 10);
            if(!ok){
                // ошибка
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
}

int* Graph::getNeighbours(int NodeNum){
    int *n = matrix->getRow(NodeNum);
    return n;
}



