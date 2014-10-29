#ifndef INTERPRETE_H
#define INTERPRETE_H
#include <string>
using namespace std;

class Interprete
{
public:

    Interprete();
    bool revisarSintaxis(string sentencia);
    bool ejecutar(string sentencia);

private:

    bool existeTabla(string tabla);
    bool existeColumna(string tabla,string columna);
    bool nombreValido(string nombre);
    bool datoValido(string dato);

    bool revisarCreateTable(string sentencia);
    bool revisarSelect(string sentencia);
    bool revisarInsert(string sentencia);
    bool revisarUpdate(string sentencia);
    bool revisarDelete(string sentencia);
    bool revisarCreateIndex(string sentencia);
    bool revisarCompress(string sentencia);
    bool revisarBackup(string sentencia);
    bool revisarRestore(string sentencia);

    bool ejecutarCreateTable(string sentencia);
    bool ejecutarSelect(string sentencia);
    bool ejecutarInsert(string sentencia);
    bool ejecutarUpdate(string sentencia);
    bool ejecutarDelete(string sentencia);
    bool ejecutarCreateIndex(string sentencia);
    bool ejecutarCompress(string sentencia);
    bool ejecutarBackup(string sentencia);
    bool ejecutarRestore(string sentencia);
};

#endif // INTERPRETE_H
