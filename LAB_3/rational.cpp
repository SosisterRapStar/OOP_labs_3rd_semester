#include "rational.h"

using namespace std;
Rational::  Rational()
{
    up = 0;
    down = 1;
}

Rational::  Rational(const int& real)
{
    up = real;
    down = 1;
}

Rational::  Rational(const int& numerator, const int& denominator)
{
    if (denominator == 0) {
        up = numerator;
        down = 1;
        return;
    }
    up = numerator;
    down = denominator;
    GCD();

}



Rational   Rational::operator+(  Rational other)
{
    Rational t;
    t.up = (up * other.down) + (other.up * down);
    t.down = down * other.down;
    t.GCD();
    return t;
}

Rational   Rational::operator*(  Rational other) {
    Rational t;
    t.up = up * other.up;
    t.down = down * other.down;
    t.GCD();
    return t;
}

Rational   Rational::operator-(  Rational other)
{
    Rational t;
    t.up = (up * other.down) - (other.up * down);
    t.down = down * other.down;
    t.GCD();
    return t;
}
Rational   Rational::operator-()
{
    Rational t;
    t.up = -up;
    t.down = down;
    return t;
}

bool   Rational::operator!=(  Rational other)
{

    return up != other.up && down != other.down;
}

bool   Rational::operator==(  Rational other)
{

    return up == other.up && down == other.down;
}

void   Rational::GCD() { // алгоритм Евклида
    int t;
    int a = up;
    int b = down;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    up /= a;
    down /= a;
}

ostream& operator<<(ostream& os,   Rational r)
{

    os << r.up << "/" << r.down;
    return os;
}
istream& operator >>(istream& is,   Rational& r) {
    is >> r.up >> r.down;
    return is;
}


bool Rational::operator != (int val){
    return up / down != val;
}

bool Rational::operator==(int val){
    return up / down == val;
}

QString& operator <<(QString& string, Rational r){
    string += QString().setNum(r.up);
    string += "/";
    string+= QString().setNum(r.down);
    return string;
}


