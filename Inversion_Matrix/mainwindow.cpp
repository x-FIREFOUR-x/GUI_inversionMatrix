#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
bool is_digit = true;
    for (int i =0; i < arg1.length(); i++)
    {
        if (!(arg1[i].isDigit()))
        {
            is_digit = false;
        }
    }

    if ((arg1.toInt() >= 0 || arg1 == "") && is_digit )
    {
        ui-> tableWidget -> setRowCount(arg1.toInt());
        ui-> tableWidget -> setColumnCount(arg1.toInt());
    }
    else
    {
        QMessageBox:: warning(this, "Помилка", "Невірно введений розмір матриці, введіть ціле додатнє число");
    }
}


void MainWindow::on_pushButton_clicked()
{
QString str_size = ui -> lineEdit -> text();
QString str_lim_min = ui -> lineEdit_2 -> text();
QString str_lim_max = ui -> lineEdit_3 -> text();

    bool is_digit = true;
    for (int i =0; i < str_size.length(); i++)
    {
        if (!(str_size[i].isDigit()) )
        {
            is_digit = false;
            break;
        }
    }

    bool is_digit_lims = true;
    for (int i =0; i < str_lim_min.length(); i++)
    {
        if (!((str_lim_min[i].isDigit()) || (i == 0 && str_lim_min[i] == '-' && str_lim_min.length() > 1 ) ))
        {
            is_digit_lims = false;
            break;
        }
    }
    if (is_digit_lims)
        for (int i =0; i < str_lim_max.length(); i++)
        {
            if (!((str_lim_max[i].isDigit()) || (i == 0 && str_lim_max[i] == '-' && str_lim_max.length() > 1 ) ))
            {
                is_digit_lims = false;
                break;
            }
        }

    if (str_size.toInt() >= 0  && is_digit && str_size != "" )
    {
        int lim_min, lim_max;
        lim_min = str_lim_min.toInt();
        lim_max = str_lim_max.toInt();

        if (is_digit_lims && str_lim_min != ""  && str_lim_max != "" && lim_min <= lim_max)
        {
            int size = str_size.toInt();
            for (int i = 0; i < size; i++ )
            {
                for (int j =0; j < size; j++ )
                {
                    QString number = QString::number(rand()%(lim_max - lim_min + 1) + lim_min);
                    ui->tableWidget -> setItem(i,j, new QTableWidgetItem(number));
                }
            }
        }
        else
        {
            QMessageBox:: warning(this, "Помилка", "Введіть діапазон генерації значень елементів матриці (цілі числа)");
        }

    }
    else
    {
        QMessageBox:: warning(this, "Помилка", "Введіть розмір матриці");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString str_size = ui -> lineEdit -> text();

        bool is_digit = true;
        for (int i =0; i < str_size.length(); i++)
        {
            if (!(str_size[i].isDigit()) )
            {
                is_digit = false;
                break;
            }
        }

     if (str_size.toInt() > 0  && is_digit )
     {
         int size = str_size.toInt();
         bool corect_date = true;
         for (int i = 0; i < size; i++)
         {
             for (int j =0; j < size; j++)
             {
                 QString element = ui -> tableWidget -> item(i,j) -> text();
                 for (int k = 0; k < element.length() ; k++)
                 {
                   if ( !((k == 0 && element[k] == '-') || element[k].isDigit() || (element[k] == '.')) )
                   {
                       corect_date = false;
                   }
                 }
             }
         }
         if (corect_date)
         {
             Matrix A(size);
             for (int i = 0; i < size; i++)
             {
                 for (int j = 0; j < size ; j++ )
                 {
                     float elem = (ui -> tableWidget -> item(i,j) -> text()).toFloat();
                     A.set_element(i, j, elem);
                 }
             }

             float det = A.determinant();
             if (det != 0 )
             {
                if (ui -> radioButton -> isChecked())
                {

                     Matrix B = A.Gauss();
                     for (int i =0; i < size ; i++ )
                     {
                         for (int j = 0; j < size; j++)
                         {
                             QString number = QString::number(B.get_element(i, j));
                             ui-> tableWidget_2 -> setRowCount(size);
                             ui-> tableWidget_2 -> setColumnCount(size);
                             ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(number));
                         }
                     }
                }
                else
                {
                    bool possibilyty_work;
                    Matrix B = A.div_cells(possibilyty_work);
                    if (possibilyty_work)
                    {
                        for (int i =0; i < size ; i++ )
                        {
                            for (int j = 0; j < size; j++)
                            {
                                QString number = QString::number(B.get_element(i, j));
                                ui-> tableWidget_2 -> setRowCount(size);
                                ui-> tableWidget_2 -> setColumnCount(size);
                                ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(number));
                            }
                        }
                    }
                    else
                    {
                         QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю методом розбиття на клітки, використайте інший метод");
                    }

                }
             }
             else
             {
                 QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю, бо вона є виродженою");
             }
          }
          else
          {
               QMessageBox:: warning(this, "Помилка", "Некоректно введені дані");
          }
     }
     else
     {
         QMessageBox:: warning(this, "Помилка", "Початкова матриця не введена");
     }

}

