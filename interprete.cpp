#include "interprete.h"
#include <QDebug>
#include "iostream"
using namespace std;

Interprete::Interprete()
{

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
        qDebug() << "Compress";
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

bool Interprete::nombreValido(string nombre)
{
    if((nombre.length()>0)&&(nombre.length()<30)){
        if((nombre.find(",")==string::npos)&&(nombre.find("'")==string::npos)&&
                (nombre.find("\"")==string::npos)&&(nombre.find(".")==string::npos)&&
                (nombre.find(";")==string::npos)){
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
    if(dato.compare("Integer")||dato.compare("String")||dato.compare("Decimal")){
        return true;
    }
    else{
        return false;
    }
}



//***************************************************************



bool Interprete::revisarCreateTable(string sentencia)//se revisa sintaxis de create table
{
    if((sentencia.find(" ",7)==12)){
        if(sentencia.find("(")!=string::npos){
            string token1=sentencia.substr(13,sentencia.find("(")-13);
            if(nombreValido(token1)){
                if((sentencia.find(")")!=string::npos) &&
                        (sentencia.find(")") == sentencia.length()-1)){

                    string token2=sentencia.substr(sentencia.find("(")+1,sentencia.length()-1);
                    while(token2.find(",")!=string::npos){
                        if(token2.find(":")!=string::npos){
                            string tokenColumna = token2.substr(0,token2.find(":")-1);
                            string tokenDato = token2.substr(token2.find(":")+1,token2.find(",")-1);
                            if(nombreValido(tokenColumna) && datoValido(tokenDato)){
                                token2=token2.substr(token2.find(",")+1,token2.length()-1);
                            }
                            else{
                                //nombre de columna o tipo de dato invalidos
                                return false;
                            }
                        }
                    }
                    string tokenColumna = token2.substr(0,token2.find(":")-1);
                    string tokenDato = token2.substr(token2.find(":")+1,token2.find(",")-1);
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
        if((sentencia.find("FROM")!=string::npos)&&(sentencia.find("FROM")!=7)&&(sentencia.length()>=15)){
            if(sentencia.find("WHERE")!=string::npos){
                string token1 = sentencia.substr(sentencia.find("WHERE")+5,sentencia.length()-sentencia.find("WHERE")+5);
                while(token1.length()>0){
                    if(token1.find(" ")!=string::npos){
                        string condicionIzq = token1.substr(0,token1.find(" "));
                        token1=token1.substr(token1.find(" ")+1,token1.length()-token1.find(" "));
                        if(condicionIzq.length()>0){

                            if(token1.find(" ")!=string::npos){
                                string operador = token1.substr(0,token1.find(" "));
                                token1=token1.substr(token1.find(" ")+1,token1.length()-token1.find(" "));
                                if(operador.compare("=") || operador.compare("<>") || operador.compare(">") || operador.compare(">=")
                                        || operador.compare("<") || operador.compare("<=")){

                                    if(token1.find(" ")!=string::npos){
                                        string condicionDer = token1.substr(0,token1.find(" "));
                                        token1=token1.substr(token1.find(" ")+1,token1.length()-token1.find(" "));
                                        if(condicionDer.length()>0){
                                            if(token1.length()>0){
                                                if(token1.find("OR ")==0){
                                                    token1=token1.substr(3,token1.length()-3);
                                                }
                                                if(token1.find("AND ")==0){
                                                    token1=token1.substr(4,token1.length()-3);
                                                }
                                                else{
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
                    else{
                        return false;
                    }
                }
                return true;//validacion con WHERE
            }
            else{
                return true;//validacion sin WHERE
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

                                cout<<"token1"<<token1<<"token2"<<token2<<endl;
                                while(token1.find(",")!=string::npos && token2.find(",")!=string::npos){
                                    qDebug()<<"hola";
                                    token1 = token1.substr(token1.find(",")+1, token1.length()-token1.find(","));
                                    token2 = token2.substr(token2.find(",")+1, token1.length()-token2.find(","));
                                }
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
                    cout<<"igualaciones"<<igualaciones<<"hola"<<endl;
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
                                                cout<<"ELSE"<<endl;
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
                                        cout<<"ELSE"<<endl;
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



bool Interprete::ejecutarCreateTable(string sentencia)
{
    //se ejecuta create table
    return true;
}

bool Interprete::ejecutarSelect(string sentencia)
{
    //se ejecuta select
    return true;
}

bool Interprete::ejecutarInsert(string sentencia)
{
    //se ejecuta insert
    return true;
}

bool Interprete::ejecutarUpdate(string sentencia)
{
    //se ejecuta update
    return true;
}

bool Interprete::ejecutarDelete(string sentencia)
{
    //se ejecuta delete
    return true;
}

bool Interprete::ejecutarCreateIndex(string sentencia)
{
    //se ejecuta create index
    return true;
}

bool Interprete::ejecutarCompress(string sentencia)
{
    //se ejecuta compress
    return true;
}

bool Interprete::ejecutarBackup(string sentencia)
{
    //se ejecuta backup
    return true;
}

bool Interprete::ejecutarRestore(string sentencia)
{
    //se ejecuta restore
    return true;
}
