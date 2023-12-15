#include "subscriber.h"

Subscriber::Subscriber()
{
    number = "228-1337-69";

}

Subscriber::Subscriber(QString number)
{
    this->number = number;

}



QString Subscriber::getNumber(){
    return number;
}


