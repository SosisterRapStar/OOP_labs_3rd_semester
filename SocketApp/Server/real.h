#ifndef REAL_H
#define REAL_H

#include<QString>
#include<iostream>

using namespace std;
class real
{
    double re;
public:
    real();
    real(const double&);
    real(const QString&);
    real operator+ (real);
    real operator* (real);
    real operator- (real);
    real operator/ (real);
    real operator- ();
    bool operator!= (real);
    bool operator != (double);
    bool operator==(double);
    bool operator==(real);
    real operator+= (real);
    friend ostream& operator <<(ostream&, real);
    friend istream& operator >>(istream&, real&);
    friend QString& operator <<(QString&, real);
    friend real abs(const real& r);

};

#endif

