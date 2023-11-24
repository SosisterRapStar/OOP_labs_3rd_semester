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

enum types
{
    REAL = 1,
    COMPLEX,
    RATIONAL,
};


class Message
{
QString toString();
public:
    Message(QByteArray);
    Message(int header, int method, int type, QString body);
    int header;
    int method;
    int type;
    QString body;
    QByteArray toQByteArray();

};


#endif // MESSAGE_H

