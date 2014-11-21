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
    string listaToString(int i);
    ListaDato *buscarListaEnPos(int ppos);
    string buscarDatoEnPos(int i,int j);

 void imprimirMatriz();    void setDato(int i, int j, string pDato);
    void deleteLista(int i);private:
    int _tamanio;
    ListaDato *_head;
    ListaDato *_tail;

};

#endif // MATRIZDATO_H
