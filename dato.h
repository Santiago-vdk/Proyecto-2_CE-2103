#ifndef DATO_H
#define DATO_H
#include <string>
using namespace std;

class Dato
{
public:
    Dato(dato,tipoDato);
    string getDato();
    string getTipoDato();

    void setDato(string dato);
    void setTipoDato(string tipoDato);


private:
    string _dato;
    string _tipoDato;
};

#endif // DATO_H
