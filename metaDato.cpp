#include "metaDato.h"

metaDato::metaDato(string metaDato, string tipometaDato)
{
    _metaDato = metaDato;
    _tipometaDato = tipometaDato;
}


string metaDato::getmetaDato()
{
    return _metaDato;
}

string metaDato::getTipometaDato()
{
    return _tipometaDato;
}

void metaDato::setmetaDato(string metaDato)
{
    _metaDato = metaDato;
}

void metaDato::setTipometaDato(string tipometaDato)
{
    _tipometaDato = tipometaDato;
}
