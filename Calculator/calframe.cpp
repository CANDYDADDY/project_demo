#include "calframe.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>

#include"config.h"

CalFrame::CalFrame(QWidget *parent)
    : QWidget(parent)
{
    //初始化计算器界面
    setWindowTitle("计算器");
    setFixedSize(CAL_WIDTH,CAL_HEIGHT);
    //设置主布局panel
    QVBoxLayout *panel=new QVBoxLayout;
    //添加文本框到主布局
    panel->addWidget(getLeField());
    //设置左边布局panleLeft
    QGridLayout *panelLeft=new QGridLayout;
    int row=0;
    for(auto m:getMButton()){
        panelLeft->addWidget(m,row,0,1,1);
        row++;
    }
    //设置右上布局panelRightUp
    QHBoxLayout *panelRightUp=new QHBoxLayout;
    for(auto n:getRButton())
        panelRightUp->addWidget(n);
    //设置右下布局panleRightDown
    QGridLayout *panelRightDown=new QGridLayout;
    row=0;
    int col=0;
    for(auto b:getNButton()){
        if(col%5==0)
            row++;
        panelRightDown->addWidget(b,row,col%5,1,1);
        col++;
    }
    //设置右布局panleRight
    QVBoxLayout *panelRight=new QVBoxLayout;
    panelRight->addLayout(panelRightUp);
    panelRight->addLayout(panelRightDown);

    //设置主布局下半部分panleDown
    QHBoxLayout *panelDown=new QHBoxLayout;
    panelDown->addLayout(panelLeft);
    panelDown->addLayout(panelRight);
    //添加主布局下半部分
    panel->addLayout(panelDown);

    this->setLayout(panel);
    connect(button,&QPushButton::clicked,this,&CalFrame::getBtClicked);

}

CalFrame::~CalFrame()
{
}
//定义槽函数
void CalFrame::getBtClicked()
{
    QString result=NULL;
    QPushButton *pbt=static_cast<QPushButton *>(sender());
    QString cmd=pbt->text();
    result = calservice.callMethod(cmd, leField->text());
    if(cmd.indexOf("MC")==0)
        button->setText("");
    else if(cmd.indexOf("M")==0&&calservice.getStore() > 0)
        button->setText("M");
    if(result!=NULL)
        leField->setText(result);
}

QPushButton *CalFrame::getButton()
{
    if(button==NULL)
        button=new QPushButton;
    return button;
}

QLineEdit *CalFrame::getLeField()
{
    if(leField==NULL){
        leField=new QLineEdit(QString::number(0),this);
        leField->setAlignment(Qt::AlignRight);
    }
    return leField;
}

QVector<QPushButton *> CalFrame::getMButton()
{
    int len=mOp.size();
    QVector<QPushButton *> result(len+1);
    result[0]=getButton();
    for (int i=0;i<len;i++) {
        QPushButton *b=new QPushButton(mOp[i],this);
        connect(b,&QPushButton::clicked,this,&CalFrame::getBtClicked);
        b->setStyleSheet("color:red");
        result[i + 1] = b;
    }
    return result;

}

QVector<QPushButton *> CalFrame::getNButton()
{
    QStringList redButton = { "/", "*", "-", "+", "=" };
    int len=nOp.size();
    QVector<QPushButton*> result(len);
    for (int i=0;i<len;i++) {
        QPushButton *b=new QPushButton(nOp[i],this);
        connect(b,&QPushButton::clicked,this,&CalFrame::getBtClicked);
        if(findOp(nOp[i],redButton)){
            b->setStyleSheet("color:red");
        }else{
            b->setStyleSheet("color:blue");
        }
        result[i]=b;
    }
    return result;
}

QVector<QPushButton *> CalFrame::getRButton()
{
    int len=rOp.size();
    QVector<QPushButton *> result(len);
    for (int i=0;i<len;i++) {
        QPushButton *b=new QPushButton(rOp[i],this);
        connect(b,&QPushButton::clicked,this,&CalFrame::getBtClicked);
        b->setStyleSheet("color:red");
        result[i] = b;
    }
    return result;
}

bool CalFrame::findOp(const QString &s, const QStringList &slist)
{
    bool res=false;
    for(auto m:slist){
        if(m==s)
            res=true;
    }
    return res;
}

