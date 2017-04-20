#ifndef STUDENT_H
#define STUDENT_H
#include <QLinkedList>
#include <QString>

class Student
{
private:
    QString first_name,
            last_name,
            parent_name,
            group;
public:
    Student();
    Student(QString first_name, QString last_name, QString parent_name, QString group);
    static QLinkedList<QString> headers();
    QLinkedList<QString*> values();
};

#endif // STUDENT_H
