#ifndef TABLA_H
#define TABLA_H

#include <string>
#include "ListaMetaDato.h"


using namespace std;
class tabla
{
public:

    tabla(string pNombre, string pNombreBasedeDatos);
    string getNombre();
    string getNombreBasedeDatos();
    void agregarMetaDatos(string pNombre, string pTipoDato);
    ListaMetaDato *getListaMetaDato();


private:
    string _Nombre;
    string _NombreBasedeDatos;
    ListaMetaDato *_metaDato;



};
#endif // TABLA_H
