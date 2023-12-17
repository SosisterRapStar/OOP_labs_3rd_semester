#ifndef GRAPH_H
#define GRAPH_H

#include "matrix.h"
#include <QString>

class Graph
{
public:
    Graph();
    bool setGraphByString(QString); // задание графа по строке
    int* getNeighbours(int nodeNum); // возвращает ребра для узла
    int getSize(); // возвращает размер графа
private:
    int size; // размер графа
    Matrix<int>* matrix;
};



#endif // GRAPH_H

