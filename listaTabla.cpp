#include "listaTabla.h"
#include <QDebug>
#include "iostream"
using namespace std;
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

void listaTabla::insertarFinal(string pNombre, string pNombreBase)
{
    tabla * tempDato = new tabla(pNombre,pNombreBase);
    nodoTabla *tmp = new nodoTabla(tempDato);
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

tabla *listaTabla::buscarTablaEnPos(int i)
{
    nodoTabla *tmp = _head;
    if(i<_tamanio){
        for(int j =0; j<i;j++){
            tmp = tmp->getTablaNext();
        }
        return tmp->getTabla();
    }
    else{
        return NULL;
    }
}

tabla *listaTabla::buscarTabla(string pnombre)
{
    nodoTabla *tmp = _head;
    while(tmp!=NULL && tmp->getTabla()->getNombre().compare(pnombre)!=0){
        tmp = tmp->getTablaNext();
    }
    return tmp->getTabla();
}

void listaTabla::imprimirTablas()
{
    nodoTabla *tmp = _head;
    for(int i =0;i<_tamanio;i++){
        tmp->getTabla()->imprimirTabla();
        tmp = tmp->getTablaNext();
    }
}

bool listaTabla::existeTabla(string pnombre)
{
    nodoTabla *tmp = _head;
    for(int i = 0; i<_tamanio;i++){
        if (tmp->getTabla()->getNombre().compare(pnombre)==0){
            return true;
        }
        tmp = tmp->getTablaNext();
    }
    return false;
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


