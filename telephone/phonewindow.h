#ifndef PHONEWINDOW_H
#define PHONEWINDOW_H

#include <QWidget>
#include "subscriber.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>


class PhoneWindow : public QWidget
{
    Q_OBJECT

public:
    PhoneWindow(Subscriber*, QWidget *parent = nullptr);

    QString status;
    Subscriber* user;
    QPushButton* startButton; // снять трубку
    QPushButton* startCallButton;
    QPushButton* stopButton; // опустить трубку
    QLineEdit* numberScreen;
    QLineEdit* messageScreen;
    QGridLayout* messageLay = new QGridLayout();
    QGridLayout* keys = new QGridLayout();
    QLineEdit* statusScreen = new QLineEdit();

    PhoneWindow* connectedPhone; // ?

    QPushButton** keyBoard;
    QHBoxLayout* buttons;
    ~PhoneWindow();
    QVBoxLayout* mainInterface;


    void setMessage(QString);


    void connectTo(PhoneWindow*);
    void disconnectPhone();


    void setStatus(QString);
    QString getStatus();


//    void addCallingSub(PhoneWindow*);
//    void addWaitingSub(PhoneWindow*);

//    void clearCallingList();
//    void clearWaitingList();


    void activeKeyboard(bool);


private:
//    PhoneWindow** callingSub = new PhoneWindow* [1];
//    PhoneWindow** waitingSub = new PhoneWindow* [1];
    Subscriber sub;
    QString number;

public slots:
//    void startCall();
//    void changeState();
//    void call();
//    void closeConnection(); // ?

    void input();
    void sendData(QString);
    void recieveData(QString);
    void startCall(); // к кнопке звонка и вызывать сигнал call
    void startSignalSlot();
    void disconnectSignalSlot();

signals:
    void messageTyping(QString str);
    void call(PhoneWindow*, QString);
    void startSignal(PhoneWindow*);
    void disconnectSignal(PhoneWindow*);

};

#endif // PHONEWINDOW_H
