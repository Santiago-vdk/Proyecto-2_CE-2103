#ifndef FACADE_H
#define FACADE_H
#include <string>
#include "interprete.h"
using namespace std;
class Facade
{
public:
    Facade();
    bool revizarSintaxis(string centencia);//   estos metodos podrian devolver strings con
    bool ejecutar(string centencia);//  errores mas directos para los msjs de error visuales
    Interprete _interprete;
};

#endif // FACADE_H
