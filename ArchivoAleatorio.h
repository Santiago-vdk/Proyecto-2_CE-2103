/*
  //MODIFICACION DEL PUNTERO DE LECTURA

  file.seekg(n);           //coloca el puntero de lectura del archivo en el n-esimo byte a partir del principio del archivo
  file.seekg(n,ios::beg);  //coloca el puntero de lectura del archivo en el n-esimo byte a partir del principio del archivo
  file.seekg(n,ios::cur);  //coloca el puntero de lectura del archivo en el n-esimo byte a partir de la posicion actual del puntero de lectura
  file.seekg(n,ios::end);  //coloca el puntero de lectura del archivo en el n-esimo byte a partir del fin del archivo (hacia atras)
  file.seekg(0,ios::end);  //coloca el puntero de lectura del archivo al final del mismo

  //MODIFICACION DEL PUNTERO DE ESCRITURA

  file.seekp(n);           //coloca el puntero de escritura del archivo en el n-esimo byte a partir del principio del archivo
  file.seekp(n,ios::beg);  //coloca el puntero de escritura del archivo en el n-esimo byte a partir del principio del archivo
  file.seekp(n,ios::cur);  //coloca el puntero de escritura del archivo en el n-esimo byte a partir de la posicion actual del puntero de escritura
  file.seekp(n,ios::end);  //coloca el puntero de escritura del archivo en el n-esimo byte a partir del fin del archivo (hacia atras)
  file.seekp(0,ios::end);  //coloca el puntero de escritura del archivo al final del mismo

  file.tellg(); //retorna la posicion actual (# de byte) del puntero de lectura
  file.tellp(); //retorna la posicion actual (# de byte) del puntero de escritura

*/

#ifndef ARCHIVOALEATORIO_H
#define	ARCHIVOALEATORIO_H

#include <fstream>

#include <string>

#include <iostream>
using namespace std;

enum openMode{truncate, append};

template <class TIPOREGISTRO>
class ArchivoAleatorio{
public:
    ArchivoAleatorio(const string &);
    bool openFile(openMode);
    bool closeFile();
    bool readRecord(TIPOREGISTRO &);
    bool writeRecord(TIPOREGISTRO &);
    bool isEOF() const;
    bool seek(TIPOREGISTRO &);
    bool seek(long);
    long getRecord(TIPOREGISTRO &);



    TIPOREGISTRO getFirstRecord();
    TIPOREGISTRO getRecordInPos(int i, TIPOREGISTRO registroTemp);

    bool reset();
    bool gotoEnd();
    bool gotoRecord(long);
    bool deleteRecord(TIPOREGISTRO &);
    bool updateRecord(TIPOREGISTRO &, TIPOREGISTRO &);


private:
    string fileName;
    fstream file;

};



template <class TIPOREGISTRO>
ArchivoAleatorio<TIPOREGISTRO>::ArchivoAleatorio(const string & fileName){
    this->fileName = fileName;
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::openFile(openMode mode){
    if (mode == append){ //si el archivo existe, se abre para lectura y agregar al final
        file.open(fileName.c_str(),ios::in | ios::out | ios::ate);
    }
    else{ // si el archivo no existe se crea y se abre para lectura y escritura

        file.open(fileName.c_str(),ios::in | ios::out | ios::trunc);
    }
    return (file ? true : false);
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::closeFile(){
    file.clear();
    file.close();
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::gotoEnd(){
    file.clear();
    file.seekg(0,ios::end);
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::reset(){
    file.clear();
    file.seekg(0);
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::gotoRecord(long n){
    file.clear();
    file.seekg((n-1)*sizeof(TIPOREGISTRO));
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::readRecord(TIPOREGISTRO & registro){
    file.clear();
    registro.read(file);
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::writeRecord(TIPOREGISTRO & registro){
    file.clear();
    registro.write(file);
    file.flush();
    return file.good();
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::isEOF() const{
    return file.eof();
}

//a diferencia del archivo secuencial este metodo retorna el numero de registro
//donde se encuentran los datos buscados
template <class TIPOREGISTRO>
long ArchivoAleatorio<TIPOREGISTRO>::getRecord(TIPOREGISTRO & registro){
    TIPOREGISTRO registroAux;
    bool encontrado = false;
    long posRegistro = 0;
    file.clear();
    long posActual = file.tellp();
    reset();
    //buscar el registro a partir de esa posicion
    while ((!file.eof()) && (!encontrado)){
        posRegistro++;
        registroAux.read(file);
        if (registroAux == registro){

            encontrado = true;
            registro = registroAux;

        }
    }
    seek(posActual);
    return (encontrado ? posRegistro : -1);
}


/*--------------------------------------------------------------*/

template <class TIPOREGISTRO>
TIPOREGISTRO ArchivoAleatorio<TIPOREGISTRO>::getFirstRecord(){
    TIPOREGISTRO registroAux;
    file.clear();
    reset();
    registroAux.read(file);
    return registroAux;
}


template <class TIPOREGISTRO>
TIPOREGISTRO ArchivoAleatorio<TIPOREGISTRO>::getRecordInPos(int i, TIPOREGISTRO registroTmp){
    TIPOREGISTRO registroAux;
    file.clear();
    reset();
    int j = 0;
    while ((j < i)    && !file.eof()){
        registroAux.read(file);
        j++;
    }
    if(file.eof()){
        cout << "Llegue al final del archivo" << endl;
        return registroTmp;
    }    return registroAux;


}

/*--------------------------------------------------------------*/




template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::seek(TIPOREGISTRO & registro){
    return (getRecord(registro) != -1 ? true : false);
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::seek(long n){
    file.clear();
    file.seekg(n);

    return file.good();
}



template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::deleteRecord(TIPOREGISTRO & registro){
    int pos = 0;
    long posActual = file.tellp();
    bool status = false;
    if ((pos = getRecord(registro)) != -1){
        gotoRecord(pos);
        TIPOREGISTRO registroEnBlanco;
        writeRecord(registroEnBlanco);
        status = true;
    }
    seek(posActual);
    return status;
}

template <class TIPOREGISTRO>
bool ArchivoAleatorio<TIPOREGISTRO>::updateRecord(TIPOREGISTRO & registroBuscar, TIPOREGISTRO & registroDatos){
    bool status = false;
    int pos = 0;
    long posActual = file.tellp();
    if ((pos = getRecord(registroBuscar)) != -1){
        gotoRecord(pos);
        writeRecord(registroDatos);
        status = true;
    }
    seek(posActual);
    return status;
}

#endif
