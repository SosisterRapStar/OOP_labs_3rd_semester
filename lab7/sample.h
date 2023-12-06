#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include"graph.h"
class TSample
{
    int gSize;
    Graph* graph;
    QPainter* p;
    qreal centerX;
    qreal centerY;
public:
    TSample(Graph*);
    void draw(QPainter*,QRect);
    void drawConnections(QPointF, QPointF, qreal);
};

#endif // SAMPLE_H
