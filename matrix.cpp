#include "matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

Matrix::Matrix()
{
    matrixRank = 1;
    matrixSize = 5;

    // инициализация изначального массива
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = new number[matrixSize ];
    }

    // создание дефолтной матрицы
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize; column++){
            matrix[row][column] = 1;
        }
    }



}


// считает определитель матрицы второго порядка
number Matrix::getDeterminantMatrixOfSizeTwo(number** matrix){
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}


// транспонирование матрицы
void Matrix::matrixTransporn(){
    for(int row =0; row < matrixSize; row++){
        for(int column =0; column < matrixSize; column++){
            cout << matrix[column][row] << '\t';
        }
        cout << '\n';
    }
}








// создает миноры матрицы для определителя
number** Matrix::findMinor(number** matrix, int columnOriginMat, int size, int minorRow){
//    cout << "\nCreatedMinor\n"; // промежуточный вывод
    number** minor = new number*[size];
    for (int i = 0; i < size; i++) {
        minor[i] = new number[size];
    }
    int currentRowInMinor = 0;
    for(int row = 0; row < size + 1; row++){
        if (minorRow != row){
             int currentColumnInMinor = 0;
             for (int column = 0; column < size + 1; column++){
                if (column != columnOriginMat){
//                    cout << matrix[row][column] << "\t"; // промежуточный вывод
                    minor[currentRowInMinor][currentColumnInMinor] = matrix[row][column];
                    currentColumnInMinor += 1;
                }
             }
             currentRowInMinor += 1;
        }

    }
    return minor;
}

void Matrix::getRank(){
    matrixRank = 1;
    rankSearch(matrix, matrixSize);
    cout << matrixRank;
}


void Matrix::deleteMatrix(number** matrix, int size){
    for (int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}



// вычисление ранга
number Matrix::rankSearch(number** matrix, int size){
    if (size == 2){
        number detForTwo = getDeterminantMatrixOfSizeTwo(matrix);
        if (size != matrixSize){
             deleteMatrix(matrix, size);
        }
        if (detForTwo != 0 and matrixRank < 2){
             matrixRank = 2;
        }
        return detForTwo;
    }

    short sign = 1;
    number determinant = 0;
    for (int row = 0; row < size; row++){
        determinant = 0;
        for(int column = 0; column < size; column++){
            // вычисление минора матрицы
            number** minor = findMinor(matrix, column, size - 1, row);
            // обработка правильного знака для разложения по строке
            sign  = ((row + 1) + (column + 1)) % 2 == 0 ?  1 : -1;
            determinant = determinant + (sign * matrix[row][column]) * rankSearch(minor, size - 1);
        }
        if (determinant != 0 and size > matrixRank){
            matrixRank = size;
        }
        if(matrixSize == matrixRank){
            return 0;
        }
    }
    if (size != matrixSize){
        deleteMatrix(matrix, size);
    }
    return determinant;
}



//  функция нахождения определителя разложением по первой строке
number Matrix::getDeterminant(number** matrix, int size){
    if (size == 2){
        number detForTwo = getDeterminantMatrixOfSizeTwo(matrix);
        deleteMatrix(matrix, size);
        return detForTwo;
    }
    number determinant = 0;
    int sign = 1;
    for (int i = 0; i < size; i++){
        number** minor = findMinor(matrix, i, size - 1, 0);
        determinant = determinant + (sign * matrix[0][i]) * getDeterminant(minor, size - 1);
//        cout << fixed << setprecision(2) << determinant << '\n'; // промежуточный вывод
        sign = -sign;
    }
    if (size != matrixSize){
        deleteMatrix(matrix, size);
    }
    return determinant;
}



// метод который вызывает приватный метод рекурсивного нахождения определителя
number Matrix::getDet(){
    if (matrixSize == 1){
        return matrix[0][0];
    }
    if(matrixSize == 2){
        return getDeterminantMatrixOfSizeTwo(matrix);
    }
    return getDeterminant(matrix, matrixSize);
}


// выводит матрицу на экран
void Matrix::getMatrix(){
    cout << "|--|Matrix|--|\n";
    for (int row = 0; row < matrixSize; row++) {
        for (int column = 0; column < matrixSize; column++) {
            cout << matrix[row][column];
            cout << "\t";
        }
        cout << '\n';
    }
}


// задает значение размера матрицы и проверяет валидность ввода
bool Matrix::setMatrixSize(int &size){

    if (size <= 0){ // проверяет валиден ли ввод
        return false; // ввод неправльный
    }
    deleteMatrix(matrix, matrixSize);
    matrixSize = size; // задает размер для матрицы
    return true; // всё прошло успешно

}


// создает пользовательскую матрицу
bool Matrix::setUserMatrix(int size){
    if (!setMatrixSize(size)){
        return false;  // Если ввод не валиден, то прекращаем работу и даем ответ в виде false
    }
    matrix = new number*[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = new number[matrixSize];
    }
    cout << "Enter your matrix values\n\n";
    number value;
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize; column++){
            cout << "MatrixSymbol " << row + 1 << " " << column + 1<< " : ";
            cin >> value;
            matrix[row][column] = value;
        }
        cout << "Row " << row + 1 << " filled\n\n";
    }
    return true; // Если все прошло нормально
}

