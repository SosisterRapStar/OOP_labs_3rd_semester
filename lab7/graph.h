#ifndef GRAPH_H
#define GRAPH_H

#include "matrix.h"
#include <QString>

class Graph
{
public:
    Graph(QString str);
    Matrix<int>* matrix;
    QString fileContent;
    int size;
    int* getNeighbours(int nodeNum);

};



#endif // GRAPH_H

