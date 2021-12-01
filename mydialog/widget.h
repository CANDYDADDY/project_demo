#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTextEdit>
#include<QErrorMessage>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QPushButton *bt_filename;
    QPushButton *bt_getcolor;
    QPushButton *bt_getfont;
    QPushButton *bt_getinput;
    QPushButton *bt_message;
    QPushButton *bt_error;
    QPushButton *bt_process;

    QTextEdit *te_text;
};
#endif // WIDGET_H
