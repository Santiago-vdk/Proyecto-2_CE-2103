#ifndef MATRIZDATO_H
#define MATRIZDATO_H
#include "ListaDato.h"

class MatrizDato
{
public:
    MatrizDato();
    int getTamanio();
    ListaDato *getHead();
    ListaDato *getTail();

    void insertarFinal(ListaDato * plista);
    ListaDato *buscarListaEnPos(int ppos);

private:
    int _tamanio;
    ListaDato *_head;
    ListaDato *_tail;

};

#endif // MATRIZDATO_H
