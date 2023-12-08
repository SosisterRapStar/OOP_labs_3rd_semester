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
    Interface(TSample, QWidget *parent = nullptr);

    ~Interface();
    QPushButton *setFileButton = new QPushButton("Выберите файл", this); // кнопка для выбора файла
    QLineEdit* errorInfoLine = new QLineEdit(this); // строка для отображения ошибки
    void drawGraph();

private:
    TSample s; // объект семпла
    Graph *graph; // объект графа
    int MIN_WINDOW_SIZE = 400; // минимальный размер окна
    int MAX_WINDOW_SIZE = 900; // максимальный размер окна
    void paintEvent(QPaintEvent*);




public slots:
    void openGraph();







};
#endif // INTERFACE_H
