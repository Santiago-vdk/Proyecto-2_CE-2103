#include "interprete.h"
#include <QDebug>
#include "iostream"
#include <dirent.h>
#include "nodoTabla.h"
#include "tabla.h"
using namespace std;

Interprete::Interprete()
{
    cargaTablas();
    sis = new sistemaArchivos();
    _listaTablas = new listaTabla();

}

bool Interprete::revisarSintaxis(string sentencia)
{
    //se obtiene la primera palabra y si coincide con alguna reservada se llama
    //al revisar correspondiente, sino retorna false directamente
    if (sentencia.find("CREATE TABLE")==0){
        return revisarCreateTable(sentencia);
    }
    if (sentencia.find("SELECT")==0){
        return revisarSelect(sentencia);
    }
    if (sentencia.find("INSERT INTO")==0){
        return revisarInsert(sentencia);
    }
    if (sentencia.find("UPDATE")==0){
        return revisarUpdate(sentencia);
    }
    if (sentencia.find("DELETE FROM")==0){
        return revisarDelete(sentencia);
    }
    if (sentencia.find("CREATE INDEX ON")==0){
        return revisarCreateIndex(sentencia);
    }
    if (sentencia.find("COMPRESS TABLE")==0){
        return revisarCompress(sentencia);
    }
    if (sentencia.find("BACKUP TABLE")==0){
        return revisarBackup(sentencia);
    }
    if (sentencia.find("RESTORE TABLE")==0){
        return revisarRestore(sentencia);
    }
    else{
        //aqui se deberia mostrar mensaje de error por no encontrar palabra reservada inicial
        return false;
    }
}

bool Interprete::ejecutar(string sentencia)
{
    //es bool ya que retorna true si se ejecuto correctamente la sentencia y false si
    //ocurrio un error, ej: la tabla o columna no existe
    if (sentencia.find("CREATE TABLE")==0){
        return ejecutarCreateTable(sentencia);
    }
    if (sentencia.find("SELECT")==0){
        return ejecutarSelect(sentencia);
    }
    if (sentencia.find("INSERT INTO")==0){
        return ejecutarInsert(sentencia);
    }
    if (sentencia.find("UPDATE")==0){
        return ejecutarUpdate(sentencia);
    }
    if (sentencia.find("DELETE FROM")==0){
        return ejecutarDelete(sentencia);
    }
    if (sentencia.find("CREATE INDEX ON")==0){
        return ejecutarCreateIndex(sentencia);
    }
    if (sentencia.find("COMPRESS TABLE")==0){
        return ejecutarCompress(sentencia);
    }
    if (sentencia.find("BACKUP TABLE")==0){
        return ejecutarBackup(sentencia);
    }
    if (sentencia.find("RESTORE TABLE")==0){
        return ejecutarRestore(sentencia);
    }
    else{
        //nunca deberia entrar aqui si las funciones revisar funcionar correctamente
        return false;
    }
}

bool Interprete::existeTabla(string ptabla)
{

    for(int i = 0;i<_listaTablas->getTamanio();i++){
        tabla *tmp = _listaTablas->buscarTablaEnPos(i);
        if(ptabla.compare(tmp->getNombre())==0){
            return true;
        }
    }
    return false;
}

bool Interprete::existeColumna(tabla *ptabla, string columna)
{
    return ptabla->existeMetaDato(columna);
}

bool Interprete::nombreValido(string nombre)
{
    if(nombre.find(" ")==0){
        nombre = nombre.substr(1,nombre.length()-1);
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }
    if((nombre.length()>0)&&(nombre.length()<30)){
        if((nombre.find(",")==string::npos)&&(nombre.find("'")==string::npos)&&
                (nombre.find("\"")==string::npos)&&(nombre.find(".")==string::npos)&&
                (nombre.find(";")==string::npos) &&
                (nombre.find(":")==string::npos)){//condicion agregada
            return true;

        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Interprete::datoValido(string dato)
{
    if(dato.find(" ")==0){
        dato = dato.substr(1,dato.length()-1);
    }
    if(dato.find(" ")==dato.length()-1){
        dato = dato.substr(0,dato.length()-2);
    }
    if(dato.compare("Integer")==0||dato.compare("String")==0||dato.compare("Decimal")==0){
        return true;
    }
    else{
        return false;
    }
}

int Interprete::cumpleWhere(tabla *ptabla, string pcondiciones, int ppos)
{
    cout<<"EntreWhere:"<<pcondiciones<<endl;
    string AndOr = "";
    int condicionAnterior = -1;
    string token1="";
    bool banderaEntreIf = false;
    while(pcondiciones.find("AND")!=string::npos || pcondiciones.find("OR")!=string::npos){
        //********* EN este par de ifs revisa si el mas proximo es un or o un and

        if(pcondiciones.find("AND")<pcondiciones.find("OR")){
            token1 = pcondiciones.substr(0,pcondiciones.find("AND")-1);
            pcondiciones=pcondiciones.substr(pcondiciones.find("AND")+3,pcondiciones.length());
            AndOr="AND";
            if(token1.find(" ")==0){
                token1=token1.substr(1,token1.length());
            }
            if(token1.find(" ")==token1.length()-1){
                token1=token1.substr(0,token1.length()-2);
            }
        }
        if(pcondiciones.find("AND")>pcondiciones.find("OR")){
            token1 = pcondiciones.substr(0,pcondiciones.find("OR")-1);
            pcondiciones=pcondiciones.substr(pcondiciones.find("OR")+2,pcondiciones.length());
            AndOr="OR";
            if(token1.find(" ")==0){
                token1=token1.substr(1,token1.length());
            }
            if(token1.find(" ")==token1.length()-1){
                token1=token1.substr(0,token1.length()-2);
            }
        }
        //********
        cout<<"pcondicionesEnWhere:"<<pcondiciones<<endl;

        //********************** verifica los signos de comparacion
        if(token1.find("<>")!= string::npos){
            cout<<"entre <>"<<endl;
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find("<>")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find("<>")+2,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            cout<<"campo:"<<campo<<" valor:"<<valor<<endl;
            if(ptabla->existeMetaDato(campo)){
                if(condicionAnterior ==-1){

                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                        condicionAnterior=1;
                    }
                    else {
                        condicionAnterior=0;
                    }
                }
                else{
                    if(AndOr=="AND"){
                        if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                            if(condicionAnterior==1){
                                condicionAnterior=1;
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                            condicionAnterior=1;
                        }
                        else{
                            if(condicionAnterior==1){
                                condicionAnterior=1;
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                    }
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }

        //********************** verifica los signos de comparacion
        if(token1.find(">=")!= string::npos){
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find(">=")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find(">=")+2,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            if(ptabla->existeMetaDato(campo)){
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                        ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){

                    std::string str = valor;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    int testInt;
                    float testFloat;
                    int valorIntEnTabla;
                    float valorFloatEnTabla;
                    string banderaIntFloat;

                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                        banderaIntFloat = "Integer";
                        testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                        banderaIntFloat = "Decimal";
                        testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ok){

                        if(condicionAnterior ==-1){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                                condicionAnterior=1;
                            }
                            else {
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if(AndOr=="AND"){
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                                    condicionAnterior=1;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                    }
                    if(!ok){
                        if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                            if(condicionAnterior ==-1){
                                condicionAnterior=0;
                            }
                            else{
                                if(AndOr=="AND"){
                                    condicionAnterior=0;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                        else{
                            return -1;//valor no es un numero
                        }
                    }


                }
                else{
                    return -1; //error comparacion invalida
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }


        if(token1.find("<=")!= string::npos){
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find("<=")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find("<=")+2,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            if(ptabla->existeMetaDato(campo)){
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                        ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                    std::string str = valor;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    int testInt;
                    float testFloat;
                    int valorIntEnTabla;
                    float valorFloatEnTabla;
                    string banderaIntFloat;

                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                        banderaIntFloat = "Integer";
                        testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                        banderaIntFloat = "Decimal";
                        testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ok){

                        if(condicionAnterior ==-1){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                                condicionAnterior=1;
                            }
                            else {
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if(AndOr=="AND"){
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                                    condicionAnterior=1;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                    }
                    if(!ok){
                        if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                            if(condicionAnterior ==-1){
                                condicionAnterior=0;
                            }
                            else{
                                if(AndOr=="AND"){
                                    condicionAnterior=0;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                        else{
                            return -1;//valor no es un numero
                        }
                    }
                }
                else{
                    return -1; //error comparacion invalida
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }

        if(token1.find(">")!= string::npos && token1.find(">=")== string::npos && token1.find("<>")== string::npos){
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find(">")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find(">")+1,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            if(ptabla->existeMetaDato(campo)){
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                        ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                    std::string str = valor;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    int testInt;
                    float testFloat;
                    int valorIntEnTabla;
                    float valorFloatEnTabla;
                    string banderaIntFloat;

                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                        banderaIntFloat = "Integer";
                        testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                        banderaIntFloat = "Decimal";
                        testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ok){

                        if(condicionAnterior ==-1){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                                condicionAnterior=1;
                            }
                            else {
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if(AndOr=="AND"){
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                                    condicionAnterior=1;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                    }
                    if(!ok){
                        if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                            if(condicionAnterior ==-1){
                                condicionAnterior=0;
                            }
                            else{
                                if(AndOr=="AND"){
                                    condicionAnterior=0;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                        else{
                            return -1;//valor no es un numero
                        }
                    }
                }
                else{
                    return -1; //error comparacion invalida
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }

        if(token1.find("<")!= string::npos && token1.find("<=")== string::npos && token1.find("<>")== string::npos){
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find("<")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find("<")+1,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            if(ptabla->existeMetaDato(campo)){
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                        ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                    std::string str = valor;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    int testInt;
                    float testFloat;
                    int valorIntEnTabla;
                    float valorFloatEnTabla;
                    string banderaIntFloat;

                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                        banderaIntFloat = "Integer";
                        testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                        banderaIntFloat = "Decimal";
                        testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                        std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                        QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                        valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                    }
                    if(ok){

                        if(condicionAnterior ==-1){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                                condicionAnterior=1;
                            }
                            else {
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if(AndOr=="AND"){
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                                    condicionAnterior=1;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                    }
                    if(!ok){
                        if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                            if(condicionAnterior ==-1){
                                condicionAnterior=0;
                            }
                            else{
                                if(AndOr=="AND"){
                                    condicionAnterior=0;
                                }
                                else{
                                    if(condicionAnterior==1){
                                        condicionAnterior=1;
                                    }
                                    else{
                                        condicionAnterior=0;
                                    }
                                }
                            }
                        }
                        else{
                            return -1;//valor no es un numero
                        }
                    }
                }
                else{
                    return -1; //error comparacion invalida
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }

        if(token1.find("=")!= string::npos && token1.find("<=")== string::npos && token1.find(">=")== string::npos){
            banderaEntreIf = true;
            string campo=token1.substr(0,token1.find("=")-1);
            if(campo.find(" ")==0){
                campo=campo.substr(1,campo.length());
            }
            if(campo.find(" ")==campo.length()-1){
                campo=campo.substr(0,campo.length()-2);
            }
            string valor=token1.substr(token1.find("=")+1,token1.length());
            if(valor.find(" ")==0){
                valor=valor.substr(1,valor.length());
            }
            if(valor.find(" ")==valor.length()-1){
                valor=valor.substr(0,valor.length()-2);
            }

            if(ptabla->existeMetaDato(campo)){
                if(condicionAnterior ==-1){
                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                        condicionAnterior=1;
                    }
                    else {
                        condicionAnterior=0;
                    }
                }
                else{
                    if(AndOr=="AND"){
                        if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                            if(condicionAnterior==1){
                                condicionAnterior=1;
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                            condicionAnterior=1;
                        }
                        else{
                            if(condicionAnterior==1){
                                condicionAnterior=1;
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                    }
                }
            }
            else{
                //error no existe la columna
                return -1;
            }
        }
        if(!banderaEntreIf){
            return -1;//no encontro operando valido
        }
        banderaEntreIf = false;

    }//cierra el while


 //en este punto falta la evaluacion de la ultima comparacion ya que
 //el while se sale al no encontrar mas AND u OR por lo que se necesita
 //duplicar el codigo del while para la evaluacion final y hacer el return

    token1 = pcondiciones;
    cout<<"token1FueraWhile:"<<token1<<endl;

    if(token1.find("<>")!= string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find("<>")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find("<>")+2,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }

        if(ptabla->existeMetaDato(campo)){
            if(condicionAnterior ==-1){
                if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                    condicionAnterior=1;
                }
                else {
                    condicionAnterior=0;
                }
            }
            else{
                if(AndOr=="AND"){
                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                        if(condicionAnterior==1){
                            condicionAnterior=1;
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                    else{
                        condicionAnterior=0;
                    }
                }
                else{
                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)!=0){
                        condicionAnterior=1;
                    }
                    else{
                        if(condicionAnterior==1){
                            condicionAnterior=1;
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                }
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }

    if(token1.find(">=")!= string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find(">=")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find(">=")+2,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }

        if(ptabla->existeMetaDato(campo)){
            if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                    ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){

                std::string str = valor;
                QString test = QString::fromStdString(str);
                bool ok;
                int testInt;
                float testFloat;
                int valorIntEnTabla;
                float valorFloatEnTabla;
                string banderaIntFloat;

                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                    banderaIntFloat = "Integer";
                    testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                    banderaIntFloat = "Decimal";
                    testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ok){

                    if(condicionAnterior ==-1){
                        if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                            condicionAnterior=1;
                        }
                        else {
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(AndOr=="AND"){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>=testFloat)){
                                condicionAnterior=1;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                }
                if(!ok){
                    if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                        if(condicionAnterior ==-1){
                            condicionAnterior=0;
                        }
                        else{
                            if(AndOr=="AND"){
                                condicionAnterior=0;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                    else{
                        return -1;//valor no es un numero
                    }
                }
            }
            else{
                return -1; //error comparacion invalida
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }

    if(token1.find("<=")!= string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find("<=")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find("<=")+2,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }

        if(ptabla->existeMetaDato(campo)){
            if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                    ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                std::string str = valor;
                QString test = QString::fromStdString(str);
                bool ok;
                int testInt;
                float testFloat;
                int valorIntEnTabla;
                float valorFloatEnTabla;
                string banderaIntFloat;

                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                    banderaIntFloat = "Integer";
                    testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                    banderaIntFloat = "Decimal";
                    testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ok){

                    if(condicionAnterior ==-1){
                        if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                            condicionAnterior=1;
                        }
                        else {
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(AndOr=="AND"){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<=testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<=testFloat)){
                                condicionAnterior=1;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                }
                if(!ok){
                    if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                        if(condicionAnterior ==-1){
                            condicionAnterior=0;
                        }
                        else{
                            if(AndOr=="AND"){
                                condicionAnterior=0;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                    else{
                        return -1;//valor no es un numero
                    }
                }
            }
            else{
                return -1; //error comparacion invalida
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }

    if(token1.find(">")!= string::npos && token1.find(">=")== string::npos && token1.find("<>")== string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find(">")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find(">")+1,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }

        if(ptabla->existeMetaDato(campo)){
            if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                    ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                std::string str = valor;
                QString test = QString::fromStdString(str);
                bool ok;
                int testInt;
                float testFloat;
                int valorIntEnTabla;
                float valorFloatEnTabla;
                string banderaIntFloat;

                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                    banderaIntFloat = "Integer";
                    testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                    banderaIntFloat = "Decimal";
                    testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ok){

                    if(condicionAnterior ==-1){
                        if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                            condicionAnterior=1;
                        }
                        else {
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(AndOr=="AND"){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla>testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla>testFloat)){
                                condicionAnterior=1;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                }
                if(!ok){
                    if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                        if(condicionAnterior ==-1){
                            condicionAnterior=0;
                        }
                        else{
                            if(AndOr=="AND"){
                                condicionAnterior=0;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                    else{
                        return -1;//valor no es un numero
                    }
                }
            }
            else{
                return -1; //error comparacion invalida
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }

    if(token1.find("<")!= string::npos && token1.find("<=")== string::npos && token1.find("<>")== string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find("<")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find("<")+1,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }

        if(ptabla->existeMetaDato(campo)){
            if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Integer") ==0 ||
                    ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getmetaDato().compare("Decimal") ==0){
                std::string str = valor;
                QString test = QString::fromStdString(str);
                bool ok;
                int testInt;
                float testFloat;
                int valorIntEnTabla;
                float valorFloatEnTabla;
                string banderaIntFloat;

                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Integer") ==0){
                    banderaIntFloat = "Integer";
                    testInt = test.toInt(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorIntEnTabla = QstringEnTabla.toInt();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ptabla->getMetaDato()->buscarPosicion(ptabla->getMetaDato()->PosMetaDato(campo))->getTipometaDato().compare("Decimal") ==0){

                    banderaIntFloat = "Decimal";
                    testFloat = test.toFloat(&ok);//convierte el valor que se desea comparar a int

                    std::string stringEnTabla = ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo));
                    QString QstringEnTabla = QString::fromStdString(stringEnTabla);
                    valorFloatEnTabla = QstringEnTabla.toFloat();//convierte el valor de la tabla con el cual se queire comparar

                }
                if(ok){

                    if(condicionAnterior ==-1){
                        if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                            condicionAnterior=1;
                        }
                        else {
                            condicionAnterior=0;
                        }
                    }
                    else{
                        if(AndOr=="AND"){
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                            else{
                                condicionAnterior=0;
                            }
                        }
                        else{
                            if((banderaIntFloat.compare("Integer")==0 && valorIntEnTabla<testInt)|| (banderaIntFloat.compare("Decimal")==0 && valorFloatEnTabla<testFloat)){
                                condicionAnterior=1;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                }
                if(!ok){
                    if(valor.compare("~")==0){//caso de espacio vacio en columna se toma como que no cumple condicion
                        if(condicionAnterior ==-1){
                            condicionAnterior=0;
                        }
                        else{
                            if(AndOr=="AND"){
                                condicionAnterior=0;
                            }
                            else{
                                if(condicionAnterior==1){
                                    condicionAnterior=1;
                                }
                                else{
                                    condicionAnterior=0;
                                }
                            }
                        }
                    }
                    else{
                        return -1;//valor no es un numero
                    }
                }
            }
            else{
                return -1; //error comparacion invalida
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }

    if(token1.find("=")!= string::npos && token1.find("<=")== string::npos && token1.find(">=")== string::npos){
        banderaEntreIf = true;
        string campo=token1.substr(0,token1.find("=")-1);
        if(campo.find(" ")==0){
            campo=campo.substr(1,campo.length());
        }
        if(campo.find(" ")==campo.length()-1){
            campo=campo.substr(0,campo.length()-2);
        }
        string valor=token1.substr(token1.find("=")+1,token1.length());
        if(valor.find(" ")==0){
            valor=valor.substr(1,valor.length());
        }
        if(valor.find(" ")==valor.length()-1){
            valor=valor.substr(0,valor.length()-2);
        }
        cout<<"=fueradelWhere:"<<AndOr<<"condicionAnterior:"<<condicionAnterior<<endl;
        if(ptabla->existeMetaDato(campo)){
            if(condicionAnterior ==-1){
                if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                    condicionAnterior=1;
                }
                else {
                    condicionAnterior=0;
                }
            }
            else{
                if(AndOr=="AND"){
                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                        if(condicionAnterior==1){
                            condicionAnterior=1;
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                    else{
                        condicionAnterior=0;
                    }
                }
                else{
                    if(ptabla->getMatrizDato()->buscarDatoEnPos(ppos,ptabla->getMetaDato()->PosMetaDato(campo)).compare(valor)==0){
                        condicionAnterior=1;
                    }
                    else{
                        if(condicionAnterior==1){
                            condicionAnterior=1;
                        }
                        else{
                            condicionAnterior=0;
                        }
                    }
                }
            }
        }
        else{
            //error no existe la columna
            return -1;
        }
    }
    if(banderaEntreIf){//returna lo que haya quedado en el resultado temporal solo si entro a uno de los if de comparacion fuera del while
        return condicionAnterior;
    }
    if(!banderaEntreIf){
        return -1;//no se encontro operando valido
    }

}//cierra funcion cumpleWhere



//***************************************************************



bool Interprete::revisarCreateTable(string sentencia)//se revisa sintaxis de create table
{
    if((sentencia.find(" ",7)==12)){
        if(sentencia.find("(")!=string::npos && sentencia.find("(")>13 && sentencia.find(" ",(sentencia.find(" ",7)+1))==sentencia.find("(")-1){
            string token1=sentencia.substr(13,sentencia.find("(")-14);//con la resta obtengo los caracteres entre ambas posiciones
            if(nombreValido(token1)){
                if(sentencia.find(")") == sentencia.length()-1){

                    string token2=sentencia.substr(sentencia.find("(")+1,sentencia.length()-1);
                    while(token2.find(",")!=string::npos){
                        if(token2.find(":")!=string::npos && token2.find(":")<token2.find(",")){
                            string tokenColumna = token2.substr(0,token2.find(":"));
                            string tokenDato = token2.substr(token2.find(":")+1,token2.find(",")-token2.find(":")-1);
                            if(nombreValido(tokenColumna) && datoValido(tokenDato)){
                                token2=token2.substr(token2.find(",")+1,token2.length()-1);
                            }
                            else{
                                //nombre de columna o tipo de dato invalidos
                                return false;
                            }
                        }
                        else{
                            //error con : o ,
                            return false;
                        }
                    }
                    string tokenColumna = token2.substr(0,token2.find(":"));
                    string tokenDato = token2.substr(token2.find(":")+1,token2.length()-token2.find(":")-2);
                    if(nombreValido(tokenColumna) && datoValido(tokenDato)){
                        return true;
                    }
                    else{
                        //nombre de columna o tipo de dato invalidos
                        return false;
                    }

                }

                else{
                    //falta cerrar parentesis o hay caracteres despues de cerrar parentesis
                    return false;
                }
            }
            else{
                //nombre invalido
                return false;
            }
        }
        else{
            //no abre parentesis
            return false;
        }
    }
    else{
        //error no se dejo espacio luego de la palabra reservada
        return false;
    }


}


bool Interprete::revisarSelect(string sentencia)//se revisa sintaxis de select
{
    if((sentencia.find(" ")==6)){
        if((sentencia.find("FROM")!=string::npos)&&(sentencia.find("FROM")>8)&&(sentencia.length()>=15)){
            if(sentencia.find("WHERE")!=string::npos){//validacion con WHERE
                if(sentencia.find(" ",sentencia.find("FROM"))==sentencia.find("FROM")+4 && sentencia.find(" ",sentencia.find("FROM")+5)==sentencia.find("WHERE")-1){
                    string token2 = sentencia.substr(sentencia.find("WHERE")+6,sentencia.length()-sentencia.find("WHERE")+5);
                    while(token2.length()!=0){
                        if(token2.find(" ")!=string::npos && token2.find(" ")!=0){
                            token2 = token2.substr(token2.find(" ")+1,token2.length()-1);
                            if (token2.find(" ")!=string::npos && token2.find(" ")!=0){
                                string operador=token2.substr(0,token2.find(" "));
                                if(operador.compare("=") || operador.compare("<>") || operador.compare(">") ||
                                        operador.compare(">=") || operador.compare("<") || operador.compare("<=")){

                                    if (token2.find(" ")!=string::npos){
                                        token2 = token2.substr(token2.find(" ")+1,token2.length()-1);
                                        if(token2.length()>0){
                                            if (token2.find(" ")==string::npos){
                                                return true;//condicion con una unica comparacion
                                            }
                                            else if(token2.find("OR ")!=0 && token2.find("OR ")!= string::npos){
                                                token2=token2.substr(token2.find("OR ")+3,token2.length()-token2.find("OR ")-3);
                                            }
                                            else if((token2.find("AND ")!=0) && (token2.find("AND ")!= string::npos)){

                                                token2=token2.substr(token2.find("AND ")+4,token2.length()-token2.find("AND ")-4);//vuelve a entrar al while
                                            }

                                            else{
                                                return false;//falta palabra reservada OR o AND
                                            }

                                        }
                                        else{
                                            return false;//espacios faltantes o indebidos
                                        }
                                    }
                                    else{
                                        return false;//operador invalido
                                    }
                                }
                                else{
                                    return false;//espacios de mas o no dejo espacios
                                }

                            }
                            else{
                                return false;//espacios de mas o no dejo espacios
                            }

                        }
                        else{
                            return false;//errores en las comparaciones
                        }
                    }
                }
                else{
                    return false;
                }
            }
            else{//validacion sin WHERE
                if(sentencia.find(" ",sentencia.find("FROM"))== sentencia.find("FROM")+4){
                    string token1 = sentencia.substr(sentencia.find(" ",sentencia.find("FROM"))+1,
                                                     sentencia.length()-sentencia.find(" ",sentencia.find("FROM")));

                    if(token1.find(" ")==string::npos){
                        return true;
                    }
                    else{
                        //sobran espacios
                        return false;
                    }
                }

                else{
                    //faltan espacios
                    return false;
                }
            }

        }
        else{
            return false;
        }

    }
    else{
        return false;
    }

}

bool Interprete::revisarInsert(string sentencia)//se revisa sintaxis de insert
{
    if(sentencia.find(" ",7)==11){
        if(sentencia.length()>26 && sentencia.find("(")!=string::npos && sentencia.find("(")>12){
            if(sentencia.find(")")!=string::npos && sentencia.find(")")>14){
                if(sentencia.find("VALUES")!=string::npos && sentencia.find("VALUES")>sentencia.find(")")){
                    if(sentencia.find("(",sentencia.find("VALUES"))!=string::npos){
                        if(sentencia.find(")",sentencia.find("VALUES"))!=string::npos &&
                                sentencia.find(")",sentencia.find("VALUES")) >
                                sentencia.find("(",sentencia.find("VALUES"))+1){
                            if(sentencia.find(")",sentencia.find("VALUES"))==sentencia.length()-1){

                                string token1 = sentencia.substr(sentencia.find("("),sentencia.find(")")-sentencia.find("("));
                                string token2 = sentencia.substr(sentencia.find("(",sentencia.find("VALUES")),sentencia.find(")",sentencia.find("VALUES"))-sentencia.find("(",sentencia.find("VALUES")));

                                while(token1.find(",")!=string::npos && token2.find(",")!=string::npos){
                                    cout<<"token1:"<<token1<<" token2:"<<token2<<endl;
                                    token1 = token1.substr(token1.find(",")+1, token1.length());
                                    token2 = token2.substr(token2.find(",")+1, token2.length());
                                }
                                cout<<"token1:"<<token1<<" token2:"<<token2<<endl;
                                if(token1.find(",")==string::npos && token2.find(",")==string::npos){

                                    return true;//misma cantidad de comas en el set y los values
                                }
                                else{
                                    return false;
                                }

                            }
                            else{
                                return false;//caracteres luego de cerrar segundo parentesis
                            }

                        }
                        else{
                            return false;//no cerro segundo parentesis o parentesis vacios
                        }
                    }
                    else{
                        return false;//no abrio segundo parentesis
                    }
                }
                else{
                    return false;//no se encontro la palabra reservada VALUES
                }
            }
            else{
                return false;//error no cerro parentesis
            }
        }
        else{
            return false;//error no abre abrir parentesis
        }
    }
    else{
        return false;
    }

}

bool Interprete::revisarUpdate(string sentencia)//se revisa sintaxis de update
{
    if(sentencia.find(" ")==6){
        string token1 = sentencia.substr(7,sentencia.length()-7);
        if(token1.find("SET")!= string::npos && token1.find("SET")>0){

            string igualaciones=token1.substr(token1.find("SET")+4,token1.find("WHERE")-token1.find("SET")-5);

            while(igualaciones.length()>0){
                if(igualaciones.find("=")!=string::npos && igualaciones.find("=")>1){
                    if(igualaciones.find(",")!=string::npos && igualaciones.find(",")>igualaciones.find("=")+1){
                        igualaciones=igualaciones.substr(igualaciones.find(",")+1,igualaciones.length()-igualaciones.find(","));
                        if(igualaciones.find(" ")==0){
                            igualaciones=igualaciones.substr(1,igualaciones.length()-1);
                        }
                    }
                    else if(igualaciones.find(" ",igualaciones.find("=")+2)!=string::npos){
                        return false;//error espacios de mas
                    }
                    else{
                        igualaciones="";//lo saca del while
                    }
                }
                else{
                    return false;// falta signo =
                }
            }
            if(token1.find("WHERE")!= string::npos){

                string token2=token1.substr(token1.find("WHERE")+6,token1.length()-token1.find("WHERE")-6);
                while(token2.length()!=0){
                    if(token2.find(" ")!=string::npos && token2.find(" ")!=0){
                        token2 = token2.substr(token2.find(" ")+1,token2.length()-1);
                        if (token2.find(" ")!=string::npos && token2.find(" ")!=0){
                            string operador=token2.substr(0,token2.find(" "));
                            if(operador.compare("=") || operador.compare("<>") || operador.compare(">") ||
                                    operador.compare(">=") || operador.compare("<") || operador.compare("<=")){

                                if (token2.find(" ")!=string::npos){
                                    token2 = token2.substr(token2.find(" ")+1,token2.length()-1);
                                    if(token2.length()>0){
                                        if (token2.find(" ")==string::npos){
                                            return true;//condicion con una unica comparacion
                                        }
                                        else if(token2.find("OR ")!=0 && token2.find("OR ")!= string::npos){
                                            token2=token2.substr(token2.find("OR ")+3,token2.length()-token2.find("OR ")-3);
                                        }
                                        else if((token2.find("AND ")!=0) && (token2.find("AND ")!= string::npos)){

                                            token2=token2.substr(token2.find("AND ")+4,token2.length()-token2.find("AND ")-4);//vuelve a entrar al while
                                        }

                                        else{
                                            return false;//falta palabra reservada OR o AND
                                        }

                                    }
                                    else{
                                        return false;//espacios faltantes o indebidos
                                    }
                                }
                                else{
                                    return false;//operador invalido
                                }
                            }
                            else{
                                return false;//espacios de mas o no dejo espacios
                            }

                        }
                        else{
                            return false;//espacios de mas o no dejo espacios
                        }

                    }
                    else{
                        return false;//errores en las comparaciones
                    }
                }

            }
            else{
                return true;//caso sin WHERE
            }
        }
        else{
            return false;//falta palabra reservada SET
        }
    }
    else{
        return false;//no dejo espacio luego de palabra reservada
    }
}

bool Interprete::revisarDelete(string sentencia)//se revisa sintaxis de delete
{

    if(sentencia.find(" ",7)==11){
        if(sentencia.find("WHERE")!=string::npos && sentencia.find("WHERE")>12 && sentencia.find(" ",sentencia.find("WHERE"))==sentencia.find("WHERE")+5){
            string token1=sentencia.substr(sentencia.find("WHERE")+6,sentencia.length()-sentencia.find("WHERE")+4);
            while(token1.length()!=0){
                if(token1.find(" ")!=string::npos && token1.find(" ")!=0){
                    token1 = token1.substr(token1.find(" ")+1,token1.length()-1);
                    if (token1.find(" ")!=string::npos && token1.find(" ")!=0){
                        string operador=token1.substr(0,token1.find(" "));
                        if(operador.compare("=") || operador.compare("<>") || operador.compare(">") ||
                                operador.compare(">=") || operador.compare("<") || operador.compare("<=")){

                            if (token1.find(" ")!=string::npos){
                                token1 = token1.substr(token1.find(" ")+1,token1.length()-1);
                                if(token1.length()>0){
                                    if (token1.find(" ")==string::npos){
                                        return true;//condicion con una unica comparacion
                                    }
                                    else if(token1.find("OR ")!=0 && token1.find("OR ")!= string::npos){
                                        token1=token1.substr(token1.find("OR ")+3,token1.length()-token1.find("OR ")-3);
                                    }
                                    else if((token1.find("AND ")!=0) && (token1.find("AND ")!= string::npos)){

                                        token1=token1.substr(token1.find("AND ")+4,token1.length()-token1.find("AND ")-4);//vuelve a entrar al while
                                    }

                                    else{
                                        return false;//falta palabra reservada OR o AND
                                    }

                                }
                                else{
                                    return false;//espacios faltantes o indebidos
                                }
                            }
                            else{
                                return false;//operador invalido
                            }
                        }
                        else{
                            return false;//espacios de mas o no dejo espacios
                        }

                    }
                    else{
                        return false;//espacios de mas o no dejo espacios
                    }

                }
                else{
                    return false;//errores en las comparaciones
                }
            }
            return true;
        }
        else{
            return false;//no se encontro palabra reservada WHERE
        }
    }
    else{
        return false;//no dejo espacio luego de frase reservada inicial
    }
}





bool Interprete::revisarCreateIndex(string sentencia)//se revisa sintaxis de create index
{
    cout<<sentencia.length()<<" "<<sentencia.find(" ",13)<<" "<<sentencia.find("(")<<" "<<sentencia.find(")")<<endl;
    if(sentencia.length()>20 && sentencia.find(" ",13)==15){
        if(sentencia.find("(")!=string::npos && sentencia.find("(")>16){

            if(sentencia.find(")")!=string::npos && sentencia.find(")")==sentencia.length()-1 &&
                    sentencia.find(")")>sentencia.find("(")+2){
                return true;
            }
            else{
                return false;
            }

        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Interprete::revisarCompress(string sentencia)//se revisa sintaxis de compress
{
    if(sentencia.length()>15 && sentencia.find(" ",9)==14 && sentencia.find(" ",15)==string::npos){
        return true;
    }
    else{
        return false;
    }

}

bool Interprete::revisarBackup(string sentencia)//se revisa sintaxis de backup
{
    if(sentencia.length()>13 && sentencia.find(" ",8)==12 && sentencia.find(" ",13)==string::npos){
        return true;
    }
    else{
        return false;
    }

}

bool Interprete::revisarRestore(string sentencia)//se revisa sintaxis de restore
{
    if(sentencia.length()>13 && sentencia.find(" ",8)==13 && sentencia.find(" ",14)==string::npos){
        return true;
    }
    else{
        return false;
    }
}


//***************************************************************



bool Interprete::ejecutarCreateTable(string sentencia)//se ejecuta create table
{

    string nombre = sentencia.substr(13,sentencia.find("(")-13);
    if(nombre.find(" ")==0){
        nombre=nombre.substr(1,nombre.length()-1);
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-1);
    }
    if(existeTabla(nombre)){
        //error ya existe tabla con ese nombre
        cout<<"ya existe la tabla"<<endl;
    }
    else{
        _listaTablas->insertarFinal(nombre,"base de datos");
        sentencia = sentencia.substr(sentencia.find("(")+1,sentencia.length() - sentencia.find("("));
        while(sentencia.find(",")!=string::npos){
            string columna = sentencia.substr(0,sentencia.find(":"));
            //los if eliminan un espacio al inicio o al final en caso de que se encuentre alguno
            if(columna.find(" ")==0){
                columna=columna.substr(1,columna.length()-1);
            }
            if(columna.find(" ")==columna.length()-1){
                columna= columna.substr(0,columna.length()-2);
            }
            //
            string tipoDato = sentencia.substr(sentencia.find(":")+1,sentencia.find(",")-sentencia.find(":")-1);
            //
            if(tipoDato.find(" ")==0){
                tipoDato=tipoDato.substr(1,tipoDato.length()-1);
            }
            if(tipoDato.find(" ")==tipoDato.length()-1){
                tipoDato= tipoDato.substr(0,tipoDato.length()-2);
            }
            //
            _listaTablas->getTail()->getTabla()->agregarMetaDatos(columna,tipoDato);
            sentencia = sentencia.substr(sentencia.find(",")+1,sentencia.length() - sentencia.find(",")-1);

        }
        string columna = sentencia.substr(0,sentencia.find(":"));
        string tipoDato = sentencia.substr(sentencia.find(":")+1,sentencia.find(")")-sentencia.find(":")-1);

        if(columna.find(" ")==0){
            columna=columna.substr(1,columna.length()-1);
        }
        if(columna.find(" ")==columna.length()-1){
            columna= columna.substr(0,columna.length()-2);
        }
        if(tipoDato.find(" ")==0){
            tipoDato=tipoDato.substr(1,tipoDato.length()-1);
        }
        if(tipoDato.find(" ")==tipoDato.length()-1){
            tipoDato= tipoDato.substr(0,tipoDato.length()-2);
        }

        _listaTablas->getTail()->getTabla()->agregarMetaDatos(columna,tipoDato);
        _listaTablas->imprimirTablas();

    }
}

bool Interprete::ejecutarSelect(string sentencia)//se ejecuta select
{

    string columnaTmp = sentencia.substr(6,sentencia.find("FROM")-6);

    if(columnaTmp.find(" ")==0){//estos if cortan los epacios sobrantes al inicio y al final
        columnaTmp = columnaTmp.substr(1,columnaTmp.length());
    }
    if(columnaTmp.find(" ")==columnaTmp.length()-1){
        columnaTmp = columnaTmp.substr(0,columnaTmp.length()-1);
    }
    cout<<"entreSelect:"<<columnaTmp<<endl;
    if(sentencia.find("WHERE")== string::npos){//select sin where
        string nombreTmp = sentencia.substr(sentencia.find("FROM")+4,sentencia.length());

        if(nombreTmp.find(" ")==0){//estos if cortan los epacios sobrantes al inicio y al final
            nombreTmp = nombreTmp.substr(1,nombreTmp.length());
        }
        if(nombreTmp.find(" ")==nombreTmp.length()-1){
            nombreTmp = nombreTmp.substr(0,nombreTmp.length()-2);
        }

        tabla *tablaTmp = new tabla(nombreTmp,"base de datos");


        if(_listaTablas->existeTabla(nombreTmp)){
            if(columnaTmp.compare("*")==0){//caso que selecciona todas las columnas de la tabla
                tablaTmp = _listaTablas->buscarTabla(nombreTmp);

                tablaTmp->imprimirTabla();//por el momento solo imprime

                return true;

            }
            else{
                if(_listaTablas->buscarTabla(nombreTmp)->existeListaMetaDato(columnaTmp)){

                    tablaTmp->setMetaDatoSinTipo(columnaTmp);
                    //con el for se crean los registros de las columnas seleccionadas y se insertan a la tabla temporal
                    for(int i = 0;i<_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->getTamanio();i++){
                        ListaDato *registroTmp = new ListaDato();
                        for(int j = 0; j<tablaTmp->getMetaDato()->getTamanio();j++){
                            if(_listaTablas->buscarTabla(nombreTmp)->existeMetaDato(tablaTmp->getMetaDato()->buscarPosicion(j)->getmetaDato())){
                                registroTmp->insertarFinal(_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->buscarDatoEnPos(i,_listaTablas->buscarTabla(nombreTmp)->getMetaDato()->PosMetaDato(tablaTmp->getMetaDato()->buscarPosicion(j)->getmetaDato())));
                            }
                        }
                        tablaTmp->getMatrizDato()->insertarFinal(registroTmp);
                    }
                    tablaTmp->imprimirTabla();
                    return true;
                }
                else{
                    return false;
                }
            }

        }
        if(!_listaTablas->existeTabla(nombreTmp)){
            return false;//error no existe la tabla
        }
    }
    if(sentencia.find("WHERE")!= string::npos){//caso con where

        string nombreTmp = sentencia.substr(sentencia.find("FROM")+4,sentencia.find("WHERE")-sentencia.find("FROM")-5);
        if(nombreTmp.find(" ")==0){
            nombreTmp = nombreTmp.substr(1,nombreTmp.length());
        }
        if(nombreTmp.find(" ")==nombreTmp.length()-1){
            nombreTmp = nombreTmp.substr(0,nombreTmp.length()-2);
        }
        cout<<"nombreTmp"<<nombreTmp<<endl;

        tabla *tablaTmp = new tabla(nombreTmp,"base de datos");
        if(_listaTablas->existeTabla(nombreTmp)){
            if(columnaTmp.compare("*")==0){//caso que selecciona todas las columnas de la tabla
                columnaTmp = _listaTablas->buscarTabla(nombreTmp)->getMetaDato()->listaMetaDatoToString();
                cout<<"columnaTmp:"<<columnaTmp<<endl;
                tablaTmp->setMetaDato(columnaTmp);

                for(int i = 0;i<_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->getTamanio();i++){
                    ListaDato *registroTmp = new ListaDato();
                    if(cumpleWhere(_listaTablas->buscarTabla(nombreTmp),sentencia.substr(sentencia.find("WHERE")+5,sentencia.length()),i)==1){

                        cout<<"cumplio where"<<endl;
                        registroTmp=_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->buscarListaEnPos(i);
                        tablaTmp->getMatrizDato()->insertarFinal(registroTmp);
                    }

                    else if(cumpleWhere(_listaTablas->buscarTabla(nombreTmp),sentencia.substr(sentencia.find("WHERE")+5,sentencia.length()),i)==-1){
                        cout<<"ERROR where"<<endl;
                        return false;//error en el where
                    }
                }
                tablaTmp->imprimirTabla();
                return true;

            }
            else{
                if(_listaTablas->buscarTabla(nombreTmp)->existeListaMetaDato(columnaTmp)){
                    tablaTmp->setMetaDatoSinTipo(columnaTmp);
                    for(int i = 0;i<_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->getTamanio();i++){
                        ListaDato *registroTmp = new ListaDato();
                        if(cumpleWhere(_listaTablas->buscarTabla(nombreTmp),sentencia.substr(sentencia.find("WHERE")+5,sentencia.length()),i)==1){

                            for(int j = 0; j<tablaTmp->getMetaDato()->getTamanio();j++){

                                registroTmp->insertarFinal(_listaTablas->buscarTabla(nombreTmp)->getMatrizDato()->buscarDatoEnPos(i,_listaTablas->buscarTabla(nombreTmp)->getMetaDato()->PosMetaDato(tablaTmp->getMetaDato()->buscarPosicion(j)->getmetaDato())));
                            }
                            tablaTmp->getMatrizDato()->insertarFinal(registroTmp);
                        }
                        else if(cumpleWhere(_listaTablas->buscarTabla(nombreTmp),sentencia.substr(sentencia.find("WHERE")+5,sentencia.length()),i)==-1){
                            return false;//error en el where
                        }
                    }
                    tablaTmp->imprimirTabla();
                    return true;
                }
                else{
                    //error columna no existe
                    return false;
                }

            }
        }
        else{
            return false;//error no existe la tabla
        }
    }
}

bool Interprete::ejecutarInsert(string sentencia)//se ejecuta insert
{
    string nombre = sentencia.substr(11,sentencia.find("(")-12);
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }
    if(_listaTablas->existeTabla(nombre)){

        string columnas = sentencia.substr(sentencia.find("(")+1,sentencia.find(")")-sentencia.find("(")-1);
        string token1 = sentencia.substr(sentencia.find("VALUES")+5,sentencia.length());
        string valores = token1.substr(token1.find("(")+1,token1.find(")")-token1.find("(")-1);
        tabla * tablaTmp = _listaTablas->buscarTabla(nombre);
        ListaDato *listaTmp = new ListaDato(tablaTmp->getMetaDato()->getTamanio());

        while(columnas.find(",")!= string::npos){
            string col = columnas.substr(0,columnas.find(","));
            if(col.find(" ")==0){//estos if cortan espacios al inicio y al final
                col = col.substr(1,col.length());
            }
            if(col.find(" ")==col.length()-1){
                col = col.substr(0,col.length()-2);
            }

            string celda = valores.substr(0,valores.find(","));
            if(celda.find(" ")==0){//estos if cortan espacios al inicio y al final
                celda = celda.substr(1,celda.length());
            }
            if(celda.find(" ")==celda.length()-1){
                celda = celda.substr(0,celda.length()-2);
            }

            if(existeColumna(tablaTmp,col)){
                if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("Integer")==0){
                    std::string str = celda;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    cout<<test.toInt(&ok)<<endl;
                    cout<<ok<<endl;
                    if(ok){
                        int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                        listaTmp->setDato(pos,celda);
                        columnas = columnas.substr(columnas.find(",")+1,columnas.length());
                        valores = valores.substr(valores.find(",")+1,valores.length());


                    }
                    else{
                        cout<<"error no se introdujo un int"<<endl;
                        return false;//error no introdujo un int
                    }

                }

                if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("Decimal")==0){
                    std::string str = celda;
                    QString test = QString::fromStdString(str);
                    bool ok;
                    test.toFloat(&ok);
                    if(ok){
                        int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                        listaTmp->setDato(pos,celda);
                        columnas = columnas.substr(columnas.find(",")+1,columnas.length());
                        valores = valores.substr(valores.find(",")+1,valores.length());

                    }
                    else{
                        return false;//error no introdujo un float
                    }
                }

                if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("String")==0){
                    int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                    listaTmp->setDato(pos,celda);
                    columnas = columnas.substr(columnas.find(",")+1,columnas.length());
                    valores = valores.substr(valores.find(",")+1,valores.length());

                    //no se valida ya que un string puede tener caracteres numericos
                }

            }
            if(!existeColumna(tablaTmp,col)){//no se usa un else debido a que puede entrar en los primeros if
                cout<<"error no existe columna"<<endl;
                return false;//error no existe la columna
            }


        }//cierra el while

        //a continuacion se valida la ultima columna ya que el while no la valida

        string col = columnas;
        if(col.find(" ")==0){//estos if cortan espacios al inicio y al final
            col = col.substr(1,col.length());
        }
        if(col.find(" ")==col.length()-1){
            col = col.substr(0,col.length()-2);
        }

        string celda = valores;
        if(celda.find(" ")==0){//estos if cortan espacios al inicio y al final
            celda = celda.substr(1,celda.length());
        }
        if(celda.find(" ")==celda.length()-1){
            celda = celda.substr(0,celda.length()-2);
        }


        if(existeColumna(tablaTmp,col)){
            if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("Integer")==0){
                std::string str = celda;
                QString test = QString::fromStdString(str);
                bool ok;
                cout<<test.toInt(&ok)<<endl;
                if(ok){

                    int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                    listaTmp->setDato(pos,celda);
                    tablaTmp->insertarRegistro(listaTmp);


                    tablaTmp->imprimirTabla();
                    return true;
                }
                else{
                    return false;//error no introdujo un int
                }
            }

            if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("Decimal")==0){
                std::string str = celda;
                QString test = QString::fromStdString(str);
                bool ok;
                test.toFloat(&ok);
                if(ok){
                    int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                    listaTmp->setDato(pos,celda);
                    tablaTmp->insertarRegistro(listaTmp);


                    tablaTmp->imprimirTabla();
                    return true;

                }
                else{
                    return false;//error no introdujo un float
                }
            }

            if(tablaTmp->getMetaDato()->buscarPosicion(tablaTmp->getMetaDato()->PosMetaDato(col))->getTipometaDato().compare("String")==0){

                int pos = tablaTmp->getMetaDato()->PosMetaDato(col);
                listaTmp->setDato(pos,celda);
                tablaTmp->insertarRegistro(listaTmp);


                tablaTmp->imprimirTabla();
                return true;
                //no se valida la conversion ya que un string puede tener caracteres numericos
            }

        }
        if(!existeColumna(tablaTmp,col)){//no se usa un else debido a que puede entrar en los primeros if
            return false;//error no existe la columna
        }


    }
    if(!_listaTablas->existeTabla(nombre)){
        return false;//no existe la tabla
    }
}

bool Interprete::ejecutarUpdate(string sentencia)//se ejecuta update
{

    string nombre = sentencia.substr(6,sentencia.find("SET")-7);
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }
    if(_listaTablas->existeTabla(nombre)){
        tabla * tablaTmp = _listaTablas->buscarTabla(nombre);
        if(sentencia.find("WHERE")!= string::npos==0){

            string cambios = sentencia.substr(sentencia.find("SET")+4,sentencia.find("WHERE")-sentencia.find("SET")-5);
            string where = sentencia.substr(sentencia.find("WHERE")+6,sentencia.length());
            for(int i = 0;i<tablaTmp->getMatrizDato()->getTamanio();i++){//recorre todos los registros
                string token1 = cambios;
                while(token1.find("=")!=string::npos){//recorre los cambios que se desean realizar en cada registro
                    if(cumpleWhere(tablaTmp,where,i)){//si no cumple las condiciones del where salta al siguiente registro
                        string col = token1.substr(0,token1.find("=")-1);
                        if(col.find(" ")==0){//estos if cortan espacios al inicio y al final
                            col = col.substr(1,col.length());
                        }
                        if(col.find(" ")==col.length()-1){
                            col = col.substr(0,col.length()-2);
                        }

                        string valor = "";//se define asi para poder utilizar la variable en otros if

                        if(token1.find(",")!=string::npos){//asignacion de valores a variables col y valores cuando

                            valor = token1.substr(token1.find("=")+1,token1.find(",")-1-token1.find("="));
                            if(valor.find(" ")==0){//estos if cortan espacios al inicio y al final
                                valor = valor.substr(1,valor.length());
                            }
                            if(valor.find(" ")==valor.length()-1){
                                valor = valor.substr(0,valor.length()-2);
                            }
                        }
                        if(token1.find(",")==string::npos){//asignacion de valores a variables col y valores cuando

                            valor = token1.substr(token1.find("=")+1,token1.length());
                            if(valor.find(" ")==0){//estos if cortan espacios al inicio y al final
                                valor = valor.substr(1,valor.length());
                            }
                            if(valor.find(" ")==valor.length()-1){
                                valor = valor.substr(0,valor.length()-2);
                            }
                        }

                        if(tablaTmp->existeMetaDato(col)){
                            int j = tablaTmp->getMetaDato()->PosMetaDato(col);
                            tablaTmp->getMatrizDato()->setDato(i,j,valor);
                            token1 = token1.substr(token1.find(",")+1,token1.length());

                        }
                        if(!tablaTmp->existeMetaDato(col)){
                            return false;//error no existe la columna
                        }

                    }

                }
            }




        }
        else{//caso sin where
            string cambios = sentencia.substr(sentencia.find("SET")+4,sentencia.length());
            for(int i = 0;i<tablaTmp->getMatrizDato()->getTamanio();i++){//recorre todos los registros
                string token1 = cambios;
                while(token1.find("=")!=string::npos){//recorre los cambios que se desean realizar en cada registro

                    string col = token1.substr(0,token1.find("=")-1);
                    if(col.find(" ")==0){//estos if cortan espacios al inicio y al final
                        col = col.substr(1,col.length());
                    }
                    if(col.find(" ")==col.length()-1){
                        col = col.substr(0,col.length()-2);
                    }

                    string valor = "";
                    if(token1.find(",")!=string::npos){//asignacion de valores a variables col y valores cuando

                        valor = token1.substr(token1.find("=")+1,token1.find(",")-1-token1.find("="));
                        if(valor.find(" ")==0){//estos if cortan espacios al inicio y al final
                            valor = valor.substr(1,valor.length());
                        }
                        if(valor.find(" ")==valor.length()-1){
                            valor = valor.substr(0,valor.length()-2);
                        }
                    }
                    if(token1.find(",")==string::npos){//asignacion de valores a variables col y valores cuando

                        valor = token1.substr(token1.find("=")+1,token1.length());
                        if(valor.find(" ")==0){//estos if cortan espacios al inicio y al final
                            valor = valor.substr(1,valor.length());
                        }
                        if(valor.find(" ")==valor.length()-1){
                            valor = valor.substr(0,valor.length()-2);
                        }
                    }

                    if(tablaTmp->existeMetaDato(col)){
                        int j = tablaTmp->getMetaDato()->PosMetaDato(col);
                        tablaTmp->getMatrizDato()->setDato(i,j,valor);
                        token1 = token1.substr(token1.find(",")+1,token1.length());

                    }
                    if(!tablaTmp->existeMetaDato(col)){
                        return false;//error no existe la columna
                    }



                }
            }
            return true;



        }



    }
    if(!_listaTablas->existeTabla(nombre)){
        return false;//la tabla no existe
    }


}

bool Interprete::ejecutarDelete(string sentencia)//se ejecuta delete
{
    string nombre = sentencia.substr(sentencia.find("FROM")+4,sentencia.find("WHERE")-5-sentencia.find("FROM"));
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }

    if(_listaTablas->existeTabla(nombre)){

        tabla* tablaTmp = _listaTablas->buscarTabla(nombre);
        string condiciones = sentencia.substr(sentencia.find("WHERE")+5,sentencia.length());
        for(int i=0;i<tablaTmp->getMatrizDato()->getTamanio();i++){

            if(cumpleWhere(tablaTmp,condiciones,i)){
                tablaTmp->getMatrizDato()->deleteLista(i);
            }
        }
        return true;


    }
    if(!_listaTablas->existeTabla(nombre)){
        return false;//no existe la tabla
    }

    return true;
}

bool Interprete::ejecutarCreateIndex(string sentencia)//se ejecuta create index
{
    string nombre = sentencia.substr(sentencia.find("ON")+2,sentencia.find("(")-3-sentencia.find("ON"));
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }


    string columna = sentencia.substr(sentencia.find("(")+1,sentencia.find(")")-2-sentencia.find("("));
    if(columna.find(" ")==0){//estos if cortan espacios al inicio y al final
        columna = columna.substr(1,columna.length());
    }
    if(columna.find(" ")==columna.length()-1){
        columna = columna.substr(0,columna.length()-2);
    }

    if(_listaTablas->existeTabla(nombre)){
        tabla *tablaTmp = _listaTablas->buscarTabla(nombre);
        if(tablaTmp->existeMetaDato(columna)){
            //aqui se crea el indice

            return true;
        }
        else{
            return false;//no existe la columna
        }


    }
    if(!_listaTablas->existeTabla(nombre)){

        return false;//no existe la tabla
    }


}

bool Interprete::ejecutarCompress(string sentencia)//se ejecuta compress
{
    string nombre = sentencia.substr(sentencia.find("TABLE")+5,sentencia.length());
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }

    if(_listaTablas->existeTabla(nombre)){
        tabla *tablaTmp = _listaTablas->buscarTabla(nombre);
        //aqui se realiza el compress

        return true;


    }
    if(!_listaTablas->existeTabla(nombre)){

        return false;//no existe la tabla
    }


}

bool Interprete::ejecutarBackup(string sentencia)//se ejecuta backup
{
    string nombre = sentencia.substr(sentencia.find("TABLE")+5,sentencia.length());
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }

    if(_listaTablas->existeTabla(nombre)){
        tabla *tablaTmp = _listaTablas->buscarTabla(nombre);
        //aqui se realiza el backup

        return true;


    }
    if(!_listaTablas->existeTabla(nombre)){

        return false;//no existe la tabla
    }
}

bool Interprete::ejecutarRestore(string sentencia)//se ejecuta restore
{
    string nombre = sentencia.substr(sentencia.find("TABLE")+5,sentencia.length());
    if(nombre.find(" ")==0){//estos if cortan espacios al inicio y al final
        nombre = nombre.substr(1,nombre.length());
    }
    if(nombre.find(" ")==nombre.length()-1){
        nombre = nombre.substr(0,nombre.length()-2);
    }

    if(_listaTablas->existeTabla(nombre)){
        tabla *tablaTmp = _listaTablas->buscarTabla(nombre);
        //aqui se realiza el backup

        return true;


    }
    if(!_listaTablas->existeTabla(nombre)){

        return false;//no existe la tabla
    }
}

/*------------------------------------------------------------------------------*/

int Interprete::cargaTablas()
{
    string path = "./";

    DIR *dir = opendir(path.c_str());
    if(!dir)
    {
        return 1;
    }
    dirent *entry;
    while(entry = readdir(dir))
    {
        if(has_suffix(entry->d_name, ".snar"))
        {
            cout << entry->d_name << endl;

            generarTabla(entry->d_name);


        }
    }
    closedir(dir);
}

bool Interprete::has_suffix(const string &s, const string &suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}

void Interprete::generarTabla(string pName)
{

    ArchivoAleatorio<Registro> archivo(pName);
    if (archivo.openFile(truncate)){ //si se puede abrir el archivo
        _listaTablas->insertarFinal(pName,"BaseDatos");
        _listaTablas->getTail()->getTabla()->setMetaDato(archivo.getFirstRecord().getDato());
    }

}
/*------------------------------------------------------------------------------*/
