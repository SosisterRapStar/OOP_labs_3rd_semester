#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <QString>
using namespace std;

class Rational
{
    int up, down;

public:
    Rational();
    Rational(const int&);
    Rational(const int& numerator, const int& denominator);
    void GCD();
    Rational operator+ (Rational);
    Rational operator* (Rational);
    Rational operator- (Rational);
    Rational operator- ();
    bool operator!= (Rational);
    bool operator != (int);
    bool operator==(Rational);
    bool operator==(int);
    friend ostream& operator <<(ostream&, Rational);
    friend istream& operator >>(istream&, Rational&);

    friend QString& operator <<(QString&, Rational);

};

#endif // RATIONAL_H
