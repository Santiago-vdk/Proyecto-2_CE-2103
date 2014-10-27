#ifndef NODOTABLA_H
#define NODOTABLA_H

#include <tabla.h>

class nodoTabla
{
public:
    nodoTabla(tabla *dato);
    tabla *getTabla();
    nodoTabla* getTablaNext();
    nodoTabla* getTablaPrev();
    void setTablaNext(nodoTabla *pTablaNext);
    void setTablaPrev(nodoTabla *pTablaPrev);

    void setDato(tabla *pDato);

private:
    nodoTabla *_next=NULL;
    nodoTabla *_prev=NULL;
    tabla * _dato=NULL;

};

#endif // NODOTABLA_H
