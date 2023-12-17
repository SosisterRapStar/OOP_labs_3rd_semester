#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include"graph.h"
class GSample
{


    QPainter* p;
    qreal centerX;
    qreal centerY;
protected:
    Graph* graph;
    int gSize;
    qreal nodeRad;
    QPointF *nodePoints;
public:
    GSample(Graph*);
    GSample();
    void draw(QPainter*,QRect);
private:
    void drawConnections(QPointF, QPointF, qreal);
    qreal arrowAngel = acos((sqrt(3)/2)); // угол наклона стрелки
    int arrowLength = 7; // длина стрелки
    qreal NODE_RAD_PART = 5;  // часть от длины отрезка окружности между двумя узлами
    qreal MAIN_CIRCLE_COEFFICIENT = 0.350; // коэффициент расчитывающий размер главной окружности
};

#endif // SAMPLE_H
