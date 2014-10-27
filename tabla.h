#ifndef TABLA_H
#define TABLA_H

#include <string>

using namespace std;
class tabla
{
public:

    tabla(string pNombre, string pNombreBasedeDatos);
    string getNombre();
    string getNombreBasedeDatos();


private:
    string _Nombre;
    string _NombreBasedeDatos;

};
#endif // TABLA_H
