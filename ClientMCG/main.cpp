#include "mainwindow.h"
#include "clientregister.h"
#include <QApplication>


int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    ClientRegister w;
    w.show();
    return a.exec();


}
