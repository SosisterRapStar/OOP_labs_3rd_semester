#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include"matrix.h"
#include"number.h"
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
    Matrix* matrix;



public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
public slots:
    void transporn();
    void getMatrixRank();
    number parseFromLineEdit(QLineEdit*);
    void getDeterminant();
    void change_size();
};
#endif // INTERFACE_H
