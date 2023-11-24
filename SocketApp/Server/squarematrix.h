#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H


#include "Matrix.h"
template<class number>
class SquareMatrix : public Matrix<number>
{
public:
    SquareMatrix(int size);
    number getDet();
private:
    number** findMinor(number** matrix, int columnOriginMat, int size, int rowOriginMat);
    number getDeterminant(number** matrix, int size);
    number getDeterminantMatrixOfSizeTwo(number** matrix);
    void deleteMatrix(number** matrix, int size);
};

template<class number>
SquareMatrix<number>::SquareMatrix(int size) : Matrix<number>(size, size)
{

}

template<class number>
number SquareMatrix<number>::getDeterminant(number** matrix, int size) {
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
    if (size != this->column) {
        deleteMatrix(matrix, size);
    }
    return determinant;
}


template<class number>
number** SquareMatrix<number>::findMinor(number** matrix, int columnOriginMat, int size, int minorRow) {
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
template<class number>
number SquareMatrix<number>::getDeterminantMatrixOfSizeTwo(number * *matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

template<class number>
number SquareMatrix<number>::getDet() {
    if (this->column == 2){
        return getDeterminantMatrixOfSizeTwo(this->matrix);
    }
    else if (this->column == 1){
        return this->matrix[0][0];
    }
    return getDeterminant(this->matrix, this->column);
}

template<class number>
void SquareMatrix<number>::deleteMatrix(number** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}







#endif // SQUAREMATRIX_H
