#include "GUI.h"
#include <QApplication>
#include "iostream"
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QString test(" saasdfasf");
//    test.toInt();

    GUI w;
    w.show();

//    std::string str = ";lhui";
//    QString test = QString::fromStdString(str);
//    bool ok;
//    cout<<test.toInt(&ok)<<endl;
//    cout<<ok<<endl;
//    if(ok){
//        cout<<"entre ok"<<endl;
//    }

    return a.exec();
}
