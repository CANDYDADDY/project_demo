#include "calservice.h"
#include"config.h"
#include<QtMath>
CalService::CalService()
{

}

QString CalService::callMethod(QString cmd, QString text)
{
    if(cmd=="C")
        return clearAll();
    else if(cmd=="CE")
        return clear();
    else if(cmd=="BACK")
        return backSpace(text);
    else if(numString.indexOf(cmd)!=-1)
        return catNum(cmd, text);
    else if(opString.indexOf(cmd)!=-1)
        return setOp(cmd, text);
    else if(cmd=="=")
        return cal(text, false);
    else if(cmd=="+/-")
        return setNegative(text);
    else if(cmd=="1/x")
        return setReciprocal(text);
    else if(cmd=="%")
        return cal(text, true);
    else if(cmd=="sqrt")
        return sqrt(text);
    else
        return mCmd(cmd, text);
}

double CalService::getStore()
{
    return store;
}

QString CalService::clearAll()
{
    firstNum = "0";
    secondNum=QString::Null();
    isSecondNum = false;// 源代码没这一行
    return firstNum;
}
//处理CE
QString CalService::clear()
{
    return "0";
}
//处理BACKSPACE
QString CalService::backSpace(QString &text)
{
    QString data=text;
    if((data.length()==1)||(data==""))
        return "0";
    else
    {
        data.chop(1);
        return data;
    }
}
//处理“0123456789.”数字按键
QString CalService::catNum(const QString &cmd, const QString &text)
{
    QString data=cmd;
    if(text!="0"){
        if(isSecondNum==true)
            isSecondNum=false;//保证1/x,sqrt,op操作后，文本框重新开始输入新的数据。
        else
            data=text+cmd;
    }
    return data.indexOf(".")==0?"0"+data:data;
}
//处理算术运算符
QString CalService::setOp(const QString &cmd, const QString &text)
{
    lastOp=cmd;
    firstNum=text;
    secondNum=QString::Null();//为了计算形如：（3*5=15）*2，只有为null，在cal计算过程中才能将text中的值赋予secondNum
    isSecondNum=true;
    return QString();
}

QString CalService::cal(const QString &text, bool flag)
{
    QString res="";
    secondNum=secondNum.isNull()?text:secondNum;
    //判断除数是否为0
    if(secondNum=="0"&&lastOp=="/"){
        lastOp="";
        firstNum="0";
        secondNum=QString::Null();
        isSecondNum=true;
        return "除数不能为零";
    }
    double secondResult=secondNum.toDouble();
    if(flag==true)
        secondResult=firstNum.toDouble()*secondResult/100;
    switch (lastOp.toStdString().c_str()[0]) {
    case '+':
        firstNum=QString::number(firstNum.toDouble()+secondResult);

        break;
    case '-':
        firstNum=QString::number(firstNum.toDouble()-secondResult);
        break;
    case '*':
        firstNum=QString::number(firstNum.toDouble()*secondResult);
        break;
    case '/':
        firstNum=QString::number(firstNum.toDouble()/secondResult,'g',16);
        break;
    default:
        return "0";
   }
    isSecondNum=true;
    return firstNum;
}
//处理"+/-"
QString CalService::setNegative(const QString &text)
{
    if(text.indexOf("-")==0)
        return text.mid(1);//取"-"后面的字符串
    else{
        return text=="0"?text:"-"+text;//注意0的特殊处理。
    }
}
//处理"1/x"
QString CalService::setReciprocal(const QString &text)
{
    if(text=="0")
        return text;
    else{
        isSecondNum=true;
        return QString::number(1.0/text.toDouble(),'g',16);//小数点后16位
    }
}
//处理"sqrt"
QString CalService::sqrt(const QString &text)
{
    isSecondNum=true;
    if(text.indexOf("-")==0){
        firstNum="0";
        secondNum=QString::Null();
        return "无效输入";
    }
    return QString::number(qSqrt(text.toDouble()),'g',16);
}

QString CalService::mCmd(const QString &cmd, const QString &text)
{
    if(cmd=="M+")
        store+=text.toDouble();
    else if(cmd=="MC")
        store=0;
    else if(cmd=="MS")
        store=text.toDouble();
    else if(cmd=="MR"){
        isSecondNum=true;
        return QString::number(store,'g',16);
    }
    return QString();
}
