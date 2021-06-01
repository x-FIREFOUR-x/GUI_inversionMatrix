#ifndef MATRIX_H
#define MATRIX_H


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
class Matrix
{
    //int size;				// розмір матриці
    int size_line;			// кількість рядків матриці
    int size_column;		// кількість стовбців матриці
    float** ptr_matrix;		// покажчик на матрицю


public:
    static int count;

    Matrix(int);			// конструктор квадратної матриці
    Matrix(int, int);		// конструктор довільної матриці
    ~Matrix();				// деструктор
    Matrix(const Matrix&);	// конструктор копіювання

    void set_element(int line, int column, float date);         // встановити значення елемента матриці
    float get_element(int line, int column);                    // отримати значення елемента матриці

    void round_matrix(int);         // заокруглити елементи матриці

    float determinant();                            // отримання визначника матриці
    Matrix Gauss();                                 // обернення матриці методом Гауса
    Matrix div_cells(bool& possibility_work, int& level_recursion);       // обернення матриці методом розбиття на клітинки

    Matrix inversion_order2(Matrix);				// обернення матриці порядку 2
    Matrix inversion_order1(Matrix);				// обернення матриці порядку 1

    Matrix operator-(const Matrix);         // перевизначення оператора віднімання (від матриці відняти матрицю)
    Matrix operator+(const Matrix);         // перевизначення оператора додавання (до матриці додати матрицю)
    Matrix operator-();                     // перевизначення оператора віднімання (змінити знак матриці)
    Matrix operator=(const Matrix&);        // перевизначення оператора присвоєння (присвоєння матриці матриці)
    Matrix operator*(const Matrix&);		// перевизначення оператора множення (множення матриць)
};
//

#endif // MATRIX_H
