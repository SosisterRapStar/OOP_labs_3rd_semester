#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QRect>
#include<QLabel>
#include<QBoxLayout>
#include<QRadioButton>
#include <QFileDialog>
#include<graph.h>
#include<QPoint>


using namespace std;
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{

    this->setWindowTitle("Матрица");
    setFixedSize(400, 400);
    errorInfoLine->setPlaceholderText("Нажмите для кнопку для выбора");
    errorInfoLine->setReadOnly(true);

    setFileButton->setGeometry(QRect(100, 150, 200, 50));
    errorInfoLine->setGeometry(QRect(100, 200, 200, 50));

    connect(setFileButton,SIGNAL(pressed()),this, SLOT(openFileSystem()));

    // настройка поля ответов
//SLOTS:
}


void Interface::openFileSystem(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/", tr("TextFiles (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        fileContent += in.readLine();
        fileContent += '|';

    }
    graph = new Graph();
    bool isValidGraph = graph->setGraphByString(fileContent);
    if (isValidGraph){
        drawGraph();
    }
    else{
        errorInfoLine->setText("Ошибка в формате графа внутри txt файла");
        return;
    }

}




void Interface::drawGraph(){

    float k = graph->size * 1/8;

    int size = MIN_WINDOW_SIZE * k;
    if (size < MIN_WINDOW_SIZE){
        graphWindow = QRect(5, 5, MIN_WINDOW_SIZE,MIN_WINDOW_SIZE);

    }
    else if (size > MAX_WINDOW_SIZE){
        graphWindow = QRect(5, 5, MAX_WINDOW_SIZE,MAX_WINDOW_SIZE);
    }
    else{
        graphWindow = QRect(5, 5, size,size);

    }
    s = new TSample(graph);
    repaint();
}

void Interface::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    s->draw(&p, graphWindow);
    p.end();
}



Interface::~Interface(){

}
