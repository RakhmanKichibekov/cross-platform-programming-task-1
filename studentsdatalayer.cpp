#include "studentsdatalayer.h"
#include <QString>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QDataStream>

QLinkedList<Student> StudentsDataLayer::data;

QLinkedList<Student> StudentsDataLayer::getData(){
    return data;
}

int StudentsDataLayer::load(QString filename = "test.dat"){
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        return LOAD_ERROR_OPEN;
    }

    QLinkedList<Student> loaded_data;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);

    while(!in.atEnd()){
        Student *student = new Student();

        QLinkedList<QString*> values = student->values();
        for(QLinkedList<QString*>::iterator value = values.begin(); value != values.end(); value++){
            in >> **value;
        }

        loaded_data.append(*student);
    }

    data = loaded_data;

    return LOAD_SUCCESS;
}

int StudentsDataLayer::save(QString filename = "test.dat"){
    QFile file(filename);

    QFile::remove(filename);

    if(!file.open(QIODevice::WriteOnly)){
        return SAVE_ERROR_OPEN;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);

    for(QLinkedList<Student>::iterator student = data.begin(); student != data.end(); student++){
        QLinkedList<QString*> values = student->values();

        for(QLinkedList<QString*>::iterator value = values.begin(); value != values.end(); value++){
            out << **value;
        }
    }

    file.flush();
    file.close();

    return SAVE_SUCCESS;
}

void StudentsDataLayer::add(Student item){
    data.append(item);
}

void StudentsDataLayer::update(int row, int column, QString value){
    if(row >= data.count()){
        return;
    }

    if(column >= Student::headers().count()){
        return;
    }


    int i = 0;
    int j = 0;

    for(QLinkedList<Student>::iterator pos = data.begin(); pos != data.end(); pos++){
        if(i == row){
            QLinkedList<QString*> values = pos->values();

            for(QLinkedList<QString*>::iterator field = values.begin(); field != values.end(); field++){
                if(j == column){
                    **field = value;
                    return;
                }
                ++j;
            }
            return;
        }

        ++i;
    }
}

int StudentsDataLayer::remove(int index){
    if(index == data.count() - 1){
        data.removeLast();
        return 0;
    }

    QLinkedList<Student>::iterator pos = data.begin();

    int i = 0;

    while(pos != data.end()){
        if(i == index){
            data.erase(pos);
            return 0;
        }

        ++i;
    }

    return 1;
}
