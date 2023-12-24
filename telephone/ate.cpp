#include "ate.h"
#include <QVector>


ATE::ATE()
{

}


ATE::ATE(QVector<PhoneWindow*> subBase){
    NO_CONNECT_STATUSES << "вызывает" << "вызов" << "разговор";
    connectionsNum = 0;
    this->subBase = subBase;
    for(int i = 0; i < subBase.size(); i++){
        connect(subBase[i], SIGNAL(call(PhoneWindow*, QString)), this, SLOT(connectTwoAbonents(PhoneWindow*, QString)));
        connect(subBase[i], SIGNAL(startSignal(PhoneWindow*)), this, SLOT(answerSignalSlot(PhoneWindow*))); // лишних проходов не будет
        // контрится статусом в самом окне телефона
        connect(subBase[i], SIGNAL(disconnectSignal(PhoneWindow*)), this, SLOT(disconnectSignalSlot(PhoneWindow*)));

    }
}



//slot
void ATE::connectTwoAbonents(PhoneWindow* firstPhone, QString secondPhoneNum){
    if (connectionsNum < CONNECTIONS_LIMIT){
        for(int i = 0; i < subBase.size(); i++){
            if (subBase[i]->user->getNumber() == secondPhoneNum &&
                !NO_CONNECT_STATUSES.contains(subBase[i]->getStatus())
                && subBase[i] != firstPhone){
                connectionsNum++;
                // firstPhone->connectTo(subBase[i]);
                // subBase[i]->connectTo(firstPhone);
                waitingSubs.push_back(subBase[i]);
                callingSubs.push_back(firstPhone);
                firstPhone->setStatus("вызывает");
                subBase[i]->setStatus("вызов");
                return;
            }
            else{
                firstPhone->setMessage("занято");
                return;
            }
        }
    }
    else{
        firstPhone->setMessage("занято");
    }

}

void ATE::disconnectSignalSlot(PhoneWindow* sub){
    /*f (sub->getStatus() == "вызывает"){
        for(int i = 0; i < callingSubs.size(); i++){
            if(callingSubs[i] == sub){
                connectionsNum--;
                sub->disconnectPhone();
                waitingSubs[i]->disconnectPhone();
                callingSubs.remove(i);
                waitingSubs.remove(i);
                return;
            }
        }
    }
    else if(sub->getStatus() == "вызов"){
        for(int i = 0; i < callingSubs.size(); i++){
            if(waitingSubs[i] == sub){
                connectionsNum--;
                sub->disconnectPhone();
                callingSubs[i]->disconnectPhone();
                callingSubs.remove(i);
                waitingSubs.remove(i);
                return;
            }
        }
    }*/

    for(int i = 0; i < callingSubs.size(); i++){
        if (sub == callingSubs[i]){
            connectionsNum--;

            sub->setStatus("бездействует");
            waitingSubs[i]->setStatus("бездействует");

            callingSubs.remove(i);
            waitingSubs.remove(i);
            return;
        }
        else if(sub == waitingSubs[i]){
            connectionsNum--;

            sub->setStatus("бездействует");
            callingSubs[i]->setStatus("бездействует");


            callingSubs.remove(i);
            waitingSubs.remove(i);
            return;
        }
    }


}

void ATE::answerSignalSlot(PhoneWindow* answeringSub){
    for(int i = 0; i < waitingSubs.size(); i++){
        if(waitingSubs[i] == answeringSub){
            answeringSub->setStatus("разговор");  // ?
            callingSubs[i]->setStatus("разговор");

            callingSubs[i]->connectTo(answeringSub);
            answeringSub->connectTo(callingSubs[i]);
            return;

        }
    }
}
