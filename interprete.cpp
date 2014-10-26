#include "interprete.h"

Interprete::Interprete()
{

}

bool Interprete::revisarSintaxis(string centencia)
{
    //se obtiene la primera palabra y si coincide con alguna reservada se llama
    //al revisar correspondiente, sino retorna false directamente
    return true;

}

bool Interprete::ejecutar(string centencia)
{
    //es bool ya que retorna true si se ejecuto correctamente la centencia y false si
    //ocurrio un error, ej: la tabla o columna no existe
    return true;
}

bool Interprete::existeTabla(string tabla)
{
    //creo que aqui se utiliza un try/catch para que el programa no se caiga si no
    //encuentra la tabla
    return true;
}

bool Interprete::existeColumna(string tabla, string columna)
{
    //creo que aqui no se necesita un try/catch, dependiendo de como se almacenen los
    // datos en el archivo binario para leer los nombres de las columnas
    return true;
}



//***************************************************************



bool Interprete::revisarCreateTable(string centencia)
{
    //se revisa sintaxis de create table
    return true;
}

bool Interprete::revisarSelect(string centencia)
{
    //se revisa sintaxis de select
    return true;
}

bool Interprete::revisarInsert(string centencia)
{
    //se revisa sintaxis de insert
    return true;
}

bool Interprete::revisarUpdate(string centencia)
{
    //se revisa sintaxis de update
    return true;
}

bool Interprete::revisarDelete(string centencia)
{
    //se revisa sintaxis de delete
    return true;
}

bool Interprete::revisarCreateIndex(string centencia)
{
    //se revisa sintaxis de create index
    return true;
}

bool Interprete::revisarCompress(string centencia)
{
    //se revisa sintaxis de compress
    return true;
}

bool Interprete::revisarBackup(string centencia)
{
    //se revisa sintaxis de backup
    return true;
}

bool Interprete::revisarRestore(string centencia)
{
    //se revisa sintaxis de restore
    return true;
}


//***************************************************************



bool Interprete::ejecutarCreateTable(string centencia)
{
    //se ejecuta create table
    return true;
}

bool Interprete::ejecutarSelect(string centencia)
{
    //se ejecuta select
    return true;
}

bool Interprete::ejecutarInsert(string centencia)
{
    //se ejecuta insert
    return true;
}

bool Interprete::ejecutarUpdate(string centencia)
{
    //se ejecuta update
    return true;
}

bool Interprete::ejecutarDelete(string centencia)
{
    //se ejecuta delete
    return true;
}

bool Interprete::ejecutarCreateIndex(string centencia)
{
    //se ejecuta create index
    return true;
}

bool Interprete::ejecutarCompress(string centencia)
{
    //se ejecuta compress
    return true;
}

bool Interprete::ejecutarBackup(string centencia)
{
    //se ejecuta backup
    return true;
}

bool Interprete::ejecutarRestore(string centencia)
{
    //se ejecuta restore
    return true;
}
