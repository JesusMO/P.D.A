#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
    using namespace std;
#include "indice.h"
Indice Manipulador_Indice;

class Registro{
private:
    int  Cedula_Cliente;
    int  Numero_Cuenta;
    char Tipo_Cuenta[15];
    float Saldo;
    bool valido;
public:
    void Deposito(int cant,int pos,fstream &Respaldo_bin,Registro Manipulador_Registro); //método para depositar
    void Retiro(int cant,int pos,fstream &Respaldo_bin,Registro Manipulador_Registro);// método para retirar
    void Eliminar(int pos,fstream &Respaldo_bin,Registro Manipulador_Registro);   //Eliminar un registro aplicando eliminacion logica
    void Crear(int _Cedula_Cliente,int _Numero_Cuenta,char _Tipo_Cuenta[15],float _Saldo); //Crear un nuevo cliente
}Manipulador_Registro;
/**Deposito*/
void Registro::Deposito(int cant,int pos,fstream &Respaldo_bin,Registro Manipulador_Registro){
    if(valido==true){
        Manipulador_Registro.Saldo+=cant;
        Respaldo_bin.seekp(pos*sizeof(Registro));
        Respaldo_bin.write((char*)&Manipulador_Registro,sizeof(Registro));
    }
    else{
        Err<<"No existe el registro Nro: "<<Manipulador_Registro.Numero_Cuenta<<" Por lo tanto el deposito  es invalido"<<endl;//controlador de errores, los envia a err.txt
    }
}
/**Retiro*/
void Registro::Retiro(int cant,int pos,fstream &Respaldo_bin,Registro Manipulador_Registro){
    if(valido==true){
        if(cant>Manipulador_Registro.Saldo){
            Err<<"Saldo insuficiente en la Cuenta Nro: "<<Manipulador_Registro.Numero_Cuenta<<" Por lo tanto el retiro es invalido"<<endl;
        }
        else{
            Manipulador_Registro.Saldo-=cant;
            Respaldo_bin.seekp(pos*sizeof(Registro));
            Respaldo_bin.write((char*)&Manipulador_Registro,sizeof(Registro));
        }
    }
    else{

        Err<<"No existe el registro Nro: "<<Manipulador_Registro.Numero_Cuenta<<" Por lo tanto el retiro es invalido"<<endl;
    }
}
/**Eliminar*/
void Registro::Eliminar(int pos,fstream &Respaldo_bin,Registro Manipulador_Registro){
    if(valido==true){
        Manipulador_Registro.valido=false;
        Respaldo_bin.seekp(pos*sizeof(Registro));
        Respaldo_bin.write((char*)&Manipulador_Registro,sizeof(Registro));
    }
    else{
        Err<<"No se puede eliminar registro Nro: "<<Manipulador_Registro.Numero_Cuenta<<" Por que no existe"<<endl;
    }
}
/**Crear Cuenta*/
void Registro::Crear(int _Cedula_Cliente,int _Numero_Cuenta,char _Tipo_Cuenta[15],float _Saldo){
        ofstream Respaldo_bin("Respaldo.bin",ios::out|ios::app|ios::binary);
        Cedula_Cliente=_Cedula_Cliente;
        Numero_Cuenta=_Numero_Cuenta;
        strcpy(Tipo_Cuenta,_Tipo_Cuenta);
        Saldo=_Saldo;
        valido=true;
        Respaldo_bin.seekp(0,ios::end);
        Manipulador_Indice.ingresar_indice(Numero_Cuenta,Respaldo_bin.tellp()/sizeof(Registro));
        Respaldo_bin.write((char*)this,sizeof(Registro));
        Manipulador_Indice.ordenar_indice();
        Respaldo_bin.close();
   }
class Transacciones{
private:
    char Tipo_Transaccion;
    int Numero_Cuenta;
    int Cedula_Cliente;
    char Tipo_Cuenta[15];
    float Monto_Transaccion;
public:
    void Cargar_Transacciones_Registro();
}Manipulador_Transacciones;

void Transacciones::Cargar_Transacciones_Registro(){
    fstream Respaldo_bin("Respaldo.bin",ios::out|ios::in|ios::binary);
    ifstream Transacciones_bin("Trans.bin",ios::in|ios::binary);
    Transacciones_bin.seekg(0,ios::end);
    int Nreg=Transacciones_bin.tellg()/sizeof(Transacciones);
    Transacciones_bin.seekg(0,ios::beg);
    for(int i=0;i<Nreg;i++){
        Transacciones_bin.read((char*)&Manipulador_Transacciones,sizeof(Transacciones));
        switch(Manipulador_Transacciones.Tipo_Transaccion){
            case 'D':{
                int pos=Manipulador_Indice.buscar_indice(0,tam(),Manipulador_Transacciones.Numero_Cuenta);
                if(pos==-1){
                   Err<<"No existe el registro Nro: "<<Manipulador_Transacciones.Numero_Cuenta<<" Por lo tanto no se procesara su solicitud "<<endl;
                }
                else{
                    Respaldo_bin.seekg(pos*sizeof(Registro));
                    Respaldo_bin.read((char*)&Manipulador_Registro,sizeof(Registro));
                    Manipulador_Registro.Deposito(Manipulador_Transacciones.Monto_Transaccion,pos,Respaldo_bin,Manipulador_Registro);

                }
                break;
            }
            case 'R':{
                int pos=Manipulador_Indice.buscar_indice(0,tam(),Manipulador_Transacciones.Numero_Cuenta);
                if(pos==-1){
                   Err<<"No existe el registro Nro: "<<Manipulador_Transacciones.Numero_Cuenta<<" Por lo tanto no se procesara su solicitud "<<endl;
                }
                else{
                    Respaldo_bin.seekg(pos*sizeof(Registro));
                    Respaldo_bin.read((char*)&Manipulador_Registro,sizeof(Registro));
                    Manipulador_Registro.Retiro(Manipulador_Transacciones.Monto_Transaccion,pos,Respaldo_bin,Manipulador_Registro);
                }

                break;
            }
            case 'E':{
                    int pos=Manipulador_Indice.buscar_indice(0,tam(),Manipulador_Transacciones.Numero_Cuenta);
                if(pos==-1){
                    Err<<"No existe el registro Nro: "<<Manipulador_Transacciones.Numero_Cuenta<<" Por lo tanto no se procesara su solicitud "<<endl;
                }
                else{
                    Respaldo_bin.seekg(pos*sizeof(Registro));
                    Respaldo_bin.read((char*)&Manipulador_Registro,sizeof(Registro));
                    Manipulador_Registro.Eliminar(pos,Respaldo_bin,Manipulador_Registro);
                }
                break;
            }

            case 'C':{
                    Manipulador_Registro.Crear(Manipulador_Transacciones.Cedula_Cliente,Manipulador_Transacciones.Numero_Cuenta,Manipulador_Transacciones.Tipo_Cuenta,Manipulador_Transacciones.Monto_Transaccion);
                    break;
            }
        }

    }
}

int main(){
    Manipulador_Transacciones.Cargar_Transacciones_Registro();
}
