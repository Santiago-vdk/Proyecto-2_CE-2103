#ifndef ListaDato_H
#define ListaDato_H
#include "Nododato.h"
#include <string>

using namespace std;

class ListaDato
{
public:
    ListaDato();

    int getTamanio();
    NodoDato *getHead();
    NodoDato *getTail();
    ListaDato *getNext();
    ListaDato *getPrev();

    void setNext(ListaDato *pnext);
    void setPrev(ListaDato *pprev);
    void setDato(int ppos,string pDato);

    void insertarFinal(string pdato);
    string buscarDatoEnPos(int ppos);


private:
    NodoDato *_head;
    NodoDato *_tail;
    ListaDato *_next;
    ListaDato *_prev;
    int _tamanio;

};

#endif // ListaDato_H
