#include "NodoDato.h"

NodoDato::NodoDato(std::string pdato)
{
    _dato = pdato;
    _next = NULL;
    _prev = NULL;
}

string NodoDato::getDato()
{
    return _dato;
}

NodoDato *NodoDato::getNext()
{
    return _next;
}

NodoDato *NodoDato::getPrev()
{
    return _prev;
}

void NodoDato::setNext(NodoDato *pnext)
{
    _next = pnext;
}

void NodoDato::setPrev(NodoDato *pprev)
{
    _prev = pprev;
}
