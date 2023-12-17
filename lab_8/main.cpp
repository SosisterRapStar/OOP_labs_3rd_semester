#include "interface.h"
#include "sgsample.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SGSample s;
    Interface w(s);
    w.show();
    return a.exec();
}
