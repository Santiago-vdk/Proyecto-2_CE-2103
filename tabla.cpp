#include "tabla.h"


tabla::tabla(string pNombre, string pBasedeDatos)
{

    _Nombre = pNombre;
    _NombreBasedeDatos = pBasedeDatos;
    _metaDato = new ListaMetaDato();
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

    metaDato *tmp = new metaDato(pNombre,pTipoDato);
    _metaDato->insertarFinal(tmp);
}

ListaMetaDato *tabla::getListaMetaDato()
{
    return _metaDato;
}
