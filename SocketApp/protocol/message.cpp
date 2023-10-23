#include "message.h"
#include <QString>
#include<QStringList>



Message::Message(int header, int method, QString body)
{
    this->header = header;
    this->method = method;
    this->body = body;
}

Message::Message(QByteArray arr)
{
    QString str = QString(arr);
    QStringList strList = str.split(SEPARATOR);
    header = strList[0].toInt();
    method = strList[1].toInt();
    body = strList[2];

}



QString Message::toString(){

    QString head;
    head.setNum(header);
    QString meth;
    meth.setNum(method);
    return head + SEPARATOR + meth + SEPARATOR + body;

}

QByteArray Message::toQByteArray(){

    QString str = toString();
    QByteArray byteString = str.toLocal8Bit();
    return byteString;
}
