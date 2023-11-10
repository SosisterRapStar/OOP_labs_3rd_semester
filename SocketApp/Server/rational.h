#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <QString>
using namespace std;

const QString RATIONAL_SEPARATOR("/");

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
    bool operator != (double);
    bool operator==(Rational);
    bool operator==(double);
    Rational operator/ (Rational);
    Rational operator+= (Rational);
    friend ostream& operator <<(ostream&, Rational);
    friend istream& operator >>(istream&, Rational&);
    friend QString& operator <<(QString&, Rational);
    friend Rational abs(const Rational& r);

};

#endif // RATIONAL_H
