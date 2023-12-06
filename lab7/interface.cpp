#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QLabel>
#include<QBoxLayout>
#include<QRadioButton>
#include <QFileDialog>
#include<graph.h>


using namespace std;
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Матрица");
    setFixedSize(400,400);
    readFileToString();


    // настройка поля ответов
//SLOTS:
}

void Interface::readFileToString(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open File"), "/Desktop", tr("TextFiles (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        fileContent += in.readLine();
        fileContent += '|';

    }
    graph = new Graph(fileContent);
    drawGraph();
}

void Interface::drawGraph(){
    float k = graph->size * 1/8;

    int size = MIN_WINDOW_SIZE * k;
    if (size < MIN_WINDOW_SIZE){
        setFixedSize(MIN_WINDOW_SIZE,MIN_WINDOW_SIZE);

    }
    else if (size > MAX_WINDOW_SIZE){
        setFixedSize(MAX_WINDOW_SIZE,MAX_WINDOW_SIZE);
    }
    else{
        setFixedSize(size,size);
    }
    s = new TSample(graph);
}

void Interface::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p,rect());
    p.end();
}



Interface::~Interface(){

}
