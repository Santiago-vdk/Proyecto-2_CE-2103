#ifndef listaTabla_H
#define listaTabla_H
#include <nodoTabla.h>
#include <tabla.h>

class listaTabla
{
public:
    listaTabla();
    ~listaTabla();

    nodoTabla *getHead();
    nodoTabla *getTail();
    listaTabla *getNext();
    listaTabla *getPrev();
    int getTamanio();
    nodoTabla *getPos(int i);

    void setHead(nodoTabla *pHead);
    void setTail(nodoTabla *pTail);
    void setNext(listaTabla *pNext);
    void setPrev(listaTabla *pPrev);

    void insertarFinal(tabla *nodo);


private:
    nodoTabla* _head=NULL;
    nodoTabla* _tail=NULL;
    listaTabla* _next=NULL;
    listaTabla* _prev=NULL;
    int _tamanio;
};

#endif // listaTabla_H
