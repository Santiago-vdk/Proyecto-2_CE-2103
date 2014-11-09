#include "MatrizDato.h"

MatrizDato::MatrizDato()
{
    _tamanio = 0;
    _head = NULL;
    _tail = NULL;
}

int MatrizDato::getTamanio()
{
    return _tamanio;
}

ListaDato *MatrizDato::getHead()
{
    return _head;
}

ListaDato *MatrizDato::getTail()
{
    return _tail;
}

void MatrizDato::insertarFinal(ListaDato *plista)
{
    if(_tamanio = 0 ){
        _head = _tail = plista;
    }
    else{
        _tail->setNext(plista);
        plista->setPrev(_tail);
        _tail = plista;
    }
    _tamanio++;
}

ListaDato *MatrizDato::buscarListaEnPos(int ppos)
{
    if(ppos<_tamanio){

        ListaDato *tmp = _head;
        for(int i = 0; i<ppos;i++){
            tmp = tmp->getNext();
        }
        return tmp;
    }
    else{
        return NULL;
    }
}
