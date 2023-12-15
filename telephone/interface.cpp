#include "interface.h"
#include<QLineEdit>
#include<QPushButton>
#include<QRect>
#include<QLabel>
#include<QBoxLayout>
#include<QRadioButton>
#include <QFileDialog>
#include<QPoint>
#include "phonewindow.h"
#include<QGridLayout>
#include "ate.h"


using namespace std;
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    Subscriber* user1 = new Subscriber("1");
    Subscriber* user2 = new Subscriber("2");
    Subscriber* user3 = new Subscriber("3");
    Subscriber* user4 = new Subscriber("4");
    Subscriber* user5 = new Subscriber("5");
    Subscriber* user6 = new Subscriber("6");

    PhoneWindow* phone1 = new PhoneWindow(user1);
    PhoneWindow* phone2 = new PhoneWindow(user2);
    PhoneWindow* phone3 = new PhoneWindow(user3);
    PhoneWindow* phone4 = new PhoneWindow(user4);
    PhoneWindow* phone5 = new PhoneWindow(user5);
    PhoneWindow* phone6 = new PhoneWindow(user6);

    PhoneWindow** phones = new PhoneWindow * [6];
    phones[0] = phone1;
    phones[1] = phone2;
    phones[2] = phone3;
    phones[3] = phone4;
    phones[4] = phone5;
    phones[5] = phone6;

    ATE* ate = new ATE(phones);

    QGridLayout *interface = new QGridLayout(this);

    interface->addWidget(phone1, 0, 0);
    interface->addWidget(phone2, 0, 1);
    interface->addWidget(phone3, 1, 0);
    interface->addWidget(phone4, 1, 1);
    interface->addWidget(phone5, 0, 2);
    interface->addWidget(phone6, 1, 2);


    // настройка поля ответов
//SLOTS:
}





Interface::~Interface(){

}
