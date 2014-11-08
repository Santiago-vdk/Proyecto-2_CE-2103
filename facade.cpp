#include "facade.h"
#include "sistemaArchivos.h"

Facade::Facade()
{


    _interprete = new Interprete();

}

bool Facade::revizarSintaxis(string sentencia)
{
    return _interprete->revisarSintaxis(sentencia);
}

bool Facade::ejecutar(string sentencia)
{
    return _interprete->ejecutar(sentencia);
}


