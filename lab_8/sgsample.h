#ifndef SGSAMPLE_H
#define SGSAMPLE_H
#include "sample.h"

class SGSample : public GSample
{
    int selected;
public:
    SGSample(Graph* g);
    SGSample();
    void clickSignal(bool);
    void draw(QPainter* pen, QRect window);
};

#endif // SGSAMPLE_H
