#include "phonewindow.h"
#include <QGridLayout>
#include <string.h>
PhoneWindow::PhoneWindow(Subscriber* user, QWidget *parent){
//    this->sub = sub;
    this->user =user;
    status = "бездействует";

    statusScreen->setReadOnly(true);


    numberScreen = new QLineEdit("", this);
    mainInterface = new QGridLayout(this);

    keyBoard = new QPushButton * [4];
    for(int i = 0; i < 4; i++){
        keyBoard[i] = new QPushButton [3];
    }



    QStringList cups{"1", "2", "3", "4", "5", "6", "7", "8", "9", "-", "0", "<-"};
    int cupsI = 0;
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 3; col++){
            keyBoard[row][col].setText(cups[cupsI]);
            connect(&keyBoard[row][col], SIGNAL(clicked()), this, SLOT(input()));
            keys->addWidget(&keyBoard[row][col], row, col);
            cupsI++;
        }
    }


    mainInterface->addWidget(statusScreen, 0, 0);
    mainInterface->addWidget(numberScreen, 1, 0);
    mainInterface->addLayout(keys, 2, 0);

    startButton = new QPushButton("Ответить");
    stopButton = new QPushButton("Сбросить");
    startCallButton = new QPushButton("Позвонить");

    stopButton->setStyleSheet("color: white; background-color: maroon");
    startButton->setStyleSheet("color: white; background-color: darkGreen");

    buttons = new QHBoxLayout();
    buttons->addWidget(startButton);
    buttons->addWidget(startCallButton);
    buttons->addWidget(stopButton);
    mainInterface->addLayout(buttons, 3, 0);
    messageScreen = new QLineEdit();
    messageScreen->setReadOnly(true);

    messageLay->addWidget(messageScreen, 0, 0, 5, 3);
    mainInterface->addLayout(messageLay, 4, 0, 6, 0);

    connect(messageScreen, SIGNAL(textChanged(QString)), this, SLOT(sendData(QString)));

    connect(startCallButton, SIGNAL(pressed()), this, SLOT(startCall()));

    connect(startButton, SIGNAL(pressed()), this, SLOT(startSignalSlot()));

    connect(stopButton, SIGNAL(pressed()), this, SLOT(disconnectSignalSlot()));

    statusScreen->setText(status);

}

PhoneWindow::~PhoneWindow()
{

}

QString PhoneWindow::getStatus(){
    return status;
}

void PhoneWindow::setStatus(QString newStatus){
    status = newStatus;
    if(newStatus == "вызов"){
        activeKeyboard(false);
        stopButton->setStyleSheet("color: white; background-color: red");
        startButton->setStyleSheet("color: white; background-color: green");
        startCallButton->setEnabled(false);
        numberScreen->setReadOnly(true);
    }
    else if(newStatus == "вызывает"){
        activeKeyboard(false);
        startCallButton->setEnabled(false);
        stopButton->setStyleSheet("color: white; background-color: red");
        startButton->setStyleSheet("color: white; background-color: darkGreen");
        startButton->setEnabled(false);
        numberScreen->setReadOnly(true);
    }
    else if(newStatus == "разговор"){
        messageScreen->setReadOnly(false);
        stopButton->setStyleSheet("color: white; background-color: red");
        startButton->setStyleSheet("color: white; background-color: darkGreen");
        activeKeyboard(false);
        startButton->setEnabled(false);
        startCallButton->setEnabled(false);
        numberScreen->setReadOnly(true);
    }
    else if(newStatus == "бездействует"){
        activeKeyboard(true);
        startButton->setEnabled(true);
        stopButton->setStyleSheet("color: white; background-color: maroon");
        startCallButton->setEnabled(true);
        startButton->setStyleSheet("color: white; background-color: darkGreen");
        stopButton->setEnabled(true);
        numberScreen->setReadOnly(false);
        messageScreen->setText("");
        messageScreen->setReadOnly(true);
        numberScreen->setText("");
    }
    statusScreen->setText(status);
}



void PhoneWindow::disconnectPhone(){
    disconnect(connectedPhone, SIGNAL(messageTyping(QString)), this, SLOT(recieveData(QString)));
    connectedPhone = nullptr;

}

void PhoneWindow::connectTo(PhoneWindow* phone){
    connectedPhone = phone;
    connect(connectedPhone, SIGNAL(messageTyping(QString)), this, SLOT(recieveData(QString)));
}


void PhoneWindow::setMessage(QString msg){
    messageScreen->setText(msg);
}

//slots:


void PhoneWindow::startSignalSlot(){
    emit startSignal(this);
}


void PhoneWindow::disconnectSignalSlot(){
    emit disconnectSignal(this);
}


void PhoneWindow::input(){

    QPushButton *button = (QPushButton *)sender();
    if(button->text() != "<-"){
        numberScreen->setText(numberScreen->text()+button->text());
        return;
    }
    numberScreen->setText(numberScreen->text().remove(numberScreen->text().size()-1, 1));
    return;
}

void PhoneWindow::sendData(QString a){
    emit messageTyping(a);
}

void PhoneWindow::recieveData(QString str){
    messageScreen->setText(str);
}



void PhoneWindow::startCall(){
    emit call(this, numberScreen->text());
}


void PhoneWindow::activeKeyboard(bool active){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 3; col++){
            keyBoard[row][col].setEnabled(active);
        }
    }
}

//void PhoneWindow::addCallingSub(PhoneWindow* callingSub){
//    this->callingSub[0] = callingSub;
//    activeKeyboard(false);
//    startCallButton->setEnabled(false);
//    numberScreen->setReadOnly(true);
//}

//void PhoneWindow::addWaitingSub(PhoneWindow* waitingSub){
//    this->waitingSub[0] = waitingSub;
//    activeKeyboard(false);
//    startCallButton->setEnabled(false);
//    startButton->setEnabled(false);
//    numberScreen->setReadOnly(true);
//}





//void PhoneWindow::disconnect(){
//    connectedPhone = nullptr;
//}
