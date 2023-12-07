#ifndef GRAPH_H
#define GRAPH_H

#include "matrix.h"
#include <QString>

class Graph
{
public:
    Graph();
    bool setGraphByString(QString);
    int* getNeighbours(int nodeNum);
    int size;
private:

    Matrix<int>* matrix;
};



#endif // GRAPH_H

