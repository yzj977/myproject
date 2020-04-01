#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    QStandardItemModel  *model = new QStandardItemModel();  //
    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");    //数据文件对象
    model->setColumnCount(6);   //6列数据
    QTextStream in(file);

    //表头名称
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");

    //设置表头属性
    ui->tableView->setModel(model); //在进行表格设置时必须是“ui->tableView->setModel(model);”
    //在前，属性具体设置在后，反之则设置不会生效
    //表头信息显示居中
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    ui->textBrowser->clear();  //清空

    /*
    ui->tableView->horizontalHeader()->setResizeMode(0,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setResizeMode(1,QHeaderView::Fixed);
    ui->tableView->setColumnWidth(0,101);
    ui->tableView->setColumnWidth(1,102);
    */
    //读取操作
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),"读取文件错误");
        return;
    }
    else{
        while(!in.atEnd()){ //读到文件结尾
                QString name,number,sex;
                int chinese,math, english;
                in >> name >> number >> sex >> chinese >> math >> english;
                studentInfo.push_back(student(name,number,sex,chinese,math,english));
                //调用之前建立的构造函数实例化一个Student对象并将其加入StudentInfo
        }
        int i=0;
        for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
        {
            find(i,model,it);
        }
        //显示多少行（多少学生）
        ui->textBrowser->append("共"+QString::number(i)+"行");
    }

    file->close();
    /*
     * Alignment 参数为int型，1表示左对齐，2表示右对齐，3表示居中
     * Qt::AlignLeft	0x0001	Aligns with the left edge.
       Qt::AlignRight	0x0002	Aligns with the right edge.
       Qt::AlignHCenter	0x0004	Centers horizontally in the available space.
       Qt::AlignJustify	0x0008	Justifies the text in the available space.
     */
}

void MainWindow::find(int i,QStandardItemModel  *model,QVector<student>::iterator it)
{
    model->setItem(i,0,new QStandardItem(it->name));
    //设置字符颜色
    //model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
    //设置字符位置
    model->item(i,0)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,1,new QStandardItem(it->number));
    model->item(i,1)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,2,new QStandardItem(it->sex));
    model->item(i,2)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,3,new QStandardItem(QString::number(it->chinese,10)));
    model->item(i,3)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,4,new QStandardItem(QString::number(it->math,10)));
    model->item(i,4)->setTextAlignment(Qt::AlignCenter);
    model->setItem(i,5,new QStandardItem(QString::number(it->english,10)));
    model->item(i,5)->setTextAlignment(Qt::AlignCenter);
}

void MainWindow::on_find_button_clicked()
{
    QString scanf_num;
    QString scanf_name;
    scanf_num=ui->numberline->text();
    scanf_name=ui->nameline->text();

    ui->textBrowser->clear();

    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(6);   //6列数据
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    int i=0;
    for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
    {
        if((it->name==scanf_name&&it->number==scanf_num)||(it->name==scanf_name&&scanf_num==NULL)
                ||(it->number==scanf_num&&scanf_name==NULL))
        {
            find(i,model,it);
        }
        else
            i--;
    }

    ui->textBrowser->append("共"+QString::number(i)+"行");
}

void MainWindow::on_modify_button_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(6);   //6列数据
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");

    QString sex;
    if(ui->radioman->isChecked())
        sex=QString("男");
    else if(ui->radiowoman->isChecked())
        sex=QString("女");
    student temp(ui->nameline->text(),ui->numberline->text(),sex,ui->chinese_line->text().toInt(),
                 ui->math_line->text().toInt(),ui->english_line->text().toInt()); //学生信息

    bool flag=false;
    QVector<student>::iterator it = studentInfo.begin();
    for(; it != studentInfo.end(); it++){
        if(it->number==temp.number)
        {
            flag=true;
            break;
        }
    }

    ui->textBrowser->clear();
    int i=0;
    if(temp.check()&&flag){
        QTextStream out(file);
        file->open(QIODevice::WriteOnly|QFile::Truncate);   //以重写方式打开文件
        *it=temp;   //对对象进行复制，修改内容
        for(it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
        {
            find(i,model,it);
        }
        //文件更新操作（这两个可合并!）
        for(it = studentInfo.begin(); it != studentInfo.end()-1; it++)
        {
            out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
              <<it->chinese<<"\t"<<it->math<<"\t"<<it->english<<"\n";
        }
        out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
          <<it->chinese<<"\t"<<it->math<<"\t"<<it->english; //最后一行特殊处理（不加换行符）
        file->close();
        //显示多少行（多少学生）
        ui->textBrowser->append("共"+QString::number(i)+"行");
        QMessageBox::information(this,tr("successed!"),"修改成功!");
    }
    else{
        for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
        {
            find(i,model,it);
        }
        //显示多少行（多少学生）
        ui->textBrowser->append("共"+QString::number(i)+"行");
        if(flag)
            QMessageBox::warning(this,tr("错误"),"修改错误!\n请检查输入数据是否合法\n（如:信息为空或不满足规则）");
        else
            QMessageBox::warning(this,tr("错误"),"学号错误!");
    }
}

void MainWindow::on_add_button_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(6);   //6列数据
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");

    QString sex;
    if(ui->radioman->isChecked())
        sex=QString("男");
    else if(ui->radiowoman->isChecked())
        sex=QString("女");
    student temp(ui->nameline->text(),ui->numberline->text(),sex,ui->chinese_line->text().toInt(),
                 ui->math_line->text().toInt(),ui->english_line->text().toInt()); //学生信息

    bool flag=false;
    for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++){
        if(it->number==temp.number)
            flag=true;
    }
    if(temp.check()&&(!flag)){
        ui->textBrowser->clear();
        QTextStream out(file);
        file->open(QIODevice::Append);   //以读写方式打开文件
        out<<"\n"<<temp.name<<"\t"<<temp.number<<"\t"<<temp.sex<<"\t"
          <<temp.chinese<<"\t"<<temp.math<<"\t"<<temp.english;
        file->close();
        studentInfo.push_back(student(temp.name,temp.number,temp.sex,temp.chinese,temp.math,temp.english));
        int i=0;
        for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
        {
            find(i,model,it);
        }
        //显示多少行（多少学生）
        ui->textBrowser->append("共"+QString::number(i)+"行");
        QMessageBox::information(this,tr("successed!"),"添加成功!");
    }
    else{
        ui->textBrowser->clear();
        int i=0;
        for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
        {
            find(i,model,it);
        }
        //显示多少行（多少学生）
        ui->textBrowser->append("共"+QString::number(i)+"行");
        if(!flag)
            QMessageBox::warning(this,tr("错误"),"添加错误!\n请检查输入数据是否合法\n（如:信息为空或不满足规则）");
        else
            QMessageBox::warning(this,tr("错误"),"学号重复!");
    }
}

void MainWindow::on_delete_button_clicked()
{
    student temp(ui->nameline->text(),ui->numberline->text(),"",0,0,0);
    ui->textBrowser->clear();

    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(6);   //6列数据
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    int i=0;
    bool flag=false;
    QVector<student>::iterator it = studentInfo.begin();
    for(; it != studentInfo.end(); it++,i++)
    {
        if((it->name==temp.name&&temp.number==NULL)||(it->number==temp.number&&temp.name==NULL)
           ||(it->name==temp.name&&it->number==temp.number))
        {
            studentInfo.erase(it);
            it--;   //重要！
            i--;
            flag=true;
        }
        else
            find(i,model,it);
    }   //对象删除

    //文件更新成删除的对象！
    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");
    QTextStream out(file);
    file->open(QIODevice::WriteOnly|QFile::Truncate);   ///QFile::Truncate表示重写
    it = studentInfo.begin();
    for(; it != studentInfo.end()-1; it++)
    {
        out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
          <<it->chinese<<"\t"<<it->math<<"\t"<<it->english<<"\n";
    }
    out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
      <<it->chinese<<"\t"<<it->math<<"\t"<<it->english; //最后一行特殊处理（不加换行符）
    ui->textBrowser->append("共"+QString::number(i)+"行");

    if(flag)
        QMessageBox::information(this,tr("删除"),"删除成功!");
    else{
        QMessageBox::warning(this,tr("错误"),"不存在该学号或名字的学生\n(或名字与学号不符)");
    }
}

void MainWindow::on_display_button_clicked()
{
    QStandardItemModel  *model = new QStandardItemModel();
    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");
    model->setColumnCount(6);
    QTextStream in(file);
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->textBrowser->clear();
    while(!in.atEnd()){
            QString name,number,sex;
            int chinese,math, english;
            in >> name >> number >> sex >> chinese >> math >> english;
            studentInfo.push_back(student(name,number,sex,chinese,math,english));
    }
    int i=0;
    for(QVector<student>::iterator it = studentInfo.begin(); it != studentInfo.end(); it++,i++)
    {
        find(i,model,it);
    }
    ui->textBrowser->append("共"+QString::number(i)+"行");
}

bool number_cmp(student a,student b){
    return a.number<b.number;
}

bool chinese_cmp(student a,student b){
    return a.chinese<b.chinese;
}

bool math_cmp(student a,student b){
    return a.math<b.math;
}

bool english_cmp(student a,student b){
    return a.english<b.english;
}

void MainWindow::on_sort_button_clicked()
{
    if(ui->radio_number->isChecked())
    {
        sort(studentInfo.begin(),studentInfo.end(),number_cmp);//从小到大
    }
    else if(ui->radio_chinese->isChecked())
    {
        sort(studentInfo.begin(),studentInfo.end(),chinese_cmp);
    }
    else if(ui->radio_math->isChecked())
    {
        sort(studentInfo.begin(),studentInfo.end(),math_cmp);
    }
    else if(ui->radio_english->isChecked())
    {
        sort(studentInfo.begin(),studentInfo.end(),english_cmp);
    }

    QStandardItemModel  *model = new QStandardItemModel();
    QFile *file=new QFile("C:\\Users\\Lenovo\\Desktop\\data.txt");
    model->setColumnCount(6);
    QTextStream in(file);
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    model->setHeaderData(1,Qt::Horizontal,"学号");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"语文");
    model->setHeaderData(4,Qt::Horizontal,"数学");
    model->setHeaderData(5,Qt::Horizontal,"英语");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    QTextStream out(file);
    file->open(QIODevice::WriteOnly|QFile::Truncate);   //以重写方式打开文件
    auto it=studentInfo.begin();    //auto自动匹配类型!
    //文件更新操作
    int i=0;
    for(it = studentInfo.begin(); it != studentInfo.end()-1; it++,i++)
    {
        out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
          <<it->chinese<<"\t"<<it->math<<"\t"<<it->english<<"\n";
        find(i,model,it);
    }
    out<<it->name<<"\t"<<it->number<<"\t"<<it->sex<<"\t"
      <<it->chinese<<"\t"<<it->math<<"\t"<<it->english; //最后一行特殊处理（不加换行符）
    find(i,model,it);
    file->close();
}

