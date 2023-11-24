#include "complex.h"
#include <iostream>
#include <QStringList>
#include <QString>
using namespace std;


complex::complex() {
    re = 0;
    im = 0;
}

complex::complex(const QString& str){
    QStringList strList = str.split(COMPLEX_SEPARATOR);

    re = strList[0].toDouble();
    im = strList[1].toDouble();
}


complex::complex(const double& r, const double& i){
    re = r;
    im = i;
}
complex::complex(const double& r)
{
    re = r;
    im = 0;
}


bool complex::operator==(complex c) {
    return (re == c.re) && (im == c.im);
}

complex complex::operator*(complex c) {
    complex t;
    t.re = re * c.re - im * c.im;
    t.im = re * c.im + im * c.re;
    return t;
}


complex complex::operator-(complex c) {
    complex t;
    t.re = (re - c.re);
    t.im = (im - c.im);
    return t;
}

complex complex::operator-()
{
    complex t;
    t.im = -im;
    t.re = -re;
    return t;
}

bool complex::operator!=(complex c)
{
    return (re != c.re) && (im != c.im);
}

complex complex::operator+(complex c) {
    complex t;
    t.re = re + c.re;
    t.im = im + c.im;
    return t;
}
bool complex::operator==(double d) {

    if (im != 0) return false;
    if (re == d) return true;
    return false;
}

bool complex::operator!=(double d) {
    if (im != 0) return true;
    if (re == d) return false;
    return true;
}


complex complex::operator+=(complex c){
    re = re + c.re;
    im = im + c.im;
    return *this;
}

complex complex::operator/(complex c) {
    complex t;
    t.re = (re * c.re + im * c.im)/((c.re*c.re) + (c.im * c.im));
    t.im = ((im * c.re) - (re * c.im))/((c.re*c.re) + (c.im * c.im));
    return t;

}

ostream& operator<<(ostream& os, complex c)
{
    os << "(" << c.re << "+" << c.im << "i)";
    return os;
}


istream& operator>>(istream& is, complex& c)
{
    is >> c.re >> c.im;
    return is;
}

QString& operator <<(QString& string, complex r){
    string += QString::number(r.re);
    string += "+";
    string += QString::number(r.im);
    return string;
}

complex abs(const complex& r) {
    return complex(sqrt(r.re*r.re + r.im * r.im));
}





