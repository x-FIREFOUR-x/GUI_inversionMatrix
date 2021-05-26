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

    bool correct_size = check_correct_size();

    if (correct_size)
    {
        ui-> tableWidget -> setRowCount(arg1.toInt());
        ui-> tableWidget -> setColumnCount(arg1.toInt());
    }
    else
    {
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

             if (det != 0 )                     // перевірка чи матрицю можна обернути
             {
                QString str_round_lengs = ui -> lineEdit_4 -> text();
                bool digit_round = true;
                for (int i = 0; i < str_round_lengs.length(); i++)
                {
                    if (!str_round_lengs[i].isDigit())
                    {
                        digit_round = false;
                    }
                }

                if (digit_round && str_round_lengs != "")       // перевірка чи коректно введена точність обчислень
                {
                    int round_lengs = str_round_lengs.toInt();
                    if (ui -> radioButton -> isChecked())           // чи обертати Гаусом
                    {

                         Matrix B = A.Gauss();
                         for (int i =0; i < size ; i++ )
                         {
                             for (int j = 0; j < size; j++)
                             {
                                 float num = round(B.get_element(i, j) * pow(10,round_lengs)) / pow(10,round_lengs) ;
                                 QString number = QString::number(num);
                                 ui-> tableWidget_2 -> setRowCount(size);
                                 ui-> tableWidget_2 -> setColumnCount(size);
                                 ui -> tableWidget_2 -> setItem(i,j, new QTableWidgetItem(number));
                             }
                         }
                    }
                    else
                        if (ui -> radioButton_2 -> isChecked())         // чи обертати розбиттям на Клітки
                        {
                            bool possibilyty_work;
                            Matrix B = A.div_cells(possibilyty_work);
                            if (possibilyty_work)
                            {
                                for (int i =0; i < size ; i++ )
                                {
                                    for (int j = 0; j < size; j++)
                                    {
                                        float num = round(B.get_element(i, j) * pow(10,round_lengs)) / pow(10,round_lengs) ;
                                        QString number = QString::number(num);
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
                        else
                        {
                             QMessageBox:: information(this, "Помилка", "Виберіть метод обернення матриці");
                        }
                }
                else
                {
                    QMessageBox:: warning(this, "Помилка", "Введіть кількість знаків після коми");
                }
             }
             else
             {
                 QMessageBox:: information(this, "Неможливо виконанати обернення", "Не можливо обернути дану матрицю, бо вона є виродженою");
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
    QMessageBox::information(this, "",file_name);

    QString str_size =  ui -> lineEdit -> text();
    ofstream fin;
    fin.open(file_name.toStdString());
}


void MainWindow::on_action_2_triggered()
{

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
                for (int k = 0; k < element.length() ; k++)
                {
                  if ( !((k == 0 && element[k] == '-') || element[k].isDigit() || (element[k] == '.')) )
                  {
                      corect_date = false;
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
