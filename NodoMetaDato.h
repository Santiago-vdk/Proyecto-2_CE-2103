#ifndef NodoMetaDato_H
#define NodoMetaDato_H
#include "metaDato.h"

class NodoMetaDato
{
public:
    NodoMetaDato(metaDato *pDato);
    NodoMetaDato *getNext();
    NodoMetaDato *getPrev();
    metaDato *getDato();

    void setNext(NodoMetaDato *pNext);
    void setPrev(NodoMetaDato *pPrev);
    void setDato(metaDato *pDato);

private:
    metaDato *_dato;
    NodoMetaDato *_next;
    NodoMetaDato *_prev;
};

#endif // NodoMetaDato_H
