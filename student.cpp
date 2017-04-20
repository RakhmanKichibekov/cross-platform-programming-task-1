
#include "student.h"

Student::Student(){

}

Student::Student(QString last_name, QString first_name, QString parent_name, QString group){
    this->last_name = last_name;
    this->first_name = first_name;
    this->parent_name = parent_name;
    this->group = group;
}


QLinkedList<QString> Student::headers(){
    QLinkedList<QString> list;

    list.append("Фамилия");
    list.append("Имя");
    list.append("Отчество");
    list.append("Группа");

    return list;
}


QLinkedList<QString*> Student::values(){
    QLinkedList<QString*> list;

    list.append(&this->last_name);
    list.append(&this->first_name);
    list.append(&this->parent_name);
    list.append(&this->group);

    return list;
}
