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

        bool is_digit = true;
        for (int i =0; i < str_size.length(); i++)
        {
            if (!(str_size[i].isDigit()))
            {
                is_digit = false;
            }
        }

        if (str_size.toInt() >= 0  && is_digit && str_size != "" )
        {
            int size = str_size.toInt();
            for (int i = 0; i < size; i++ )
            {
                for (int j =0; j < size; j++ )
                {
                    QString number = QString::number(rand()%101 - 50);
                    ui->tableWidget -> setItem(i,j, new QTableWidgetItem(number));
                }
            }
        }
        else
        {
            QMessageBox:: warning(this, "Помилка", "Введіть розмір матриці");
        }
}

