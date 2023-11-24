

#include "real.h"
#include <iostream>
#include <QStringList>
#include <QString>
using namespace std;


real::real() {
    re = 0;
}

real::real(const QString& str){
    re = str.toDouble();
}


real::real(const double& r){
    re = r;
}


bool real::operator==(real c) {
    return re == c.re;
}

real real::operator*(real c) {
    real t;
    t.re = re * c.re;
    return t;
}


real real::operator-(real c) {
    real t;
    t.re = re - c.re;
    return t;
}

real real::operator-()
{
    real t;
    t.re = -re;
    return t;
}

bool real::operator!=(real c)
{
    return (re != c.re);
}

real real::operator+(real c) {
    real t;
    t.re = re + c.re;
    return t;
}
bool real::operator==(double d) {

    return re == d;
}

bool real::operator!=(double d) {
    return re != d;
}


real real::operator+=(real c){
    re += c.re;
    return *this;
}

real real::operator/(real c) {
    real t;
    t.re = re / c.re;
    return t;

}

ostream& operator<<(ostream& os, real c)
{
    os << c.re;
    return os;
}


istream& operator>>(istream& is, real& c)
{
    is >> c.re;
    return is;
}

QString& operator <<(QString& string, real r){
    string += QString::number(r.re);
    return string;
}

real abs(const real& r) {
    return abs(r.re);
}





