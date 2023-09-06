#include "application.h"
#include <iostream>
#include <vector>
using namespace std;


Application::Application()
{

}

void Application::menu(){
    cout << "==============Matrix================\n";
    cout << "1) Set user matrix\n";
    cout << "2) Calculate determinant\n";
    cout << "3) Transporn matrix\n";
    cout << "4) Calculate matrix rank\n";
    cout << "5) Print matrix\n";
    cout << "6) Exit\n";
    cout << "> ";
}

// ввод матрицы



int Application::exec()
{
    setlocale(LC_ALL, "rus");
    int ch = 0;
    Matrix matrix;
    while(ch != 6)
    {
        menu();
        cin >> ch;
        switch(ch)
        {
        case 1:{
                int size;
                cout << "Enter matrix size\n";
                cin >> size;
                bool isCreated = matrix.setUserMatrix(size);
                if (isCreated){
                    cout << "Matrix sexcessfully created\n";
                    break;
                }
                cout << "Error, matrix were not created...Try again\n";
                break;}
        case 2:{
                cout << "Matrix determinant: " << matrix.getDet() << "\n";
                break;}
        case 3: {
                cout << "Transporned matrix:\n";
                matrix.matrixTransporn();
                break;}
        case 4: {

                cout << "Matrix rank: ";
                matrix.getRank();
                cout << '\n';
                break;}
        case 5:{
                matrix.getMatrix();
                break;}
        case 6:{
                break;}
        default:{
                cout << "There is no such functional...Try again\n";
                break;}
        }
    }
}
