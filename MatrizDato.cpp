#include "MatrizDato.h"
#include <iostream>

using namespace std;

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
    if(_tamanio == 0 ){
        _head = _tail = plista;
    }
    else{
        _tail->setNext(plista);
        plista->setPrev(_tail);
        _tail = plista;
    }
    _tamanio++;
}

string MatrizDato::listaToString(int i)
{
    NodoDato *tmp = buscarListaEnPos(i)->getHead();
    string result = "";
    for(int a=0;a<i;a++){
        result.append(tmp->getDato());
        result.append(",");
        tmp = tmp->getNext();
    }
    result = result.substr(0,result.length()-1);
    return result;
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
string MatrizDato::buscarDatoEnPos(int i, int j)
{
    if(i<_tamanio && j<_head->getTamanio()){
        ListaDato *tmp = _head;
        for(int a=0; a< i;a++){
            tmp = tmp->getNext();
        }
        NodoDato *tmp2 = tmp->getHead();
        for(int b=0; b< j;b++){
            tmp2 = tmp2->getNext();
        }
        return tmp2->getDato();
    }
    else{
        return NULL;
    }
}void MatrizDato::imprimirMatriz()
{
    ListaDato *listaTmp = _head;
    for(int i=0;i<_tamanio;i++){
        for(int j = 0; j<listaTmp->getTamanio();j++){
            cout<<listaTmp->buscarDatoEnPos(j)<<endl;
        }
        listaTmp = listaTmp->getNext();
    }
}


void MatrizDato::setDato(int i, int j,string pDato)
{
    ListaDato * tmp = _head;
    for(int a=0;a<i;a++){
        tmp=tmp->getNext();
    }
    NodoDato* tmp2 = tmp->getHead();
    for(int b=0;b<j;b++){
        tmp2=tmp2->getNext();
    }

    tmp2->setDato(pDato);

}

void MatrizDato::deleteLista(int i)
{
    if(i==0){
        cout<<"entre 0"<<endl;
        _head->getNext()->setPrev(NULL);
        _head = _head->getNext();
        _tamanio--;
    }
    else if(i==_tamanio-1){
        cout<<"entre tam"<<endl;
        _tail->getPrev()->setNext(NULL);
        _tail = _tail->getPrev();
        _tamanio--;
    }

    else{
        cout<<"borrando"<<endl;
        ListaDato *tmp = _head;
        for(int a=0;a<i;a++){
            tmp = tmp->getNext();
            cout<<"a"<<a<<endl;
        }
        tmp->getPrev()->setNext(tmp->getNext());
        tmp->getNext()->setPrev(tmp->getPrev());
        _tamanio--;
        cout<<"borrando:"<<tmp->buscarDatoEnPos(0);
    }

}

