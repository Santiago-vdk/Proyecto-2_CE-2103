#include "listaTabla.h"
#include <QDebug>

listaTabla::listaTabla()
{
    _tamanio=0;
}

listaTabla::~listaTabla()
{
    for(int i=0;i<_tamanio;i++){
        nodoTabla *tmp=_head;
        _head=_head->getTablaNext();
        delete tmp;
    }
}

void listaTabla::insertarFinal(tabla *nodo)
{
    nodoTabla *tmp = new nodoTabla(nodo);
    if(_head == NULL){
        _head = _tail = tmp;
    }
    else{
        _tail->setTablaNext(tmp);
        tmp->setTablaPrev(_tail);
        _tail = tmp;
    }
    _tamanio++;
}

nodoTabla *listaTabla::getHead()
{
    return _head;
}

nodoTabla*listaTabla::getTail()
{
    return _tail;
}

listaTabla* listaTabla::getNext()
{
    return _next;
}

listaTabla* listaTabla::getPrev()
{
    return _prev;
}

int listaTabla::getTamanio()
{
    return _tamanio;
}

nodoTabla *listaTabla::getPos(int i)
{
    nodoTabla *tmp= _head;
    for(int a=0;a<i;a++){
        tmp=tmp->getTablaNext();
    }
    return tmp;
}

void listaTabla::setHead(nodoTabla *pHead)
{
    _head = pHead;
}

void listaTabla::setTail(nodoTabla *pTail)
{
    _tail = pTail;
}

void listaTabla::setNext(listaTabla *pNext)
{
    _next = pNext;
}

void listaTabla::setPrev(listaTabla* pPrev)
{
    _prev = pPrev;
}


