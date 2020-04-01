#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <iostream>
#include <algorithm>
#include <QVector>
#include <studentinfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    QVector<student>studentInfo;
    void find(int i,QStandardItemModel  *model,QVector<student>::iterator it);

private slots:

    void on_find_button_clicked();

    void on_modify_button_clicked();

    void on_add_button_clicked();

    void on_display_button_clicked();

    void on_delete_button_clicked();

    void on_sort_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
