#include "GUI.h"
#include <QApplication>
#include "string"
#include "iostream"
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GUI w;
    //w.show();
    string st="hola mundo nuevo";
    //string *s=new string('"');
    //st.append('"');
//    string to = st.substr(1,st.find(" ",5)-1);
//    cout<<"split"<<st.find(" ",5)<<to<<endl;

    return a.exec();
}
