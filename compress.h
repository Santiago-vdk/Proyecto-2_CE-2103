#ifndef COMPRESS_H
#define COMPRESS_H
#include <QByteArray>
#include <QFile>
#include <QMessageBox>
class compress
{
public:
    compress(char * Dire,char * Dird); //Recibe dos direcciones, la primera es el archivo a comprimir, la segunda es el archivo a descomprimir. si alguno de los dos no esta creado, el codigo lo crea automaticamente.
    void encode();
    void decode();
private:
    char * _Dire;
    char * _Dird;
};


#endif // COMPRESS_H
