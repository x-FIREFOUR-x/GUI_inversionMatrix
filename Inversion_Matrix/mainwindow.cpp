#include "mainwindow.h"
#include "ui_mainwindow.h"

int Matrix::count = 0;

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

    bool correct_size = check_correct_size();

    if (correct_size)
    {
        ui-> tableWidget -> setRowCount(arg1.toInt());
        ui-> tableWidget -> setColumnCount(arg1.toInt());
        ui-> tableWidget_2 -> setRowCount(0);
        ui-> tableWidget_2 -> setColumnCount(0);
        inversed = false;
    }
    else
    {
        ui-> tableWidget -> setRowCount(0);
        ui-> tableWidget -> setColumnCount(0);
        ui-> tableWidget_2 -> setRowCount(0);
        ui-> tableWidget_2 -> setColumnCount(0);
        inversed = false;
        QMessageBox:: warning(this, "Помилка", "Невірно введений розмір матриці, введіть ціле додатнє число не менше 1 і не більше 100");
    }
}


void MainWindow::on_pushButton_clicked()
{
QString str_size = ui -> lineEdit -> text();
QString str_lim_min = ui -> lineEdit_2 -> text();
QString str_lim_max = ui -> lineEdit_3 -> text();

    bool correct_size = check_correct_size();

    if (correct_size && str_size != "")
    {
        int lim_min, lim_max;
        lim_min = str_lim_min.toInt();
        lim_max = str_lim_max.toInt();

        bool correct_limits = check_correct_limits();

        if (correct_limits)
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
            ui-> tableWidget_2 -> setRowCount(0);
            ui-> tableWidget_2 -> setColumnCount(0);
            inversed = false;
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

     bool correct_size = check_correct_size();

     if (correct_size && str_size != "")            // перевірка коректності розміру
     {
         int size = str_size.toInt();

         bool correct_matrix_date = check_correct_input_matrix();

         if (correct_matrix_date)      // перевірка чи матриця введена коректно
         {
             bool correct_round = check_correcr_len_round();

             if (correct_round)        // перевірка чи коректно введена точність обчислень
             {
                Matrix A = read_matrix(size);

                Matrix::count = 0;
                float det = A.determinant();


                if (det != 0 )      // перевірка чи матрицю можна обернути
                {
                    QString str_round_lengs = ui -> lineEdit_4 -> text();
                    int round_lengs = str_round_lengs.toInt();

                    if (ui -> radioButton -> isChecked())           // чи обертати Гаусом
                    {
                        Matrix B = A.Gauss();

                        B.round_matrix(round_lengs);
                        write_matrix(B, size);

                        inversed = true;
                        stats = Matrix::count;
                        use_method = 1;

                    }
                    else
                        if (ui -> radioButton_2 -> isChecked())         // чи обертати розбиттям на Клітки
                        {
                            bool possibilyty_work;
                            level_recursion = 0;

                            Matrix B = A.div_cells(possibilyty_work, level_recursion);

                            if (possibilyty_work)
                            {
                                B.round_matrix(round_lengs);
                                write_matrix(B, size);
                                inversed = true;
                                stats = Matrix::count;
                                use_method = 2;
                            }
                            else
                            {
                                //QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю методом розбиття на клітки, використайте інший метод");
                                //use_method = 0;

                                level_recursion = 0;
                                Matrix T = A.transponation();
                                Matrix A1 = T * A;
                                Matrix B1 = A1.div_cells(possibilyty_work, level_recursion);
                                Matrix B_i = B1 * T;
                                if (possibilyty_work)
                                {
                                    B_i.round_matrix(round_lengs);
                                    write_matrix(B_i, size);
                                    inversed = true;
                                    stats = Matrix::count;
                                    use_method = 2;
                                }
                                else
                                {
                                    QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю методом розбиття на клітки, використайте інший метод");
                                    use_method = 0;
                                }
                            }
                        }
                        else
                        {
                             QMessageBox:: information(this, "Помилка", "Виберіть метод обернення матриці");
                        }
                }
                else
                {
                    QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю, бо вона є виродженою");
                }
             }
             else
             {
                 QMessageBox:: warning(this, "Помилка", "Введіть кількість знаків після коми");
             }
          }
          else
          {
               QMessageBox:: warning(this, "Помилка", "Не введені елементи матриці, або введені не коректно");
          }
     }
     else
     {
         QMessageBox:: warning(this, "Помилка", "Розмір і матриця не введені");
     }

}





void MainWindow::on_action_3_triggered()
{
   QApplication::quit();
}

void MainWindow::on_action_triggered()
{
    file_name = QFileDialog::getSaveFileName(this, tr("Збереження файла"), "D://", tr("Текстовий файл(*.txt)"));
    MainWindow::write_file();

    if (file_name != "")
    {
         QMessageBox:: information(this, "Збережено", "Файл " + file_name + " успішно збережений" );
    }

}

void MainWindow::on_action_4_triggered()
{
    MainWindow::write_file();
    if (file_name != "")
    {
         QMessageBox:: information(this, "Збережено", "Файл " + file_name + " успішно перезаписаний" );
    }
}

void MainWindow::on_action_2_triggered()
{
    file_name = QFileDialog::getOpenFileName(this, tr("Відкрити файл"), "D://", tr("Текстовий файл(*.txt)"));

    ifstream fin;
    fin.open(file_name.toStdString());
    string cod_im;
    fin >> cod_im;

    if (cod_im == "IM")
    {
        int size;
        fin >> size;
        if (size > 0)
        {
            QString qstr_size = QString::fromUtf8(to_string(size));
            ui -> lineEdit -> setText(qstr_size);
            ui-> tableWidget -> setRowCount(size);
            ui-> tableWidget -> setColumnCount(size);
            string str_element;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    fin >> str_element;
                    if (str_element != "*")
                    {
                        QString element = QString::fromUtf8(str_element);
                        ui -> tableWidget -> setItem(i,j, new QTableWidgetItem(element));
                    }
                    else
                    {
                        ui -> tableWidget -> setItem(i,j, new QTableWidgetItem(""));
                    }
                }
            }

            ui-> tableWidget_2 -> setRowCount(0);
            ui-> tableWidget_2 -> setColumnCount(0);

            string is_inversed;
            fin >> is_inversed;
            if (is_inversed == "Inversed")
            {
               inversed = true;

                ui-> tableWidget_2 -> setRowCount(size);
                ui-> tableWidget_2 -> setColumnCount(size);

                for (int i = 0; i < size; i++)
                {
                    for (int j = 0; j < size; j++)
                    {
                        fin >> str_element;
                        if (str_element != "*")
                        {
                            QString element = QString::fromUtf8(str_element);
                            ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(element));
                        }
                        else
                        {
                            ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(""));
                        }
                    }
                }
            }
        }
        else
            if (size == 0)
            {
                ui -> lineEdit -> setText("");
                ui-> tableWidget -> setRowCount(size);
                ui-> tableWidget -> setColumnCount(size);
                ui-> tableWidget_2 -> setRowCount(size);
                ui-> tableWidget_2 -> setColumnCount(size);
            }
        QMessageBox::information(this, "Відкрито", "Файл " + file_name + " успішно відкритий");
    }
    else
        if (file_name != "")
        {
            QMessageBox::warning(this, "Неможливо відкрити", "Файл " + file_name + " не вдалося відкрити, імовірно він не є файлом даної програми");
            file_name = "";
        }
    fin.close();
}

void MainWindow::on_action_5_triggered()
{
    QString qstr_stats = QString::number(stats);
    QString qstr_level = QString::number(level_recursion);
    switch (use_method)
    {
        case 0:
                QMessageBox:: information(this, "Не здійснено обертання", "Ви не обернули жодної матриці тому не можна подивитися статистику роботи метода");
                break;
        case 1:
                QMessageBox:: about(this, "Статистика", "Метод Гауса\nКількість ітерацій: " + qstr_stats + "\n" );
                break;
        case 2:
                QMessageBox:: about(this, "Статистика", "Метод розбиття на клітки\nГлибина рекурсії: " + qstr_level + "\n" + "Кількість ітерацій: " + qstr_stats  + "\n"  );
                break;
    }

}



bool MainWindow::check_correct_size()
{
    bool correct;

    QString str_size =  ui -> lineEdit -> text();
    bool is_digit = true;
    for (int i =0; i < str_size.length(); i++)
    {
        if (!(str_size[i].isDigit()))
        {
            is_digit = false;
        }
    }
   int size = str_size.toInt();
   if ((is_digit && size > 0 && size <= 100)|| str_size == "")
   {
        correct = true;
   }
   else
   {
       correct = false;
   }

   return correct;
}

bool MainWindow::check_correct_limits()
{
    bool correct;

    QString str_lim_min = ui -> lineEdit_2 -> text();
    QString str_lim_max = ui -> lineEdit_3 -> text();

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

    int lim_min = str_lim_min.toInt();
    int lim_max = str_lim_max.toInt();

    if (is_digit_lims && str_lim_min != ""  && str_lim_max != "" && lim_min <= lim_max)
    {
        correct = true;
    }
    else
    {
        correct = false;
    }


    return correct;
}

bool MainWindow::check_correct_input_matrix()
{
    bool correct;

    QString str_size = ui -> lineEdit -> text();
    int size = str_size.toInt();
    bool corect_date = true;
    bool is_empty = false;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (ui -> tableWidget -> item(i,j) == NULL)
            {
                is_empty = true;
            }
        }
    }

    if (!is_empty)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j =0; j < size; j++)
            {
                QString element = "";
                element = ui -> tableWidget -> item(i,j) -> text();
                int num_point = 0;
                int num_minus = 0;
                for (int z = 0; z < element.length();z++ )
                {
                    if (element[z] == '.')
                    {
                        num_point++;
                    }
                    if (element[z] == '-')
                    {
                        num_minus++;
                    }
                }
                for (int k = 0; k < element.length() ; k++)
                {
                    if (element.length() >=2 && k == 0)
                    {
                        if ( !(( element[k] == '-' && element[k+1].isDigit() && num_minus == 1) || (element[k].isDigit() )) )
                        {
                             corect_date = false;
                        }

                    }
                    if (element.length() >=3 && k > 0 && k < element.length()- 1)
                    {
                            if ( !((element[k] == '.' && element[k-1].isDigit() && element[k+1].isDigit() && num_point == 1 ) || (element[k].isDigit() )) )
                            {
                                corect_date = false;
                            }
                    }
                    if (element.length() == 1 || k == element.length() -1 )
                    {
                        if ( !( element[k].isDigit()))
                        {
                            corect_date = false;
                        }
                    }

                }

            }

        }
    }

    if (!is_empty && corect_date)
    {
        correct = true;
    }
    else
    {
        correct = false;
    }

    return correct;
}

bool MainWindow::check_correcr_len_round()
{
    bool correct;

    QString str_round_lengs = ui -> lineEdit_4 -> text();
    bool digit_round = true;
    for (int i = 0; i < str_round_lengs.length(); i++)
    {
        if (!str_round_lengs[i].isDigit())
        {
            digit_round = false;
        }
    }

    if (digit_round && str_round_lengs != "")
    {
        correct = true;
    }
    else
    {
        correct = false;
    }
    return correct;
}




Matrix MainWindow::read_matrix(int size)
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

     return A;
 }

void MainWindow::write_matrix(Matrix A, int size)
 {
     ui-> tableWidget_2 -> setRowCount(size);
     ui-> tableWidget_2 -> setColumnCount(size);

     QString number;

     for (int i =0; i < size ; i++ )
     {
         for (int j = 0; j < size; j++)
         {
             number = QString::number(A.get_element(i,j));
             ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(number));
         }
     }
 }

void MainWindow::write_file()
{
    ofstream fout;
    fout.open(file_name.toStdString());

    fout << "IM" << "\n";
    int size = ui-> tableWidget -> rowCount();

    if (size == 0)
    {
       fout << size << "\n";
    }

    if (size > 0)
    {
       fout << size << "\n";

        for(int i =0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (ui -> tableWidget -> item(i, j) != NULL && ui -> tableWidget -> item(i, j) -> text() != "")
                {
                    if (j != 0)
                    {
                        fout << " " << ui -> tableWidget -> item(i, j) -> text().toStdString();
                    }
                    else
                    {
                       fout << ui -> tableWidget -> item(i, j) -> text().toStdString();
                    }
                }
                else
                {
                    if (j != 0)
                    {
                       fout << " " << "*";
                    }
                    else
                    {
                        fout << "*";
                    }
                }
            }
           fout << "\n";
        }

        if (inversed)
        {
           fout << "Inversed" << "\n";

            for(int i =0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (ui -> tableWidget_2 -> item(i, j) != NULL && ui -> tableWidget_2 -> item(i, j) ->text() != "")
                    {
                        if (j != 0)
                        {
                           fout << " " << ui -> tableWidget_2 -> item(i, j) -> text().toStdString();
                        }
                        else
                        {
                           fout << ui -> tableWidget_2 -> item(i, j) -> text().toStdString();
                        }
                    }
                    else
                    {
                        if (j != 0)
                        {
                            fout << " " << "*";
                        }
                        else
                        {
                            fout << "*";
                        }
                    }
                }
                fout << "\n";
            }
        }
        else
        {
           fout << "noInversed";
        }

    }
    fout.close();
}







