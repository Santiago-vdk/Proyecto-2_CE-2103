#ifndef NODODATO_H
#define NODODATO_H
#include <string>

using namespace std;

class NodoDato
{
public:
    NodoDato(string pdato);

    string getDato();
    NodoDato *getNext();
    NodoDato *getPrev();

    void setNext(NodoDato *pnext);
    void setPrev(NodoDato *pprev);
    void setDato(string pDato);

private:
    string _dato;
    NodoDato *_next;
    NodoDato *_prev;
};


#endif // NODODATO_H
