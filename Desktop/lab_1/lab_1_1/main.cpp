
#include <iostream>
#include "application.h"

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    // вызов приложения
    Application app;
    app.exec();
}
