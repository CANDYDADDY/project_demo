#include "widget.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFileDialog>
#include<QColorDialog>
#include<QFontDialog>
#include<QInputDialog>
#include<QErrorMessage>
#include<QMessageBox>
#include<QProgressDialog>
#include<QCoreApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("七种对话框");
    bt_filename=new QPushButton("获取文件名");
    bt_getcolor=new QPushButton("获取颜色");
    bt_getfont=new QPushButton("获取字体");
    bt_getinput=new QPushButton("获取输入");
    bt_error=new QPushButton("错误弹框");
    bt_message=new QPushButton("消息弹框");
    bt_process=new QPushButton("进度条对话框");

    te_text=new QTextEdit;
    QVBoxLayout *vb=new QVBoxLayout;
    vb->addWidget(bt_filename);
    vb->addWidget(bt_getcolor);
    vb->addWidget(bt_getfont);
    vb->addWidget(bt_getinput);
    vb->addWidget(bt_error);
    vb->addWidget(bt_message);
    vb->addWidget(bt_process);

    QHBoxLayout *hb=new QHBoxLayout;
    hb->addLayout(vb);
    hb->addWidget(te_text);
    setLayout(hb);

    //建立槽函数
    connect(bt_filename,&QPushButton::clicked,this,[=](){
        QString filename=QFileDialog::getOpenFileName();
        te_text->append(filename);
    });

    connect(bt_getcolor,&QPushButton::clicked,this,[=](){
        QColor color=QColorDialog::getColor();
        te_text->setTextColor(color);
    });

    connect(bt_getfont,&QPushButton::clicked,this,[=](){
        bool ok;
        QFont font=QFontDialog::getFont(&ok);
        if(ok)
            te_text->setCurrentFont(font);
    });

    connect(bt_getinput,&QPushButton::clicked,this,[=](){
        QString input=QInputDialog::getText(this,"输入对话框","我要说：");
        //te_text->setText(input);
        te_text->append(input);
    });
    connect(bt_message,&QPushButton::clicked,this,[=](){
        QMessageBox::warning(this,"警告","出现错误了！！",QMessageBox::Open,QMessageBox::Apply);
    });
    connect(bt_error,&QPushButton::clicked,this,[=](){
        QErrorMessage *err=new QErrorMessage;//这里必须是指针，否则对话框闪退。
        err->showMessage("脑回路断了！！");
    });
    connect(bt_process,&QPushButton::clicked,this,[=](){
        QProgressDialog *pro=new QProgressDialog("文件复制进度","取消",0,50000,this);
        pro->setWindowTitle("进度对话框");
        pro->setAutoClose(false);//进度达到最大值时不关闭，默认为true
        pro->setWindowModality(Qt::WindowModal);
        pro->show();
        for (int i=0;i<50000;i++) {
            pro->setValue(i);
            QCoreApplication::processEvents();
            if(pro->wasCanceled())
                break;
        }
        pro->setValue(50000);
       // pro.exec();
    });
}

Widget::~Widget()
{
}

