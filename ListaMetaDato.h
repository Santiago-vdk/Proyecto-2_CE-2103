#ifndef LISTAMETADATO_H
#define LISTAMETADATO_H
#include "NodoMetaDato.h"

class ListaMetaDato
{
public:
    ListaMetaDato();

    int getTamanio();
    NodoMetaDato getHead();
    NodoMetaDato getTail();

    void insertarFinal(metaDato *pDato);
    metaDato *buscarPosicion(int pPos);



private:
    int _tamanio;
    NodoMetaDato *_head;
    NodoMetaDato *_tail;
};

#endif // LISTADATOS_H
