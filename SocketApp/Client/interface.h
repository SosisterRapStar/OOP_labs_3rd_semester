#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include"message.h"
#include<QRadioButton>

class Interface : public QWidget
{
    Q_OBJECT
    QLineEdit* sizeEditLine = new QLineEdit();
    QLineEdit* answerEditLine = new QLineEdit();
    QGridLayout* mainGridLayout;
    QGridLayout* matrixLayout;
    QGridLayout* type_layout;
    QVBoxLayout* menuLayout;
    QLineEdit** cells;
    int size = 3;
    QPushButton *buttonDet = new QPushButton("Детерминант");
    QPushButton *buttonRank = new QPushButton("Ранг");
    QPushButton *buttonTransponation = new QPushButton("Транспонирование");
    QRadioButton *real_type = new QRadioButton("Вещественные числа");
    QRadioButton *complex_type = new QRadioButton("Комплексные числа");
    QRadioButton *rational_type = new QRadioButton("Рациональные числа");



public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
private:
    QString current_cell_type = "1";
    int get_request_datatype();
    QString formMatrixBody();
public slots:
    void change_view();
    void answer(Message);
    void makeRequest();
    void transporn();
    void change_size();
signals:
    void request(Message);
};
#endif // INTERFACE_H
