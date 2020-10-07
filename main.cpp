#include "progflash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgFlash w;
    w.show();

    return a.exec();
}
