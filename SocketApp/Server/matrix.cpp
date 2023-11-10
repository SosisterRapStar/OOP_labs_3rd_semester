#include "matrix.h"
#include <iostream>
#include "number.h"
using namespace std;



Matrix::~Matrix() {
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;


}
// создание стандартной матрицы по заданному размеру
Matrix::Matrix(int row, int column)
{
    this->row = row;
    this->column = column;
    matrix = new number * [row];
    // инициализация изначального массива
    for (int i = 0; i < row; i++) {
        matrix[i] = new number[column];
    }

    // создание дефолтной матрицы
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            matrix[r][c] = 1;
        }
    }

}

// транспонирование матрицы
void Matrix::matrixTransporn() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            cout << matrix[c][r] << '\t';
        }
        cout << '\n';
    }
}


// создает миноры матрицы для определителя


int Matrix::getRank() {
    return rank_by_gaussian_transformation();
}

void Matrix::setMatrixByArray(number** valueArray){
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = new number* [row];
    for(int i = 0; i < row; i++){
        matrix[i] = new number [column];
    }
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            matrix[r][c] = valueArray[r][c];
        }
    }
}


int Matrix::rank_by_gaussian_transformation() {
    // создание копии матрицы
    number** copy_matrix = new number * [row];

    for (int i = 0; i < row; i++) {
        copy_matrix[i] = new number[column];
    }

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            copy_matrix[r][c] = matrix[r][c];
        }
    }


    int row_step_counter = 0;// сдвиг по строкам
    int col_step_counter = 0;// сдвиг по столбцам
    bool skip_null_col = false; // является ли столбец нулевым и нужно ли его пропускать
    for (int r = 0; r < row - 1 && col_step_counter < column; r += 1 ? !skip_null_col: 0){
        skip_null_col = false;

        if (copy_matrix[r][col_step_counter] == 0) {
            int not_null_row = -1;
            for (int r = row_step_counter; r < row; r++) {
                if (copy_matrix[r][col_step_counter] != 0) {
                    not_null_row = r;
                    break;
                }
            }
            if (not_null_row == -1) {
                skip_null_col = true;
                col_step_counter += 1;
                continue;
            }
            else {

                for (int c = 0; c < column; c++) {
                    number swap_num = copy_matrix[r][c];
                    copy_matrix[not_null_row][c] = copy_matrix[r][c];
                    copy_matrix[not_null_row][c] = swap_num;
                }
            }

        }
        number first_el = copy_matrix[r][col_step_counter];
        for (int i = r + 1; i < row; i++) {
            number sign;
            number curr_first;
            if (copy_matrix[i][col_step_counter] != 0) {
                sign = (copy_matrix[i][col_step_counter] / abs(copy_matrix[i][col_step_counter]));
                curr_first = abs(copy_matrix[i][col_step_counter]);
            }
            else {
                curr_first = 0;
                sign = 0;
            }
            for (int j = col_step_counter; j < column; j++) {
                copy_matrix[i][j] += sign * (-1) * (copy_matrix[r][j] / first_el) * curr_first;
            }
        }
        row_step_counter += 1;
        col_step_counter += 1;

    }
    number row_sum;
    int rank = 0;
    for (int r = 0; r < row; r++) {
        row_sum = 0;
        for (int c = 0; c < column; c++) {
            cout << copy_matrix[r][c] << " ";
            row_sum += copy_matrix[r][c];
        }
        if (row_sum != 0) {
            rank += 1;
        }
        cout << '\n';
    }

    for (int i = 0; i < row; i++) {
        delete[] copy_matrix[i];
    }
    delete[] copy_matrix;

    return rank;
}




void Matrix::getMatrix() {
    cout << "|--|Matrix|--|\n";
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            cout << matrix[r][c];
            cout << "\t";
        }
        cout << '\n';
    }
}

bool Matrix::setUserMatrix() {
    cout << "Enter your matrix values\n\n";
    number value;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            cout << "MatrixSymbol " << r + 1 << " " << c + 1 << " : ";
            cin >> value;
            matrix[r][c] = value;
        }
        cout << "Row " << row + 1 << " filled\n\n";
    }
    return true; // Если все прошло нормально
}



