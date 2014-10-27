#include "nodoTabla.h"


nodoTabla::nodoTabla(tabla *dato)
{
    _dato = dato;

}

tabla *nodoTabla::getTabla()
{
    return _dato;
}

nodoTabla * nodoTabla::getTablaNext()
{
    return _next;
}

nodoTabla* nodoTabla::getTablaPrev()
{
    return _prev;
}

void nodoTabla::setTablaNext(nodoTabla* pTablaNext)
{
    _next = pTablaNext;
}

void nodoTabla::setTablaPrev(nodoTabla* pTablaPrev)
{
    _prev = pTablaPrev;
}

void nodoTabla::setDato(tabla* pDato)
{
    _dato = pDato;
}


