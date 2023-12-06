#include "sample.h"
#include <math.h>

TSample::TSample(Graph* graph)
{
    gSize=graph->size;
    this->graph = graph;
}

void TSample::draw(QPainter* pen, QRect window)
{
    p = pen;
    p->setRenderHint(QPainter::Antialiasing, true);



    qreal NODE_RAD_PART = 5;
    qreal MAIN_CIRCLE_COEFFICIENT = 0.350;

    centerX = 0.5 * window.width();
    centerY = 0.5 * window.right();

    QPointF center;
    center.setX(centerX);
    center.setY(centerY);
    qreal main_radius = MAIN_CIRCLE_COEFFICIENT * window.width();
    qreal mainCircleRadius = main_radius;

    QPointF *nodePoints = new QPointF[gSize];


    qreal angelD = 2*acos(-1)/gSize; // деление окружности на равные углы
    qreal angelNodeRadDelta = angelD / NODE_RAD_PART;



    qreal curAng = 0;


    qreal nodeRad = centerY + main_radius * sin(angelNodeRadDelta) - centerY;





    p->setPen(QPen(Qt::black, 1, Qt::DashLine));

    p->drawEllipse(center, mainCircleRadius, mainCircleRadius);


    p->setFont(QFont("Arial", nodeRad));




    p->setPen(QPen(Qt::black, 2));




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


void TSample::drawConnections(QPointF lowerNode, QPointF upperNode, qreal nodeRad){

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




    qreal upstepY = sin(alfa + acos(sqrt(2)/2)) * 7;
    qreal upstepX = cos(alfa + acos(sqrt(2)/2)) * 7;
    qreal downstepY = sin(alfa - acos(sqrt(2)/2)) * 7;
    qreal downstepX = cos(alfa - acos(sqrt(2)/2)) * 7;

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













