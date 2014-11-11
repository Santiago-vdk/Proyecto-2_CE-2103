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

    _metaDato->insertarFinal(pNombre,pTipoDato);
}

ListaMetaDato *tabla::getListaMetaDato()
{
    return _metaDato;
}

MatrizDato *tabla::getMatrizDato()
{
    return _matrizDato;
}

void tabla::insertarRegistro(ListaDato *pRegistro)
{
    _matrizDato->insertarFinal(pRegistro);
}

void tabla::setMetaDato(string pMetaDato)
{
    ListaMetaDato * listaTmp = new ListaMetaDato();
    while(pMetaDato.find(",") != string::npos){
        string datoTmp = pMetaDato.substr(0,pMetaDato.find(":")-1);
        string tipoTmp = pMetaDato.substr(pMetaDato.find(":")+1,pMetaDato.find(",") - pMetaDato.find(":") -1);
        pMetaDato = pMetaDato.substr(pMetaDato.find(","),pMetaDato.length() - pMetaDato.find(","));
        listaTmp->insertarFinal(datoTmp,tipoTmp);
    }
}

ListaMetaDato *tabla::getMetaDato()
{
    return _metaDato;
}

void tabla::imprimirTabla()
{
    cout<<"nombre: "<<_Nombre<<endl;
    NodoMetaDato tmp = _metaDato->getHead();
    for(int i=0;i<_metaDato->getTamanio();i++){
        cout<<"MetaDato: "<<tmp.getDato()->getmetaDato()<<" Tipo: "<<tmp.getDato()->getTipometaDato()<<endl;
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
    while(plistaMetaDato.find(",")!=string::npos){
        string token1 = plistaMetaDato.substr(0,plistaMetaDato.find(",")-1);
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
    }
    string token1 = plistaMetaDato;
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
    return true;
}
