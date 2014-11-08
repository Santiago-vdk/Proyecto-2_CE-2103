#ifndef FACADE_H
#define FACADE_H
#include <string>
#include "interprete.h"

#include "sistemaArchivos.h"

using namespace std;
class Facade
{
public:
    Facade();
    bool revizarSintaxis(string sentencia);//   estos metodos podrian devolver strings con
    bool ejecutar(string sentencia);//  errores mas directos para los msjs de error visuales
    Interprete * _interprete;




    sistemaArchivos *sis;
    void crearArchivo(string pNombre);



};

#endif // FACADE_H
