#include "sample.h"
#include <math.h>

GSample::GSample(Graph* graph)
{
    gSize=graph->getSize();
    this->graph = graph;
}

GSample::GSample(){
    gSize = 0;
}

void GSample::draw(QPainter* pen, QRect window)
{
    p = pen;
    p->setRenderHint(QPainter::Antialiasing, true);

    centerX = 0.5 * window.width();
    centerY = 0.5 * window.right();

    QPointF center(centerX, centerY); // центр окружности
    qreal main_radius = MAIN_CIRCLE_COEFFICIENT * window.width();
    qreal mainCircleRadius = main_radius;
    qreal angelD = 2*acos(-1)/gSize;
    qreal angelNodeRadDelta = angelD / NODE_RAD_PART;
    qreal nodeRad = centerY + main_radius * sin(angelNodeRadDelta) - centerY;

    p->setPen(QPen(Qt::black, 1, Qt::DashLine));
    p->drawEllipse(center, mainCircleRadius, mainCircleRadius);
    p->setFont(QFont("Arial", nodeRad));
    p->setPen(QPen(Qt::black, 2));


    QPointF *nodePoints = new QPointF[gSize];
    qreal curAng = 0;
    for(int i = 0; i < gSize; i++){
        nodePoints[i] = QPointF(centerX + main_radius * cos(curAng), centerY + main_radius * sin(curAng));

        p->drawEllipse(nodePoints[i], nodeRad, nodeRad);
        QRectF textRect(nodePoints[i].x() - nodeRad, nodePoints[i].y() - nodeRad, 2 * nodeRad, 2 * nodeRad);
        p->drawText(textRect, QString::number((i+1)), QTextOption(Qt::AlignCenter));
        curAng += angelD;

    }


    for(int i = 0; i < gSize; i++){
        int *n = graph->getNeighbours(i);
        for(int g = 0; g < gSize; g++){
            if (n[g] != 0){
                drawConnections(nodePoints[i], nodePoints[g], nodeRad);
            }
        }
    }


}


void GSample::drawConnections(QPointF lowerNode, QPointF upperNode, qreal nodeRad){

    p->setPen(QPen(2));
    bool isSwaped = false;
    if (lowerNode.y() < upperNode.y()){
        swap(lowerNode, upperNode);
        isSwaped = true;
    }

    qreal b = upperNode.x() - lowerNode.x();
    qreal a = lowerNode.y() - upperNode.y();
    qreal alfa = atan(a/b);

    qreal xDelta = cos(alfa) * nodeRad;
    qreal yDelta = sin(alfa) * nodeRad;

    if (alfa < 0){
        xDelta *= -1;
        yDelta *= -1;
    }

    lowerNode.setX(lowerNode.x() + xDelta);
    lowerNode.setY(lowerNode.y() - yDelta);
    upperNode.setX(upperNode.x() - xDelta);
    upperNode.setY(upperNode.y() + yDelta);
    p->drawLine(lowerNode, upperNode);



    qreal upstepY = sin(alfa + arrowAngel) * arrowLength;
    qreal upstepX = cos(alfa + arrowAngel) * arrowLength;
    qreal downstepY = sin(alfa - arrowAngel) * arrowLength;
    qreal downstepX = cos(alfa - arrowAngel) * arrowLength;

    if (alfa < 0){
        upstepY *= -1;
        upstepX *= -1;
        downstepY *= -1;
        downstepX *= -1;
    }

    if(!isSwaped){
        p->drawLine(upperNode, QPointF(upperNode.x() - upstepX, upperNode.y() + upstepY));
        p->drawLine(upperNode, QPointF(upperNode.x() - downstepX, upperNode.y() + downstepY));
    }

    else{
        swap(upperNode, lowerNode);
        p->drawLine(upperNode, QPointF(upperNode.x() + upstepX, upperNode.y() - upstepY));
        p->drawLine(upperNode, QPointF(upperNode.x() + downstepX, upperNode.y() - downstepY));
    }
}




//        qreal k =(lowerNode.y() - upperNode.y())/(upperNode.x() - lowerNode.x());
//        qreal stepY = (tan(alfa) * stepX);
//        qreal upperArrX = upperNode.x() - 30;
//        qreal upperArrY = (- 1/tan(alfa)) * (upperArrX - stepX) + stepY;
//        qreal lowerArrX = upperNode.x() + 30;
//        qreal lowerArrY = (- 1/tan(alfa)) * (upperArrX - stepX) + stepY;
//        p -> drawLine(upperNode, QPointF(upperArrX, upperArrY));
//        p -> drawLine(upperNode, QPointF(lowerArrX, lowerArrY));
//    }













