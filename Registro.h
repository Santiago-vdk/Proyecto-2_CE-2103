/*
  Esta clase modela un registro de datos que puede ser
  leido o escrito en un archivo de accceso secuencial
*/

#ifndef REGISTRO_H
#define	REGISTRO_H

#include <string>

#include <iostream>

#include <fstream>
#include "metaDato.h"

#include "ListaMetaDato.h"

using namespace std;  //permite abrir 1 archivo para lectura y escritura simultaneamente

const int TAM_CEDULA = 10;
const int TAM_NOMBRE = 16;

class Registro{
    //friend ostream & operator<<(ostream &, const Registro &); //operador sobrecargado para desplegar un registro a la salida estandar
public:
    Registro();
    Registro(char *pDato); //constructor por defecto
    Registro(Registro &);



    bool operator==( Registro &);
    Registro & operator=( Registro &);  //utilizado para asignar un registro a otro
    bool write(fstream &);
    bool read(fstream &);

    char *getDato();




private:
    char  *_dato;

};
#endif



