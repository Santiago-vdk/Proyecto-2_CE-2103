#include "facade.h"

Facade::Facade()
{
}

bool Facade::revizarSintaxis(string centencia)
{
    return _interprete.revisarSintaxis(centencia);
}

bool Facade::ejecutar(string centencia)
{
    return _interprete.ejecutar(centencia);
}
