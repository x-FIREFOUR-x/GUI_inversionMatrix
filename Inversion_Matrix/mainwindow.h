#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include <QLabel>
#include <cmath>
#include "matrix.h"
#include <QFileDialog>
#include <fstream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_lineEdit_textChanged(const QString &arg1);      // введення розміра матриці і створення таблиці для ввода матриці

    void on_pushButton_clicked();       // генерації випадкової матриці

    void on_pushButton_2_clicked();     // обернення матриці

    void on_action_3_triggered();       // вихід з програми

    void on_action_triggered();         // зберегти файл

    void on_action_2_triggered();       // відкрити файл

private:
    Ui::MainWindow *ui;
    QString file_name;              // імя файла

public:
    bool check_correct_size();
    bool check_correct_limits();
    bool check_correct_input_matrix();
    bool check_correcr_len_round();

};
#endif // MAINWINDOW_H
