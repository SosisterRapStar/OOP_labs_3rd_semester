#ifndef ATE_H
#define ATE_H

#include "phonewindow.h"
#include <QObject>
#include <QSet>

using namespace std;
class ATE: public QObject
{
    Q_OBJECT
public:
    ATE();
    ATE(PhoneWindow**);
    int connectionsNum;
    PhoneWindow** subBase;
    void addSubscriber(PhoneWindow*);

private:
    QVector<PhoneWindow*> callingSubs;
    QVector<PhoneWindow*> waitingSubs;
    int CONNECTIONS_LIMIT = 2;
    QSet <QString> NO_CONNECT_STATUSES;

public slots:
    void connectTwoAbonents(PhoneWindow*, QString);
    void answerSignalSlot(PhoneWindow*);
    void disconnectSignalSlot(PhoneWindow*);


};

#endif // ATE_H
