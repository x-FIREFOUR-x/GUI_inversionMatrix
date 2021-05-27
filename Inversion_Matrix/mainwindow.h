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
    Ui::MainWindow *ui;             // вказівник на головне меню
    QString file_name;              // ім'я файла
    bool inversed = false;                  // чи користувач опернув матрицю

public:
    bool check_correct_size();              // перевірка чи в lineEdit введене коректне значення(розмір матриці)
    bool check_correct_limits();            // перевірка чи в lineEdit_2 і lineEdit_3 введені коректні значення (межі генерації)
    bool check_correct_input_matrix();      // перевірка чи в TableWidget введена коректно матриця
    bool check_correcr_len_round();         // перевірка чи в lineEdit_4 введене коректне значення (точність заокруглення)

    Matrix read_matrix(int);                // зчитати матрицю з таблиці(GUI) (ввести з екрану)
    void write_matrix(Matrix, int);         // записати матрицю в таблицю (GUI) (вивести на екран)

};
#endif // MAINWINDOW_H
