#include "tabla.h"


tabla::tabla(string pNombre, string pBasedeDatos)
{

    _Nombre = pNombre;
    _NombreBasedeDatos = pBasedeDatos;


}

string tabla::getNombre()
{
    return _Nombre;
}

string tabla::getNombreBasedeDatos()
{
    return _NombreBasedeDatos;
}
