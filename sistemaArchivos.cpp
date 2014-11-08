#include "sistemaArchivos.h"
#include "ArchivoAleatorio.h"
#include "Registro.h"
#include "QDebug"

sistemaArchivos::sistemaArchivos()
{
}

bool sistemaArchivos::crearNuevaTabla(string pNombre)
{


    char *meta[3];
    meta[0] = "stanas";
    meta[1] = "cances";
    meta[2] = "nene";

    int caso = 0;

    for(int i = 0; i < 3; i++){
        ifstream f(meta[i]);
        if (f.good()) {
            f.close();
            caso = 2;
            break;
        } else {
            f.close();
            cout << "La tabla no existe, creando..." << endl;
            caso = 1;
            break;
        }
    }
    switch(caso){
    case 1:
    {
        cout << "CREANDO..." << endl;
        ArchivoAleatorio<Registro> archivo(pNombre); //Deberia revisar si no existe una con ese nombre
        if (archivo.openFile(truncate)){
            archivo.closeFile();
        }
        
    }
    case 2:
    {
        cout << "No se crea ya existe" << endl;
    }
    }











}
