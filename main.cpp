#include "squorder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    squorder w;
    w.show();
    return a.exec();
}
