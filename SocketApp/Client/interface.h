#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include"message.h"

class Interface : public QWidget
{
    Q_OBJECT
    QLineEdit* sizeEditLine = new QLineEdit();
    QLineEdit* answerEditLine = new QLineEdit();
    QGridLayout* mainGridLayout;
    QGridLayout* matrixLayout;
    QVBoxLayout* menuLayout;
    QLineEdit** cells;
    int size = 3;
    QPushButton *buttonDet = new QPushButton("Детерминант");
    QPushButton *buttonRank = new QPushButton("Ранг");
    QPushButton *buttonTransponation = new QPushButton("Транспонирование");



public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
private:
    QString formMatrixBody();
public slots:
    void answer(Message);
    void makeRequest();
    void transporn();
    void change_size();
signals:
    void request(Message);
};
#endif // INTERFACE_H
