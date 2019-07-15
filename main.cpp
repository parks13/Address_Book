#include "phonewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhoneWindow w;
    w.show();

    return a.exec();
}
