#ifndef MATRIX_H
#define MATRIX_H


#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Matrix
{
    //int size;				// розмір матриці
    int size_line;			// кількість рядків матриці
    int size_column;		// кількість стовбців матриці
    float** ptr_matrix;		// покажчик на матрицю


public:
    Matrix(int);			// конструктор квадратної матриці
    Matrix(int, int);		// конструктор довільної матриці
    ~Matrix();				// деструктор
    Matrix(const Matrix&);	// конструктор копіювання
    void set_element(int line, int column, float date);
    float get_element(int line, int column);

    void random(int min, int max);		// випадкова генерація елементів матриці

    float determinant();		// отримання визначника матриці
    Matrix Gauss();				// обернення матриці методом Гауса
    Matrix div_cells(bool& possibility_work);			// обернення матриці методом розбиття на клітинки

    static Matrix inversion_order2(Matrix);				// обернення матриці порядку 2
    static Matrix inversion_order1(Matrix);				// обернення матриці порядку 1

    Matrix operator-(const Matrix);
    Matrix operator+(const Matrix);
    Matrix operator-();
    Matrix operator=(const Matrix&);
    Matrix operator*(const Matrix&);		// множення матриць
};


#endif // MATRIX_H
