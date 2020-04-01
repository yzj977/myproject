#ifndef STUDENTINFO_H
#define STUDENTINFO_H
#include <QMainWindow>
class student{
    public:
            QString name;
            QString number;
            QString sex;
            int math,english,chinese;
            student(QString,QString,QString,int,int,int);
            student();
            ~student(){};
            bool check();
};

#endif // STUDENTINFO_H
