#include "GUI.h"
#include <QApplication>
#include "iostream"

#include "compress.h"
using namespace std;


int main(int argc, char *argv[])
{
 QApplication a(argc, argv);
    GUI w;
     w.show();

   // compress archivo("/prueba.txt","/prueba.zip");
    //archivo.encode();


    return a.exec();
}
