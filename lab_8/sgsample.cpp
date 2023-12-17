#include "sgsample.h"

SGSample::SGSample()
{
    gSize = 0;
    selected = 0;
}

SGSample::SGSample(Graph* graph)
{
    gSize=graph->getSize();
    this->graph = graph;
    selected = 0;
}


void SGSample::draw(QPainter* pen, QRect window){
    if (gSize == 0){
        return;
    }
    GSample::draw(pen, window);
    pen->setFont(QFont("Arial", nodeRad));
    pen->setBrush(QBrush(Qt::magenta));

    pen->drawEllipse(nodePoints[selected], nodeRad, nodeRad);
    QRectF textRect(nodePoints[selected].x() - nodeRad, nodePoints[selected].y() - nodeRad, 2 * nodeRad, 2 * nodeRad);
    pen->drawText(textRect, QString::number((selected+1)), QTextOption(Qt::AlignCenter));


}


void SGSample::clickSignal(bool direction){
    if(gSize == 0){
        return;
    }
    if (direction) this->selected++;
    else this->selected = --this->selected + this->graph->getSize();
    this->selected = this->selected % this->graph->getSize();
}
