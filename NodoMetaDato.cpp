#include "NodoMetaDato.h"

NodoMetaDato::NodoMetaDato(metaDato *pDato)
{
    _dato = pDato;
    _next = NULL;
    _prev = NULL;

}


NodoMetaDato *NodoMetaDato::getNext()
{
    return _next;
}

NodoMetaDato *NodoMetaDato::getPrev()
{
    return _prev;
}

metaDato *NodoMetaDato::getDato()
{
    return _dato;
}

void NodoMetaDato::setNext(NodoMetaDato *pNext)
{
    _next = pNext;
}

void NodoMetaDato::setPrev(NodoMetaDato* pPrev)
{
    _prev = pPrev;
}

void NodoMetaDato::setDato(metaDato* pDato)
{
    _dato = pDato;
}
