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
Interface::Interface(SGSample sample, QWidget *parent)
    : QWidget(parent)
{
    s = sample;
    this->setWindowTitle("Граф");


    setFixedSize(400, 400);


    errorInfoLine->setPlaceholderText("Нажмите кнопку для выбора");
    errorInfoLine->setReadOnly(true);

    setFileButton->setGeometry(QRect(0, 0, 150, 40));
    errorInfoLine->setGeometry(QRect(0, 40, 150, 20));

    connect(setFileButton,SIGNAL(pressed()),this, SLOT(openGraph()));

    // настройка поля ответов
//SLOTS:
}


void Interface::openGraph(){ // Поиск файла и его отрктия
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/", tr("TextFiles (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    QString fileContent = "";

    // Парсинг файла в строку
    while (!in.atEnd()) {
        fileContent += in.readLine();
        fileContent += '|'; // разделяющая строка
    }

    graph = new Graph();
    bool isValidGraph = graph->setGraphByString(fileContent); // Принимает false если файл задан неверно




    if (isValidGraph){
        drawGraph();
    }
    else{
        errorInfoLine->setText("Ошибка в формате");
        return;
    }

}




void Interface::drawGraph(){ // функция регулирует изменение размера окна для графов разных размеров

    float k = graph->getSize() * 1/5;
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
    s = SGSample(graph);
    repaint();
}

void Interface::paintEvent(QPaintEvent*)
{

    QPainter p;
    p.begin(this);
    s.draw(&p, rect());
    p.end();
}

void Interface::mousePressEvent(QMouseEvent* event){ // вот тут обработчик нажатия на клавишу
    if (event->button() == Qt::LeftButton)  s.clickSignal(false);
    if (event->button() == Qt::RightButton) s.clickSignal(true);
    update();
}

Interface::~Interface(){
    delete setFileButton;
    delete errorInfoLine;
}
