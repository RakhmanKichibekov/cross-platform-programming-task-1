#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include "studentsdatalayer.h"

void MainWindow::init_headers(QLinkedList<QString> headers){
    QLinkedList<QString>::iterator iterator = headers.begin();
    int column = 0;

    ui->tableWidget->setColumnCount(headers.count());

    while(iterator != headers.end()){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(*iterator);
        ui->tableWidget->setHorizontalHeaderItem(column, item);
        ++iterator;
        ++column;
    }
}

void MainWindow::add_row(QLinkedList<QString*> values){
    QLinkedList<QString*>::iterator iterator = values.begin();
    int row = ui->tableWidget->rowCount();
    int column = 0;

    ui->tableWidget->setRowCount(row + 1);

    while(iterator != values.end()){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(**iterator);
        ui->tableWidget->setItem(row, column, item);
        ++iterator;
        ++column;
    }
}

void MainWindow::init_data(QLinkedList<Student> students){
    for(QLinkedList<Student>::iterator student = students.begin(); student != students.end(); student++){
        QLinkedList<QString*> values = student->values();
        add_row(values);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLinkedList<QString> headers = Student::headers();
    init_headers(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    Student *item = new Student();

    StudentsDataLayer::add(*item);

    QLinkedList<QString*> values = item->values();
    add_row(values);
}

void MainWindow::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    int result = StudentsDataLayer::remove(row);

    if(result == 0){
        ui->tableWidget->removeRow(row);
        ui->deleteButton->setEnabled(false);
    }else{
        QMessageBox::critical(this, "Ошибка удаления", "Не удалось удалить строку.");
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    ui->deleteButton->setEnabled(true);
}

void MainWindow::on_saveButton_clicked()
{
    int result = StudentsDataLayer::save();

    if(result == 0){
        QMessageBox::information(this, "Успех!", "Список успешно сохранен.");
    }else{
        QMessageBox::critical(this, "Ошибка сохранения", "Не удалось сохранить список.");
    }
}

void MainWindow::on_loadButton_clicked()
{
    int error = StudentsDataLayer::load();

    if(error == 0){
        ui->tableWidget->setRowCount(0);

        QLinkedList<Student> students = StudentsDataLayer::getData();

        init_data(students);

        QMessageBox::information(this, "Успех!", "Список успешно загружен.");
    }else{
        switch(error){
        case StudentsDataLayer::LOAD_ERROR_OPEN:
        {
            QMessageBox::critical(this, "Ошибка загрузки", "Не удалось открыть файл.");
            break;
        }
        case StudentsDataLayer::LOAD_ERROR_FORMAT:
        {
            QMessageBox::critical(this, "Ошибка загрузки", "Файл поврежден.");
            break;
        }
        default:
        {
            QMessageBox::critical(this, "Ошибка загрузки", "Произошла неизвестная ошибка: #" + error);
        }
        }
    }
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    StudentsDataLayer::update(item->row(), item->column(), item->text());
}
