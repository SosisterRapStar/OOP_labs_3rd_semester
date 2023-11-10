
#include "number.h"


class Matrix
{
public:
    Matrix();
    Matrix(int row, int column); // создание матрицы заранее заданного размера
    ~Matrix(); //добавлен деструктор
    void getMatrix();
    bool setUserMatrix();
    void matrixTransporn();
    int getRank();
    void setMatrixByArray(number**); // добавлено задание матрицы по массиву

private:
    int row;
    int rank_by_gaussian_transformation();
protected:
    int column;
    number** matrix;
};
