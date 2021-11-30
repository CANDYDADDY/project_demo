#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
public slots:
    void chopOneData();
    void getNumBtPushed();
    void getOpBtPushed();
    void getCalBtPushed();

private:
    QPushButton *btNum[10];
    QPushButton *btAdd,*btSub,*btMul,*btDiv,*btCal,*btCut;
    QLineEdit *leSHow;
    int lData;
    QString op;

};
#endif // MYWIDGET_H
