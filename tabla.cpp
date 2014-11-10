#include "tabla.h"
#include "ListaMetaDato.h"


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
