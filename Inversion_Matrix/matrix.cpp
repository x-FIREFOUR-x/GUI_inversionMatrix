#include "matrix.h"

Matrix::Matrix(int size)
{
    size_line = size;			// присвоєння значення кількості рядків
    size_column = size;		// присвоєння значення кількості стовбців

    ptr_matrix = new float* [size_line];		// виділення пам'яті для матриці
    for (int i = 0; i < size_line; i++)
        ptr_matrix[i] = new float[size_column];
}
Matrix::Matrix(int line, int column)
{
    size_line = line;			// присвоєння значення кількості рядків
    size_column = column;		// присвоєння значення кількості стовбців

    ptr_matrix = new float* [size_line];		// виділення пам'яті для матриці
    for (int i = 0; i < size_line; i++)
        ptr_matrix[i] = new float[size_column];
}
Matrix::~Matrix()
{
    for (int i = 0; i < size_line; i++)
        delete[]ptr_matrix[i];
    delete[]ptr_matrix;
}
Matrix::Matrix(const Matrix& origin)
{
    size_line = origin.size_line;
    size_column = origin.size_column;

    ptr_matrix = new float* [size_line];
    for (int i = 0; i < size_line; i++)
        ptr_matrix[i] = new float[size_column];

    for (int i = 0; i < size_line; i++)
    {
        for (int j = 0; j < size_column; j++)
        {
            ptr_matrix[i][j] = origin.ptr_matrix[i][j];
        }
    }

}

void  Matrix::set_element(int line, int column, float date)
{
    ptr_matrix[line][column] = date;
}
float  Matrix::get_element(int line, int column)
{
    return ptr_matrix[line][column];
}

 void Matrix::round_matrix(int round_lengs)
 {
     for(int i = 0; i < size_line; i++)
     {
         for (int j = 0; j <size_column; j++)
         {
            ptr_matrix[i][j] = (round(ptr_matrix[i][j] * pow(10,round_lengs))) / pow(10,round_lengs) ;
         }
     }
 }


float Matrix::determinant()
{
    if (size_line == size_column)
    {
        float determinant = 1;

        Matrix A = *this;
        float c_det = 1;   // коефіцієнт на який потрібно домножити визначник, внаслідок елементарних перетворень він може змінюватися

        for (int i = 0; i < size_line; i++)
        {
            if (A.ptr_matrix[i][i] == 0)			// заміна рядків місцями якщо там 0
            {
                int number = i;		// номер підходящого рядка
                for (int k = i; k < size_line; k++)		// пошук підходящого рядка
                {
                    Matrix::count++;
                    if (A.ptr_matrix[k][i] != 0)
                    {
                        number = k;
                        break;
                    }
                }
                if (number == i)
                {
                    determinant = 0;
                    break;
                }
                Matrix::count++;
                float* temp;
                temp = A.ptr_matrix[i];
                A.ptr_matrix[i] = A.ptr_matrix[number];
                A.ptr_matrix[number] = temp;

                c_det *= -1;
            }

            float coef = A.ptr_matrix[i][i];		// коефіцієнт на який потрібно ділити всі елементи рядка матриці для перетворення елем. гол. діагоналі на одиниці
            c_det *= coef;
            for (int j = 0; j < size_column; j++)		// стовбці (елем рядка i) які теж перебразуються коли роблять 1 на діаг
            {
                A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
                Matrix::count++;
            }

            for (int k = i + 1; k < size_line; k++)	// рядок від якого віднімають
            {
                float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль (щоб під гол діаг стали нулі)
                for (int z = 0; z < size_column; z++)		// стовбці (елементи рядків k, i )
                {
                    A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z] * n);
                    Matrix::count++;
                }

            }
        }

        for (int i = 0; i < size_line; i++)			// обрахунок визначник як добутка елем гол діагоналі зведеної до трикутної матриці
        {
            determinant *= A.ptr_matrix[i][i];
            Matrix::count++;
        }
        determinant *= c_det;
        Matrix::count++;

        return determinant;
    }
    else
    {
        return 0;
    }
}

Matrix Matrix::Gauss()
{
    if (size_line == size_column)
    {
        Matrix A = *this;						// створення обєкта копії вхідної матриці

        int size = size_line;		// вхідна матриця повинна бути квадратною
        Matrix E(size);							// одинична матриця яка стане оберненою до даної
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Matrix::count++;
                if (i == j)
                {
                    E.ptr_matrix[i][j] = 1;
                }
                else
                {
                    E.ptr_matrix[i][j] = 0;
                }
            }
        }
        // прямий хід
        for (int i = 0; i < size; i++)		// рядок який віднімають
        {
            if (A.ptr_matrix[i][i] == 0)			// заміна рядків місцями якщо там 0
            {
                int number = i;		// номер підходящого рядка
                for (int k = i; k < size; k++)		// пошук підходящого рядка
                {
                    Matrix::count++;
                    if (A.ptr_matrix[k][i] != 0)
                    {
                        number = k;
                        break;
                    }
                }
                float* temp;
                temp = A.ptr_matrix[i];
                A.ptr_matrix[i] = A.ptr_matrix[number];
                A.ptr_matrix[number] = temp;
                temp = E.ptr_matrix[i];
                E.ptr_matrix[i] = E.ptr_matrix[number];
                E.ptr_matrix[number] = temp;
            }

            float coef = A.ptr_matrix[i][i];		// коефіцієнт на який потрібно ділити всі елементи рядка матриці для перетворення елем. гол. діагоналі на одиниці
            for (int j = 0; j < size; j++)		// стовбці (елем рядка i) які теж перебразуються коли роблять 1 на діаг
            {
                A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
                E.ptr_matrix[i][j] = E.ptr_matrix[i][j] / coef;
                Matrix::count++;
            }

            for (int k = i + 1; k < size; k++)	// рядок від якого віднімають
            {
                float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль (щоб під гол діаг стали нулі)
                for (int z = 0; z < size; z++)		// стовбці (елементи рядків k, i )
                {
                    A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z] * n);
                    E.ptr_matrix[k][z] = E.ptr_matrix[k][z] - (E.ptr_matrix[i][z] * n);
                    Matrix::count++;
                }

            }
        }
        // зворотній хід
        for (int i = size - 1; i >= 0; i--)		// рядок який віднімають
        {
            for (int k = i - 1; k >= 0; k--)		// рядок від якого віднімають
            {
                float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль  (щоб під гол діаг стали нулі)
                for (int z = size - 1; z >= 0; z--)		// стовбці (елементи рядків k, i )
                {
                    A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - A.ptr_matrix[i][z] * n;
                    E.ptr_matrix[k][z] = E.ptr_matrix[k][z] - E.ptr_matrix[i][z] * n;
                    Matrix::count++;
                }
            }
        }

        return E;
    }
    else
    {
        return 0;
    }
}
Matrix Matrix::div_cells(bool& possibility_work, int& level_recursion)
{
    level_recursion++;
    possibility_work = true;
    float det = determinant();
    if (size_line == size_column && det !=0)
    {
        Matrix A11(size_line - 1, size_column - 1);		// 4 матриці на які поділені матриця A
        Matrix A12(size_line - 1, 1);
        Matrix A21(1, size_column - 1);
        Matrix A22(1, 1);

        // поділ матриці A на 4 матриці розміром (n-1, n-1) (n-1, 1) (1, n-1) (1, 1)
        for (int i = 0; i < size_line; i++)
        {
            for (int j = 0; j < size_column; j++)
            {
                Matrix::count++;
                if (i < size_line - 1)
                {
                    if (j < size_column - 1)
                    {
                        A11.ptr_matrix[i][j] = ptr_matrix[i][j];
                    }
                    else
                    {
                        A12.ptr_matrix[i][size_column - j - 1] = ptr_matrix[i][j];
                    }
                }
                else
                {
                    if (j < size_column - 1)
                    {
                        A21.ptr_matrix[size_line - i - 1][j] = ptr_matrix[i][j];
                    }
                    else
                    {
                        A22.ptr_matrix[size_line - i - 1][size_column - j - 1] = ptr_matrix[i][j];
                    }
                }
            }
        }

        // умова рекурсії (поділ матриці відділяючи по лівому нижньмо краю на один доки не дійдем до чотирьох матриць роз 1)
        if (A11.size_column > 1)
        {
            Matrix A11_i = A11.div_cells(possibility_work, level_recursion);			// виклик рекурсії для знаходження оберненої до A11 допоки вона не стане розміру 1

            if (possibility_work)			// перевірка можливості здійснення операції
            {
                Matrix X = A11_i * A12;
                Matrix Y = A21 * A11_i;
                Matrix Q = A22 - (Y * A12);

                det = Q.determinant();
                if (det == 0)						// перевірка чи матриця що є частиною основної матриці невироджена, якщо так знайти обернену вхідної цим методом неможливо
                    possibility_work = false;

                if (possibility_work)		// перевірка можливості здійснення операції
                {
                    Matrix Q_i = inversion_order1(Q);

                    Matrix B11(size_line - 1, size_column - 1);		// 4 матриці на які поділена обернена матриця A
                    Matrix B12(size_line - 1, 1);
                    Matrix B21(1, size_column - 1);
                    Matrix B22(1, 1);

                    B11 = A11_i + (X * Q_i * Y);
                    B12 = -(X * Q_i);
                    B21 = -(Q_i * Y);
                    B22 = Q_i;

                    Matrix B(size_line, size_column);		// обернена матриця до A, яка складається з B11, B12, B21, B22

                       // складання матриць частин B до кучі
                    for (int i = 0; i < size_line; i++)
                    {
                        for (int j = 0; j < size_column; j++)
                        {
                            if (i < size_line - 1)
                            {
                                if (j < size_column - 1)
                                {
                                    B.ptr_matrix[i][j] = B11.ptr_matrix[i][j];
                                }
                                else
                                {
                                    B.ptr_matrix[i][j] = B12.ptr_matrix[i][size_column - j - 1];
                                }
                            }
                            else
                            {
                                if (j < size_column - 1)
                                {
                                    B.ptr_matrix[i][j] = B21.ptr_matrix[size_line - i - 1][j];
                                }
                                else
                                {
                                    B.ptr_matrix[i][j] = B22.ptr_matrix[size_line - i - 1][size_column - j - 1];
                                }
                            }
                        }
                    }

                    return B;
                }

            }

            if (!possibility_work)
            {
                return 0;
            }

        }
        else
        {
            float det = A11.determinant();
            if (det == 0)							// перевірка чи матриця що є частиною основної матриці невироджена, якщо так знайти вхідної обернену цим методом неможливо
                possibility_work = false;

            if (possibility_work)						// перевірка можливості здійснення операції
            {
                Matrix A11_i = inversion_order1(A11);
                Matrix X = A11_i * A12;
                Matrix Y = A21 * A11_i;
                Matrix Q = A22 - (Y * A12);

                det = Q.determinant();			// перевірка чи матриця що є частиною основної матриці невироджена, якщо так знайти вхідної обернену цим методом неможливо
                if (det == 0)
                    possibility_work = false;

                if (possibility_work)	// перевірка можливості здійснення операції
                {
                    Matrix Q_i = inversion_order1(Q);

                    Matrix B11(size_line - 1, size_column - 1);		// 4 матриці на які поділена обернена матриця A
                    Matrix B12(size_line - 1, 1);
                    Matrix B21(1, size_column - 1);
                    Matrix B22(1, 1);

                    B11 = A11_i + (X * Q_i * Y);
                    B12 = -(X * Q_i);
                    B21 = -(Q_i * Y);
                    B22 = Q_i;

                    Matrix B(size_line, size_column);		// обернена матриця до A, яка складається з B11, B12, B21, B22

                       // складання матриць частин B до кучі
                    for (int i = 0; i < size_line; i++)
                    {
                        for (int j = 0; j < size_column; j++)
                        {
                            Matrix::count++;
                            if (i < size_line - 1)
                            {
                                if (j < size_column - 1)
                                {
                                    B.ptr_matrix[i][j] = B11.ptr_matrix[i][j];
                                }
                                else
                                {
                                    B.ptr_matrix[i][j] = B12.ptr_matrix[i][size_column - j - 1];
                                }
                            }
                            else
                            {
                                if (j < size_column - 1)
                                {
                                    B.ptr_matrix[i][j] = B21.ptr_matrix[size_line - i - 1][j];
                                }
                                else
                                {
                                    B.ptr_matrix[i][j] = B22.ptr_matrix[size_line - i - 1][size_column - j - 1];
                                }
                            }
                        }
                    }

                    return B;
                }

            }

            if (!possibility_work)
            {
                return 0;
            }

        }


    }
    else
    {
        possibility_work = false;
        return 0;
    }
}

 Matrix Matrix::inversion_order2(Matrix A)
{
     if (A.size_line == A.size_column && A.size_line == 2)
     {
         Matrix B(A.size_line, A.size_column);		// обернена матриці матриці A
         float det = (A.ptr_matrix[0][0] * A.ptr_matrix[1][1]) - (A.ptr_matrix[0][1] * A.ptr_matrix[1][0]);		// визначник матриці A

         B.ptr_matrix[0][0] = A.ptr_matrix[1][1] / det;
         B.ptr_matrix[0][1] = -1 * A.ptr_matrix[0][1] / det;
         B.ptr_matrix[1][0] = -1 * A.ptr_matrix[1][0] / det;
         B.ptr_matrix[1][1] = A.ptr_matrix[0][0] / det;

         return B;
     }
     else
     {
         return 0;
     }
}
 Matrix Matrix::inversion_order1(Matrix A)
 {
     if (A.size_line == A.size_column && A.size_line == 1)
     {
         Matrix B(A.size_line, A.size_column);
         B.ptr_matrix[0][0] = 1 / A.ptr_matrix[0][0];
         Matrix::count += 1;
         return B;
     }
     else
     {
         return 0;
     }
 }

 Matrix Matrix::operator-(const Matrix B)
 {
     Matrix C(size_line, size_column);

     for (int i = 0; i < size_line; i++)
     {
         for (int j = 0; j < size_column; j++)
         {
             Matrix::count += 1;
             C.ptr_matrix[i][j] = ptr_matrix[i][j] - B.ptr_matrix[i][j];
         }
     }

     return C;
 }
 Matrix Matrix:: operator-()
 {
     Matrix C(size_line, size_column);

     for (int i = 0; i < size_line; i++)
     {
         for (int j = 0; j < size_column; j++)
         {
             Matrix::count += 1;
             C.ptr_matrix[i][j] = 0 - ptr_matrix[i][j];
         }
     }
     return C;
 }
 Matrix Matrix::operator+(const Matrix B)
 {
     Matrix C(size_line, size_column);

     for (int i = 0; i < size_line; i++)
     {
         for (int j = 0; j < size_column; j++)
         {
             Matrix::count += 1;
             C.ptr_matrix[i][j] = ptr_matrix[i][j] + B.ptr_matrix[i][j];
         }
     }

     return C;
 }
 Matrix Matrix::operator=(const Matrix& A)
 {
     for (int i = 0; i < size_line; i++)
     {
         for (int j = 0; j < size_column; j++)
         {
             Matrix::count += 1;
             ptr_matrix[i][j] = A.ptr_matrix[i][j];
         }
     }
     return *this;
 }
 Matrix Matrix::operator*(const Matrix& B)
 {
     if (size_column == B.size_line)
     {
         Matrix C(size_line, B.size_column);
         for (int i = 0; i < size_line; i++)
         {
             for (int j = 0; j < B.size_column; j++)
             {
                 float S = 0;
                 for (int k = 0; k < size_column; k++)
                 {
                     Matrix::count += 1;
                     S += ptr_matrix[i][k] * B.ptr_matrix[k][j];
                 }
                 C.ptr_matrix[i][j] = S;
             }
         }
         return C;
     }
     else
     {
         return 0;
     }
 }
Matrix Matrix::transponation()
{
    Matrix A(size_line, size_column);
    for (int i =0; i < size_line; i++ )
    {
        for(int j =0; j < size_column; j++)
        {
            A.ptr_matrix[i][j] = ptr_matrix[j][i];
        }
    }
    return A;
}
