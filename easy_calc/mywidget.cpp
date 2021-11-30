#include "mywidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("简易计算器");
    QHBoxLayout *hb=new QHBoxLayout();
    QVBoxLayout *vb=new QVBoxLayout();
    QGridLayout *gd=new QGridLayout();

    leSHow=new QLineEdit();
    leSHow->setAlignment(Qt::AlignRight);
    btCut=new QPushButton("<",this);
    for (int i=0;i<10;i++) {
        btNum[i]=new QPushButton(QString::number(i),this);
    }
    btAdd=new QPushButton("+",this);
    btSub=new QPushButton("-",this);
    btMul=new QPushButton("*",this);
    btDiv=new QPushButton("/",this);
    btCal=new QPushButton("=",this);
    btCal->setMinimumHeight(75);

    //布局
    hb->addWidget(leSHow);
    hb->addWidget(btCut);
    int row=0;
    for (int col=1;col<10;col++) {
        gd->addWidget(btNum[col],row,(col-1)%3,1,1);
        if(col%3==0)
            row++;
    }
    gd->addWidget(btNum[0],3,1,1,1);
    gd->addWidget(btMul,3,0,1,1);
    gd->addWidget(btDiv,3,2,1,1);
    gd->addWidget(btAdd,0,3,1,1);
    gd->addWidget(btSub,1,3,1,1);
    gd->addWidget(btCal,2,3,2,1);
    vb->addLayout(hb);
    vb->addLayout(gd);
    this->setLayout(vb);

    //信号与槽的连接
    connect(btCut,&QPushButton::clicked,this,&MyWidget::chopOneData);
    for (int i=0;i<10;i++) {
        connect(btNum[i],&QPushButton::clicked,this,&MyWidget::getNumBtPushed);
    }
    connect(btAdd,&QPushButton::clicked,this,&MyWidget::getOpBtPushed);
    connect(btSub,&QPushButton::clicked,this,&MyWidget::getOpBtPushed);
    connect(btMul,&QPushButton::clicked,this,&MyWidget::getOpBtPushed);
    connect(btDiv,&QPushButton::clicked,this,&MyWidget::getOpBtPushed);
    connect(btCal,&QPushButton::clicked,this,&MyWidget::getCalBtPushed);

}

MyWidget::~MyWidget()
{
}

void MyWidget::chopOneData()
{
    //提取文字
    QString data=leSHow->text();
    //删除一位数字
    data.chop(1);
    leSHow->setText(data);

}

void MyWidget::getNumBtPushed()
{
    QPushButton *pbt=static_cast<QPushButton *>(sender());
    //2.提取文字
    QString vstr=pbt->text();
    //3.追加显示在编辑框
    QString data=leSHow->text();
    leSHow->setText(data+vstr);
}

void MyWidget::getOpBtPushed()
{
    lData=leSHow->text().toInt();
    QPushButton *pbt=static_cast<QPushButton *>(sender());
    //2.提取文字
    op=pbt->text();
    leSHow->clear();
}

void MyWidget::getCalBtPushed()
{
    int rData=leSHow->text().toInt();
    int sum=0;
    switch (op.toStdString().c_str()[0]) {
    case '+':
        sum=lData+rData;
        break;
    case '-':
        sum=lData-rData;
        break;
    case '*':
        sum=lData*rData;
        break;
    case '/':
        sum=lData/rData;
        break;
    }
    leSHow->setText(QString::number(sum));

}

