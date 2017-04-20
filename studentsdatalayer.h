#ifndef STUDENTSDATALAYER_H
#define STUDENTSDATALAYER_H

#include <QLinkedList>
#include "student.h"

class StudentsDataLayer
{

private:
    static QLinkedList<Student> data;

public:
    static const int LOAD_SUCCESS = 0;
    static const int LOAD_ERROR_OPEN = 1;
    static const int LOAD_ERROR_FORMAT = 2;

    static const int SAVE_SUCCESS = 0;
    static const int SAVE_ERROR_OPEN = 1;

    static QLinkedList<Student> getData();
    StudentsDataLayer();
    static int load();
    static int save();
    static void add(Student item);
    static void update(int row, int column, QString value);
    static int remove(int index);
};

#endif // STUDENTSDATALAYER_H
