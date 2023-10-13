#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QDockWidget>
#include<QLabel>
#include <iostream>
#include<QBoxLayout>
#include"number.h"
using namespace std;
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Матрица");

    // настройка поля ответов
    answerEditLine->setPlaceholderText("Answer");
    sizeEditLine->setPlaceholderText("MatrixSize");
    answerEditLine->setReadOnly(true);

    matrix = new Matrix(size);
    matrixLayout = new QGridLayout();
    mainGridLayout = new QGridLayout();
    menuLayout = new QVBoxLayout();


    cells = new QLineEdit* [size];
    for (int i = 0; i < size; ++i) {
        cells[i] = new QLineEdit[size];
    }
    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {
            cells[i][j].setText("1");
            matrixLayout->addWidget(&cells[i][j], i , j);

        }
    }

    menuLayout->setSpacing(2);
    menuLayout->addWidget(sizeEditLine);
    menuLayout->addWidget(buttonTransponation);
    menuLayout->addWidget(buttonRank);
    menuLayout->addWidget(buttonDet);
    menuLayout->addWidget(answerEditLine);

    mainGridLayout->addLayout(matrixLayout, 0, 0);
    mainGridLayout->addLayout(menuLayout, 1,0);

    this->setLayout(mainGridLayout);

    //CONNECTIONS:
    connect(sizeEditLine, SIGNAL(returnPressed()), this, SLOT(change_size()));
    connect(buttonDet, SIGNAL(pressed()), this, SLOT(getDeterminant()));
    connect(buttonRank, SIGNAL(pressed()), this, SLOT(getMatrixRank()));
    connect(buttonTransponation, SIGNAL(pressed()), this, SLOT(transporn()));


}

//SLOTS:

void Interface::change_size() {

    int new_size = sizeEditLine->text().toInt();
    if(new_size <= 7 && new_size > 0){

        for (int i = 0; i < size; ++i) {
            delete[] cells[i];
        }
        delete [] cells;
        size = new_size;
        cells = new QLineEdit*[size];
        for (int i = 0; i < size; ++i) {
            cells[i] = new QLineEdit[size];
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cells[i][j].setText("1");
                matrixLayout->addWidget(&cells[i][j], i , j);
            }
        }
        this->setLayout(mainGridLayout);
        delete matrix;
        matrix = new Matrix(size);
    }

}

number Interface::parseFromLineEdit(QLineEdit* lineEdit){
    QString str  = lineEdit->text();
    bool haveRationalView = false;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '/'){
            haveRationalView = true;
            break;
        }
    }
    if(haveRationalView){
        QStringList strList = lineEdit->text().split(u'/');
        int up = strList[0].toInt();
        int down = strList[1].toInt();
        number rational(up, down);
        return rational;
    }
    number rational(str.toInt());
    return rational;
}

void Interface::getDeterminant(){
    // создание массива для хранения матрицы
    QString s("Determinant = ");
    number** valueArray = new number* [size];
    for(int i = 0; i < size; i++){
        valueArray[i] = new number [size];
    }

    for (int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            valueArray[row][col] = parseFromLineEdit(&cells[row][col]);
        }
    }
    matrix->setMatrixByArray(valueArray);
    number det = matrix->getDet();
    delete [] valueArray;
    s<<det;
    answerEditLine -> setText(s);
}
void Interface::getMatrixRank(){
    // создание массива для хранения матрицы
    QString s("Rank = ");
    number** valueArray = new number* [size];
    for(int i = 0; i < size; i++){
        valueArray[i] = new number [size];
    }

    for (int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            valueArray[row][col] = parseFromLineEdit(&cells[row][col]);
        }
    }
    matrix->setMatrixByArray(valueArray);
    int r = matrix->getRank();
    delete [] valueArray;
    s += QString().setNum(r);
    answerEditLine -> setText(s);
}

void Interface::transporn(){

    for (int row = 0; row < size; row++) {
        for (int column = row; column < size; column++) {
            QString swap = cells[column][row].text();
            cells[column][row].setText(cells[row][column].text());
            cells[row][column].setText(swap);
        }
    }
}



Interface::~Interface(){
    delete sizeEditLine;
    delete answerEditLine;
    delete mainGridLayout;
    delete matrixLayout;
    delete menuLayout;
    for (int i = 0; i < size; ++i) {
        delete[] cells[i];
    }
    delete [] cells;
    delete buttonDet;
    delete buttonRank;
    delete buttonTransponation;
    delete matrix;
}
