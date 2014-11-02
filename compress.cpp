#include "compress.h"

compress::compress(char *Dire,char *Dird)
{
    _Dire=Dire;
    _Dird=Dird;
}

void compress::encode()
{
    QFile infile(_Dire);
    QFile outfile(_Dird);
    if (infile.exists()){
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);

    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qCompress(uncompressedData);

    outfile.write(compressedData);

    infile.close();
    outfile.close();
    remove(_Dire);
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","El archivo no existe!");
    }
}
void compress::decode()
{

    QFile outfile(_Dire);
    QFile infile(_Dird);
    if (infile.exists()){
    infile.open(QIODevice::ReadOnly);
    outfile.open(QIODevice::WriteOnly);

    QByteArray uncompressedData = infile.readAll();
    QByteArray compressedData = qUncompress(uncompressedData);

    outfile.write(compressedData);

    infile.close();
    outfile.close();
    remove(_Dird);
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","El archivo no existe!");
    }
}
