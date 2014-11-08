#include "Registro.h"

#include <cstring>

#include <iostream>
using namespace std;

Registro::Registro( Registro & r){
    _dato = r.getDato();

}

Registro::Registro()
{
    _dato = "~";
}

Registro::Registro(char *pDato){
    _dato = pDato;
}

char *Registro::getDato()
{
    return _dato;
}


bool Registro::operator==( Registro & registro){
  return (strcmp(this->_dato,registro.getDato()) == 0);
}

Registro & Registro::operator=(Registro & registro){
  _dato = registro.getDato();
  return *this;
}


bool Registro::read(fstream & entrada){
  Registro r;
  entrada.clear();
  
  //Obliga al compilador a aceptar un tipo de objeto por otro sin cuestionar, por muy ilógica
  //que sea la transformación. Cabe destacar que este tipo de transformaciones son 
  //de lo más peligroso y que deben ser realizadas con extrema precaución
  entrada.read(reinterpret_cast<char *>(&r), sizeof(_dato));
  *this = r;
  return entrada.good();
}



bool Registro::write(fstream & salida){
  Registro r(*this);
  salida.clear();
  salida.write(reinterpret_cast<char *>(&r),sizeof(_dato));
  return salida.good();
}
