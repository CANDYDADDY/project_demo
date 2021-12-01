#include "calframe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalFrame w;
    w.show();
    return a.exec();
}
