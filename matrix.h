#ifndef MATRIX_H
#define MATRIX_H
#include "number.h"


class Matrix
{
public:
    Matrix();
    void getMatrix();
    bool setUserMatrix(int size);
    number getDet();
    void getAnyMatrix(number** matrix);
    void matrixTransporn();
    void getRank();


private:
    int matrixRank;
    int matrixSize;
    bool setMatrixSize(int &size);
    number** findMinor(number** matrix, int columnOriginMat, int size, int rowOriginMat);
    number getDeterminant(number** matrix, int size);
    number rankSearch(number** matrix, int size);
    number** matrix = new number*[matrixSize];
    void setDefaultMatrix();
    number getDeterminantMatrixOfSizeTwo(number** matrix);
    void deleteMatrix(number** matrix, int size);
};

#endif // MATRIX_H
