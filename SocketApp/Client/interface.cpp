#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QLabel>
#include<QBoxLayout>
#include"message.h"
#include<QRadioButton>



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
    type_layout = new QGridLayout();
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


    type_layout->addWidget(real_type, 0, 0);
    type_layout->addWidget(complex_type, 0, 1);
    rational_type->setChecked(true);
    type_layout->addWidget(rational_type, 0, 2);

    menuLayout->addWidget(answerEditLine);
    mainGridLayout->addLayout(type_layout, 0, 0);
    mainGridLayout->addLayout(matrixLayout, 1, 0);
    mainGridLayout->addLayout(menuLayout, 2,0);

    this->setLayout(mainGridLayout);

    //CONNECTIONS:

    connect(real_type, SIGNAL(clicked()), this, SLOT(change_view()));
    connect(complex_type, SIGNAL(clicked()), this, SLOT(change_view()));
    connect(rational_type, SIGNAL(clicked()), this, SLOT(change_view()));

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
                cells[i][j].setText(current_cell_type);
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

int Interface::get_request_datatype(){
    if (real_type->isChecked()){
        return REAL;
    }
    else if(complex_type->isChecked()){
        return COMPLEX;
    }
    else{
        return RATIONAL;
    }
}


void Interface::change_view(){
    int type = get_request_datatype();
    if (type == REAL || type == RATIONAL){
        current_cell_type = "1";
        for (int i = 0; i < size; ++i) {

            for (int j = 0; j < size; ++j) {
                cells[i][j].setText(current_cell_type);
                matrixLayout->addWidget(&cells[i][j], i , j);

            }
        }
    }
    else{
        current_cell_type = "1+0";
        for (int i = 0; i < size; ++i) {

            for (int j = 0; j < size; ++j) {
                cells[i][j].setText(current_cell_type);
                matrixLayout->addWidget(&cells[i][j], i , j);

            }
        }
    }
}

void Interface::makeRequest(){
    // создание массива для хранения матрицы
    QPushButton *button = (QPushButton *)sender();
    if(button == buttonDet){
        Message msg(REQUEST, DETERMINANT, get_request_datatype(), formMatrixBody());
        emit request(msg);
    }
    if(button == buttonRank){
        Message msg(REQUEST, RANK, get_request_datatype(),formMatrixBody());
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
    delete type_layout;
    for (int i = 0; i < size; ++i) {
        delete[] cells[i];
    }
    delete [] cells;
    delete buttonDet;
    delete buttonRank;
    delete buttonTransponation;
}
