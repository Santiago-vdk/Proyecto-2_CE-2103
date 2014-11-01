#include "dato.h"

Dato::Dato(string dato, string tipoDato)
{
    _dato = dato;
    _tipoDato = tipoDato;
}


string Dato::getDato()
{
    return _dato;
}

string Dato::getTipoDato()
{
    return _tipoDato;
}

void Dato::setDato(string dato)
{
    _dato = dato;
}

void Dato::setTipoDato(string tipoDato)
{
    _tipoDato = tipoDato;
}
