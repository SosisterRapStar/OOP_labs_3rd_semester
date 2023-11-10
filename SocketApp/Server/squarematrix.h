#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include "Matrix.h"

class SquareMatrix : public Matrix
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
#endif // SQUAREMATRIX_H
