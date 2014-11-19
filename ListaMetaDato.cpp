#include "ListaMetaDato.h"
#include "iostream"
using namespace std;

ListaMetaDato::ListaMetaDato()
{
    _tamanio = 0;
    _head = NULL;
    _tail = NULL;
}

int ListaMetaDato::getTamanio()
{
    return _tamanio;
}

NodoMetaDato *ListaMetaDato::getHead()
{
    return _head;
}

NodoMetaDato *ListaMetaDato::getTail()
{
    return _tail;
}

void ListaMetaDato::insertarFinal(string pNombre, string pTipo)
{

    metaDato *metaTmp = new metaDato(pNombre,pTipo);
    NodoMetaDato *tmp = new NodoMetaDato(metaTmp);
    if(_head == NULL){
        _head = tmp;
        _tail = tmp;
        _tamanio++;

    }
    else{

       _tail->setNext(tmp);
       tmp->setPrev(_tail);
       _tail = tmp;
       _tamanio++;
    }
}

metaDato *ListaMetaDato::buscarPosicion(int pPos)
{
    if(pPos < _tamanio){
        NodoMetaDato *tmp = _head;
        for(int i=0; i<pPos;i++){
            tmp = tmp->getNext();
        }
        return tmp->getDato();
    }
    else{
        cout<<"busqueda out of range"<<endl;
    }
}

string ListaMetaDato::listaMetaDatoToString()
{
    string tmp ="";
    NodoMetaDato *nodoTmp = _head;
    for(int i = 0; i<_tamanio;i++){
            tmp= tmp+nodoTmp->getDato()->getmetaDato()+":"+nodoTmp->getDato()->getTipometaDato()+",";
            nodoTmp=nodoTmp->getNext();
    }
    tmp = tmp.substr(0,tmp.length()-1);//elimina la ultima coma
    cout<<"lista...tostring:"<<tmp<<endl;
    return tmp;
}

int ListaMetaDato::PosMetaDato(string pmetaDato)
{
    NodoMetaDato *tmp = _head;
    int i=0;
    while(tmp->getDato()->getmetaDato().compare(pmetaDato)!=0){
        i++;
        tmp = tmp->getNext();
    }
    return i;
}
