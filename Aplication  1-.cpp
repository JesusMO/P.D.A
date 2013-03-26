/**
    EL BANCO PDA-BANK HA PERDIDO UN DISCO DURO DE UNO DE SUS SERVIDORES.
    EN DICHO SE ALMACENABAM LAS CUENTAS DE SUS CLIENTES.
    EL ULTIMO PRESPALDO FUE ECHO HACE 3 DIAS(RESPALDO.TXT) Y ADEMAS
    EL ARCHIVO DE TRANSACCIONESESTA INTACTO Y ACTUALIZADO (TRANS.TXT).
    APROVECHANDO LA COYUNTURA EL BANCO HA DECIDIDO MIGRAR SUS DATOS DE TEXTO A UN FORMATO BINARIO CON ACCESO INDEXADO

        USTED DEBE:
            -CREAR UNA APLICACION QUE MIGRE LOS DATOS DE TEXTO A BINARIO, CREANDO LOS
            ARCHIVOS RESPALDO.BIN Y TRANS.BIN A PARTIR DE LOS ARCHIVOS EXISTENTES.
            - Crear una aplicación que genere un indice para los datos almacenados en el archivo respaldo.bin
            - Crear una aplicación que actualize el archivo de respaldo con los datos de las transacciones, generando
            un archivo "banco.bin" y su indice (es el mismo) actualziados.

            -trans.txt crear cuentas, depositos y retiros, cerrar cuenta

            banco.txt cedula del cliente, numero de cuenta, tipo de cuenta, saldo

            trans.txt *tipo de transaccion, numero de cuenta, cedula del cliente, tipo monto

            *DEBE manejar: crear, depositar/retirar,eliminar
*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
    using namespace std;

class Registro{ //registro banco.txt
private:
    int  Cedula_Cliente;
    int  Numero_Cuenta;
    char Tipo_Cuenta[15];
    float Saldo;
    bool valido;
public:
    void Migrar_Respaldo(); //metodo de migracion banco.txt -----> banco .bin
};

class Transacciones{
private:
    char Tipo_Transaccion;
    int Numero_Cuenta;
    int Cedula_Cliente;
    char Tipo_Cuenta[15];
    float Monto_Transaccion;
public:
    void Migrar_Transacciones(); //Método de migración de trans.txt ----> tans.bin
};

void Transacciones::Migrar_Transacciones(){
    ifstream Transacciones_txt("Trans.txt",ios::in);
    ofstream Transacciones_bin("Trans.bin",ios::out|ios::binary);
    if(!Transacciones_bin || !Transacciones_txt){ //verificar si hay errores,
        exit(0);
    }

    Transacciones_txt>>Tipo_Transaccion; //tecnica de lectura adelantada para el txt
        while(!Transacciones_txt.eof()){
            Transacciones_txt>>Cedula_Cliente;
            Transacciones_txt>>Numero_Cuenta;
            Transacciones_txt>>Tipo_Cuenta;
            Transacciones_txt>>Monto_Transaccion;
            Transacciones_bin.write((char*)this,sizeof(Transacciones)); //metodo para escribir en el archivo.bin
            Transacciones_txt>>Tipo_Transaccion;
        }
    Transacciones_bin.close();
    Transacciones_txt.close();
}
void Registro::Migrar_Respaldo(){
    ifstream Respaldo_txt("Respaldo.txt",ios::in);
    ofstream Respaldo_bin("Respaldo.bin",ios::out|ios::binary);
    if(!Respaldo_bin || !Respaldo_txt){
        exit(0);
    }

    Respaldo_txt>>Cedula_Cliente;
        while(!Respaldo_txt.eof()){
            Respaldo_txt>>Numero_Cuenta;
            Respaldo_txt>>Tipo_Cuenta;
            Respaldo_txt>>Saldo;
            valido=true;
            Respaldo_bin.write((char*)this,sizeof(Registro));
            Respaldo_txt>>Cedula_Cliente;
        }
}

int main(){
Registro Aux_Resgistro;
Transacciones Aux_Transacciones;
    Aux_Resgistro.Migrar_Respaldo();
    Aux_Transacciones.Migrar_Transacciones();
}

