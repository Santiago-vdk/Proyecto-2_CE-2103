#include "facade.h"
#include "sistemaArchivos.h"

Facade::Facade()
{

    sis = new sistemaArchivos();

}

bool Facade::revizarSintaxis(string sentencia)
{
    return _interprete.revisarSintaxis(sentencia);
}

bool Facade::ejecutar(string sentencia)
{
    return _interprete.ejecutar(sentencia);
}

void Facade::crearArchivo(string pNombre)
{
    sis->crearNuevaTabla(pNombre);
}
