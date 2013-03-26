#include <iostream>
#include <fstream>
    using namespace std;
#include "indice.h"
class Registro{ //la estrucura del registro debe ser identica en los 3 programas para que su conjunto de informacion binaria sea recuperable
private:
    int  Cedula_Cliente;
    int  Numero_Cuenta;
    char Tipo_Cuenta[15];
    float Saldo;
    bool valido;
public:
    void Crear_Indice(); //método para crear índice
};
Indice Manipulador_Indice; //a través de la utilización de la libreria "indice.h" creo un objeto que me permita manipula y controlar los metodos sobre el indice

    void Registro::Crear_Indice(){
        ifstream Respaldo_bin("Respaldo.bin",ios::in|ios::binary);
        Respaldo_bin.seekg(0,ios::end);
        int Nreg=Respaldo_bin.tellg()/sizeof(Registro);
        Respaldo_bin.seekg(0,ios::beg);
        Manipulador_Indice.Limpiar_indice(); //siguiendo las especificaciones del enunciado ellos desean hacer una recuperacion, por lo tanto cada vez q se desee recuperar el indice debe estar limpio
        for(int i=0;i<Nreg;i++){
            Respaldo_bin.read((char*)this, sizeof(Registro));
            Manipulador_Indice.ingresar_indice(Numero_Cuenta,(i));
            Manipulador_Indice.ordenar_indice();
        }

        Respaldo_bin.close();
    }

    int main(){

        Registro Manipulador_Registro;
        Manipulador_Registro.Crear_Indice();
    }


