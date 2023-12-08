#include "interface.h"
#include "sample.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TSample s;
    Interface w(s);
    w.show();
    return a.exec();
}
