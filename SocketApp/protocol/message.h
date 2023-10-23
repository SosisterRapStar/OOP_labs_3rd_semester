#ifndef MESSAGE_H
#define MESSAGE_H
#include<QString>


const QString MATRIX_SEPARATOR("|");
const QString SEPARATOR(";");


enum headers
{
    REQUEST=1,
    RESPONSE,
};

enum methods
{
    DETERMINANT = 1,
    RANK,
    ANSWER,
};


class Message
{
QString toString();
public:
    Message(QByteArray);
    Message(int header, int method, QString body);
    int header;
    int method;
    QString body;
    QByteArray toQByteArray();
    QString fromQByteArray(QByteArray& arr);

};


#endif // MESSAGE_H

