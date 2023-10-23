
#include "number.h"


class Matrix
{
public:
    Matrix();
    Matrix(int size); // создание матрицы заранее заданного размера
    ~Matrix(); //добавлен деструктор
    void getMatrix();
    bool setUserMatrix(int size);
    number getDet();
    void matrixTransporn();
    int getRank();
    void setMatrixByArray(number**); // добавлено задание матрицы по массиву
    bool setMatrixSize(int& size);

private:

    int matrixRank;
    int matrixSize;
    // приватные методы, где осуществляется передача number** matrix служат для вычислений т.к. сам динамический массив постоянно
    // изменяется и в методы передаются разные матрциы разных размеров в ходе рекурсивных вычислений: миноров, ранга матрицы, а также её определителя
    // deleteMatrix существует для удаления всех объектов динамического массива, которые создаются в ходе работы рекурсивных функций
    number** findMinor(number** matrix, int columnOriginMat, int size, int rowOriginMat);
    number getDeterminant(number** matrix, int size);
    number rankSearch(number** matrix, int size);
    number** matrix;
    void setDefaultMatrix();
    number getDeterminantMatrixOfSizeTwo(number** matrix);
    void deleteMatrix(number** matrix, int size);
};
