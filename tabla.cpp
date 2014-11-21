#include "tabla.h"
#include "ListaMetaDato.h"
#include "iostream"
using namespace std;


tabla::tabla(string pNombre, string pBasedeDatos)
{

    _Nombre = pNombre;
    _NombreBasedeDatos = pBasedeDatos;
    _metaDato = new ListaMetaDato();
    _matrizDato = new MatrizDato();
}

string tabla::getNombre()
{
    return _Nombre;
}

string tabla::getNombreBasedeDatos()
{
    return _NombreBasedeDatos;
}

void tabla::agregarMetaDatos(string pNombre, string pTipoDato)
{
   //_metaDato->insertarFinal(tmp);
    _metaDato->insertarFinal(pNombre,pTipoDato);}

ListaMetaDato *tabla::getListaMetaDato()
{
    return _metaDato;
}

MatrizDato *tabla::getMatrizDato()
{
    return _matrizDato;
}

void tabla::insertarRegistro(ListaDato *pRegistro){
    _matrizDato->insertarFinal(pRegistro);
}

void tabla::setMetaDato(string pMetaDato)
{
    while(pMetaDato.find(",") != string::npos){
        string datoTmp = pMetaDato.substr(0,pMetaDato.find(":"));
        string tipoTmp = pMetaDato.substr(pMetaDato.find(":")+1,pMetaDato.find(",") - pMetaDato.find(":") -1);
        pMetaDato = pMetaDato.substr(pMetaDato.find(",")+1,pMetaDato.length());
        _metaDato->insertarFinal(datoTmp,tipoTmp);
    }
    string datoTmp = pMetaDato.substr(0,pMetaDato.find(":"));
    string tipoTmp = pMetaDato.substr(pMetaDato.find(":")+1,pMetaDato.length());
    _metaDato->insertarFinal(datoTmp,tipoTmp);

}

void tabla::setMetaDatoSinTipo(string pMetaDato)
{
    while(pMetaDato.find(",")!=string::npos){
        string datoTmp = pMetaDato.substr(0,pMetaDato.find(","));

        if(datoTmp.find(" ")==0){
            datoTmp = datoTmp.substr(1,datoTmp.length());
        }
        if(datoTmp.find(" ")==datoTmp.length()-1){
            datoTmp = datoTmp.substr(0,datoTmp.length()-2);
        }
        pMetaDato = pMetaDato.substr(pMetaDato.find(",")+1,pMetaDato.length());
        _metaDato->insertarFinal(datoTmp,"String");
    }

    string datoTmp = pMetaDato;
    if(datoTmp.find(" ")==0){
        datoTmp = datoTmp.substr(1,datoTmp.length());
    }
    if(datoTmp.find(" ")==datoTmp.length()-1){
        datoTmp = datoTmp.substr(0,datoTmp.length()-2);
    }
    pMetaDato = pMetaDato.substr(pMetaDato.find(",")+1,pMetaDato.length() - pMetaDato.find(",")-1);
    _metaDato->insertarFinal(datoTmp,"String");//esta funcion se utiliza para crear tablas temporales donde el tipo es irrelevante
}


ListaMetaDato *tabla::getMetaDato(){
    return _metaDato;
}

void tabla::imprimirTabla()
{
    cout<<"nombre: "<<_Nombre<<endl;
    NodoMetaDato *tmp = _metaDato->getHead();
    for(int i=0;i<_metaDato->getTamanio();i++){
        cout<<"MetaDato: "<<tmp->getDato()->getmetaDato()<<" Tipo: "<<tmp->getDato()->getTipometaDato()<<endl;
        tmp = tmp->getNext();
    }
    for(int j=0;j<_matrizDato->getTamanio();j++){
        cout<<"Registro #"<<j<<endl;
        for(int k = 0; k<_matrizDato->getHead()->getTamanio();k++){
            cout<<_matrizDato->buscarDatoEnPos(j,k)<<endl;
        }
    }

}

bool tabla::existeMetaDato(string pmetaDato)
{
    for(int i=0;i<_metaDato->getTamanio();i++){
        if(_metaDato->buscarPosicion(i)->getmetaDato().compare(pmetaDato)==0){
            return true;
        }
    }
    return false;
}

bool tabla::existeListaMetaDato(string plistaMetaDato)
{
    cout<<"plistaMetadato:"<<plistaMetaDato<<endl;
    while(plistaMetaDato.find(",")!=string::npos){
        string token1 = plistaMetaDato.substr(0,plistaMetaDato.find(","));
        //los if eliminan espacios al inicio y al final para evitar que falle la igualacion
        if(token1.find(" ")==0){
            token1= token1.substr(1,token1.length()-1);
        }
        if(token1.find(" ")==token1.length()-1){
            token1= token1.substr(0,token1.length()-2);
        }
        if(!existeMetaDato(token1)){
            return false;
        }
        plistaMetaDato=plistaMetaDato.substr(plistaMetaDato.find(",")+1,plistaMetaDato.length());
        cout<<"plistaMetadato:"<<plistaMetaDato<<endl;
    }
    cout<<"sali while"<<endl;

    string token1 = plistaMetaDato;
    //los if eliminan espacios al inicio y al final para evitar que falle la igualacion
    if(token1.find(" ")==0){
        token1= token1.substr(1,token1.length()-1);
    }
    if(token1.find(" ")==token1.length()-1){
        token1= token1.substr(0,token1.length()-2);
    }
    cout<<"token1:"<<token1<<endl;
    if(!existeMetaDato(token1)){
        return false;
    }
    return true;
}
