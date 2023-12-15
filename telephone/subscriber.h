#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QString>


class Subscriber
{

    QString number;


public:
    Subscriber();
    Subscriber(QString);
    void setStatus(QString);
    QString getNumber();


};

#endif // SUBSCRIBER_H
