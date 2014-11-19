#ifndef LISTAMETADATO_H
#define LISTAMETADATO_H
#include "NodoMetaDato.h"

class ListaMetaDato
{
public:
    ListaMetaDato();

    int getTamanio();
    NodoMetaDato *getHead();
    NodoMetaDato *getTail();

    void insertarFinal(string pNombre, string pTipo);
    metaDato *buscarPosicion(int pPos);
    string listaMetaDatoToString();
    int PosMetaDato(string pmetaDato);



private:
    int _tamanio;
    NodoMetaDato *_head;
    NodoMetaDato *_tail;
};

#endif // LISTADATOS_H
