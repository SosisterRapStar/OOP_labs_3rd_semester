#include "message.h"
#include <QString>
#include<QStringList>



Message::Message(int header, int method, int type, QString body)
{
    this->header = header;
    this->method = method;
    this->type = type;
    this->body = body;
}




Message::Message(QByteArray arr)
{
    QString str = QString(arr);
    QStringList strList = str.split(SEPARATOR);
    header = strList[0].toInt();
    method = strList[1].toInt();
    type = strList[2].toInt();
    body = strList[3];

}



QString Message::toString(){

    QString head;
    head.setNum(header);
    QString meth;
    meth.setNum(method);
    QString typ;
    typ.setNum(type);
    return head + SEPARATOR + meth + SEPARATOR + typ + SEPARATOR + body;

}

QByteArray Message::toQByteArray(){

    QString str = toString();
    QByteArray byteString = str.toLocal8Bit();
    return byteString;
}
