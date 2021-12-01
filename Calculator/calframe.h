#ifndef CALFRAME_H
#define CALFRAME_H

#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QVector>

#include"calservice.h"

class CalFrame : public QWidget
{
    Q_OBJECT

public:
    CalFrame(QWidget *parent = nullptr);
    ~CalFrame();
public slots:
    void getBtClicked();
private:
    QStringList mOp={"MC", "MR", "MS", "M+"};
    QStringList rOp={"BACK", "CE", "C"};
    QStringList nOp={ "7", "8", "9", "/", "sqrt", "4", "5", "6", "*", "%", "1", "2", "3", "-", "1/x", "0", "+/-",
                     ".", "+", "=" };
    QPushButton *button=NULL;
    QLineEdit *leField=NULL;
    QPushButton *getButton();//获得当前的按钮指针
    QLineEdit *getLeField();//获得当前文本框指针
    QVector<QPushButton *> getMButton();
    QVector<QPushButton *> getNButton();
    QVector<QPushButton *> getRButton();
    bool findOp(const QString& s,const QStringList& slist);

    CalService calservice;


};
#endif // CALFRAME_H
