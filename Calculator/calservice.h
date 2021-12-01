#ifndef CALSERVICE_H
#define CALSERVICE_H

#include<QString>

class CalService
{
public:
    CalService();
    QString callMethod(QString cmd,QString text);
    double getStore();
    QString clearAll();//处理按键“C”
    QString clear();//处理按键“CE”
    QString backSpace(QString& text);//处理按键“BACK”
    QString catNum(const QString& cmd, const QString& text);//处理数字键
    QString setOp(const QString& cmd, const QString& text);//处理运算符键
    QString cal(const QString& text, bool flag);//处理“=”和"%"
    QString setNegative(const QString& text);//处理“+/-”
    QString setReciprocal(const QString& text);//处理“1/x”
    QString sqrt(const QString& text);//处理“sqrt”
    QString mCmd(const QString& cmd, const QString& text);//处理“MC”...


private:
    QString numString="0123456789.";
    QString opString="+-*/";
    QString firstNum=QString::Null();
    QString secondNum=QString::Null();
    QString lastOp=NULL;
    double store = 0;
    bool isSecondNum = false;
};

#endif // CALSERVICE_H
