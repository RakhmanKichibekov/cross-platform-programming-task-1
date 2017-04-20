#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student.h"
#include <QMainWindow>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init_headers(QLinkedList<QString> headers);
    void add_row(QLinkedList<QString*> values);
    void init_data(QLinkedList<Student> students);

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
