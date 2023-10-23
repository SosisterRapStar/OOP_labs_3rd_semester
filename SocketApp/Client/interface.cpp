#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QLabel>
#include<QBoxLayout>
#include"message.h"



using namespace std;
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Матрица");

    // настройка поля ответов
    answerEditLine->setPlaceholderText("Answer");
    sizeEditLine->setPlaceholderText("MatrixSize");
    answerEditLine->setReadOnly(true);

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
    connect(buttonDet, SIGNAL(pressed()), this, SLOT(makeRequest()));
    connect(buttonRank, SIGNAL(pressed()), this, SLOT(makeRequest()));
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
    }

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

void Interface::answer(Message msg){
    QString ans = msg.body;
    answerEditLine -> setText(ans);
}


void Interface::makeRequest(){
    // создание массива для хранения матрицы
    QPushButton *button = (QPushButton *)sender();
    if(button == buttonDet){
        Message msg(REQUEST, DETERMINANT, formMatrixBody());
        emit request(msg);
    }
    if(button == buttonRank){
        Message msg(REQUEST, RANK, formMatrixBody());
        emit request(msg);
    }
}


QString Interface::formMatrixBody(){

    QString matrix_size = QString().setNum(size);

    QString body = matrix_size + MATRIX_SEPARATOR;
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            body += cells[row][col].text() + " ";
        }
        body += MATRIX_SEPARATOR;
    }
    return body;
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
}
