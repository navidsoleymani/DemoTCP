#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << Widget::numberOfObjects;
//    Widget w,w1,w2,w3,w4;
//    w.show();
    Widget::numberOfObjects = 200;
    qDebug() << Widget::numberOfObjects;
    return a.exec();
}
