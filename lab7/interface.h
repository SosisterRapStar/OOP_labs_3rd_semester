#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include<QRadioButton>
#include"sample.h"
#include<graph.h>

class Interface : public QWidget
{
    Q_OBJECT


public:
    Interface(QWidget *parent = nullptr);

    ~Interface();
    TSample* s;
    Graph *graph;
    void readFileToString();
    QString fileContent;
    QPushButton *setFileButton = new QPushButton("Выберите файл", this);
    QLineEdit* errorInfoLine = new QLineEdit(this);
    QVBoxLayout* menuLayout;
    QRect graphWindow;
    int MIN_WINDOW_SIZE = 400;
    int MAX_WINDOW_SIZE = 900;
    bool isValidString();
    void parseStringToGraph();

    void drawGraph();
    void paintEvent(QPaintEvent*);






public slots:
    void openFileSystem();





};
#endif // INTERFACE_H
