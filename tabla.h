#ifndef TABLA_H
#define TABLA_H

#include <string>
#include "ListaMetaDato.h"
#include "MatrizDato.h"
#include "ListaDato.h"

using namespace std;
class tabla
{
public:

    tabla(string pNombre, string pNombreBasedeDatos);
    string getNombre();
    string getNombreBasedeDatos();
    void agregarMetaDatos(string pNombre, string pTipoDato);
    ListaMetaDato *getListaMetaDato();
    MatrizDato * getMatrizDato();
    void insertarRegistro(ListaDato *pRegistro);
    void setMetaDato(string pMetaDato);
    ListaMetaDato *getMetaDato();
    void imprimirTabla();
    bool existeMetaDato(string pmetaDato);
    bool existeListaMetaDato(string plistaMetaDato);



private:
    string _Nombre;
    string _NombreBasedeDatos;
    ListaMetaDato *_metaDato;
    MatrizDato *_matrizDato;



};
#endif // TABLA_H
