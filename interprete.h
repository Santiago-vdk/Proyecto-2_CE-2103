#ifndef INTERPRETE_H
#define INTERPRETE_H
#include <string>
using namespace std;

class Interprete
{
public:

    Interprete();
    bool revisarSintaxis(string centencia);
    bool ejecutar(string centencia);

private:

    bool existeTabla(string tabla);
    bool existeColumna(string tabla,string columna);

    bool revisarCreateTable(string centencia);
    bool revisarSelect(string centencia);
    bool revisarInsert(string centencia);
    bool revisarUpdate(string centencia);
    bool revisarDelete(string centencia);
    bool revisarCreateIndex(string centencia);
    bool revisarCompress(string centencia);
    bool revisarBackup(string centencia);
    bool revisarRestore(string centencia);

    bool ejecutarCreateTable(string centencia);
    bool ejecutarSelect(string centencia);
    bool ejecutarInsert(string centencia);
    bool ejecutarUpdate(string centencia);
    bool ejecutarDelete(string centencia);
    bool ejecutarCreateIndex(string centencia);
    bool ejecutarCompress(string centencia);
    bool ejecutarBackup(string centencia);
    bool ejecutarRestore(string centencia);
};

#endif // INTERPRETE_H
