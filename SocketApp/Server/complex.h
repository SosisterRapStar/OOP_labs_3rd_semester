#ifndef COMPLEX_H
#define COMPLEX_H

#include<QString>
#include<iostream>
const QString COMPLEX_SEPARATOR("+");

using namespace std;
class complex
{
    double re, im;
public:
    complex();
    complex(const double&, const double&);
    complex(const double&);
    complex(const QString&);
    complex operator+ (complex);
    complex operator* (complex);
    complex operator- (complex);
    complex operator/ (complex);
    complex operator- ();
    bool operator!= (complex);
    bool operator != (double);
    bool operator==(double);
    bool operator==(complex);
    complex operator+= (complex);
    friend ostream& operator <<(ostream&, complex);
    friend istream& operator >>(istream&, complex&);
    friend QString& operator <<(QString&, complex);
    friend complex abs(const complex& r);

};

#endif // COMPLEX_H
