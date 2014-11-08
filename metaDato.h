#ifndef metaDato_H
#define metaDato_H
#include <string>
using namespace std;

class metaDato
{
public:
    metaDato(string metaDato,string tipometaDato);
    string getmetaDato();
    string getTipometaDato();

    void setmetaDato(string metaDato);
    void setTipometaDato(string tipometaDato);


private:
    string _metaDato;
    string _tipometaDato;
};

#endif // metaDato_H
