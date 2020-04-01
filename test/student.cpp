#include "mainwindow.h"

student::student()
{
    this->name=this->number=this->chinese=this->math=this->english=NULL;
    this->sex="";
}

student::student(QString name,QString number,QString sex,int chinese,int math,int english)
{
    this->name=name;
    this->sex=sex;
    this->number=number;
    this->chinese=chinese;
    this->math=math;
    this->english=english;
}

bool student::check(){
    if(sex==""||math==NULL||name==NULL||number==NULL||chinese==NULL||english==NULL)
        return false;
    else
        return true;
}
