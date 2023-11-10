#include "squarematrix.h"


SquareMatrix::SquareMatrix(int size) : Matrix(size, size)
{

}


number SquareMatrix::getDeterminant(number** matrix, int size) {
    if (size == 2) {
        number detForTwo = getDeterminantMatrixOfSizeTwo(matrix);
        deleteMatrix(matrix, size);
        return detForTwo;
    }
    number determinant = 0;
    number sign = 1;
    for (int i = 0; i < size; i++) {
        number** minor = findMinor(matrix, i, size - 1, 0);
        determinant = determinant + (matrix[0][i] * sign) * getDeterminant(minor, size - 1);
        //        cout << fixed << setprecision(2) << determinant << '\n'; // промежуточный вывод
        sign = -sign;
    }
    if (size != column) {
        deleteMatrix(matrix, size);
    }
    return determinant;
}



number** SquareMatrix::findMinor(number** matrix, int columnOriginMat, int size, int minorRow) {
    //    cout << "\nCreatedMinor\n"; // промежуточный вывод
    number** minor = new number * [size];
    for (int i = 0; i < size; i++) {
        minor[i] = new number[size];
    }
    int currentRowInMinor = 0;
    for (int row = 0; row < size + 1; row++) {
        if (minorRow != row) {
            int currentColumnInMinor = 0;
            for (int column = 0; column < size + 1; column++) {
                if (column != columnOriginMat) {
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


// считает определитель матрицы второго порядка
number SquareMatrix::getDeterminantMatrixOfSizeTwo(number * *matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

number SquareMatrix::getDet() {
    return getDeterminant(matrix, column);
}


void SquareMatrix::deleteMatrix(number** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

