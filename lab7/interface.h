#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include<QRadioButton>
#include"canvas.h"
#include"sample.h"
#include<graph.h>

class Interface : public QWidget
{
    Q_OBJECT

    QGridLayout* mainGridLayout;





public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    TSample* s;
    Graph *graph;
    void readFileToString();
    QString fileContent;
    int MIN_WINDOW_SIZE = 400;
    int MAX_WINDOW_SIZE = 900;



private:

    void parseStringToGraph();
    void paintEvent(QPaintEvent*);
    void drawGraph();

public slots:

};
#endif // INTERFACE_H
