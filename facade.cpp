#include "facade.h"

Facade::Facade()
{
}

bool Facade::revizarSintaxis(string sentencia)
{
    return _interprete.revisarSintaxis(sentencia);
}

bool Facade::ejecutar(string sentencia)
{
    return _interprete.ejecutar(sentencia);
}
