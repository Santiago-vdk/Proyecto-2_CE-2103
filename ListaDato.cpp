#include "ListaDato.h"
#include "Nododato.h"

ListaDato::ListaDato()
{
    _tamanio = 0;
    _head = NULL;
    _tail = NULL;
    _next = NULL;
    _prev = NULL;
}


int ListaDato::getTamanio()
{
    return _tamanio;
}


NodoDato *ListaDato::getHead()
{
    return _head;
}

NodoDato *ListaDato::getTail()
{
    return _tail;
}

ListaDato *ListaDato::getNext()
{
    return _next;
}

ListaDato *ListaDato::getPrev()
{
    return _prev;
}

void ListaDato::setNext(ListaDato *pnext)
{
    _next = pnext;
}

void ListaDato::setPrev(ListaDato *pprev)
{
    _prev = pprev;
}

void ListaDato::setDato(int ppos, string pDato)
{
    if(ppos<_tamanio){
        NodoDato *tmp = _head;
        for(int i = 0; i<ppos;i++){
            tmp = tmp->getNext();
        }
        tmp->setDato(pDato);
    }
}

void ListaDato::insertarFinal(string pdato)
{
    NodoDato *tmp = new NodoDato(pdato);
    if(_tamanio=0){
        _head = tmp;
        _tail = tmp;
    }
    else{
        _tail->setNext(tmp);
        tmp->setPrev(_tail);
        _tail = tmp;
    }
    _tamanio++;


}

string ListaDato::buscarDatoEnPos(int ppos)
{
    if(ppos<_tamanio){
        NodoDato *tmp = _head;
        for(int i = 0; i<ppos;i++){
            tmp = tmp->getNext();
        }
        return tmp->getDato();
    }
    else{
        return NULL;
    }
}
