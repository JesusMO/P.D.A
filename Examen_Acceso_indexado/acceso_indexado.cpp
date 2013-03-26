#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#include "indice.h"
#include <queue>
Indice Manipulador_indice;//manipula las funciones de la clase indice declarada en indice.h
class Registro{
private:
    int codigo;
    char marca[10];
    float precio;
    int cant;
    bool valido;
public:
    void ingresar();
    void mostrar_especifico(int);
    void vender(int);
    void eliminar(int);
    friend int Menu();
    friend class Indice;
}Manipulador_registro;
/**Inicializacion de la cola*/
queue <Registro> Buffer;
queue <Registro> Buffer2;
int cant=0; //inicializar tamacio

void Registro::vender(int codigo1){
    fstream Zapateria("data.bin",ios::in|ios::binary|ios::out);
    int Pos=Manipulador_indice.buscar_indice(0,tam(),codigo1);
    Zapateria.seekg(Pos*sizeof(Registro));
    Zapateria.read((char*)this,sizeof(Registro));
    if(Pos==-1 || !valido){
        cout<<" NO SE ENCONTRO"<<endl;
    }
    else
        if(valido==true){
            int cantidad;
            cout<<"<----------------------->"<<endl;
            cout<<"Su Codigo: "<<codigo<<endl;
            cout<<"Su Marca: "<<marca<<endl;
            cout<<"Su Precio: "<<precio<<endl;
            cout<<"Su Cantidad: "<<cant<<endl;
            cout<<"Cuantos calzados desean comprar?"<<endl;
            cin>>cantidad;
            if(cantidad>cant)
                cout<<"No poseemos esa cantidad"<<endl;
            else{
                cout<<"Total a pagar"<<cantidad*precio<<endl;
                cant-=cantidad;
            }
            Zapateria.seekp(Pos*sizeof(Registro));
            Zapateria.write((char*)this,sizeof(Registro));
        }
        Zapateria.close();
}

void Registro::ingresar(){

    ofstream Zapateria("data.bin",ios::binary|ios::out|ios::app);
    char otra_op='s';
    do{
        Zapateria.seekp(0,ios::end);

        cout<<"Ingrese su Codigo"<<endl;
        cin>>Manipulador_registro.codigo;
        cout<<"Ingrese su Marca"<<endl;
        cin>>Manipulador_registro.marca;
        cout<<"Ingrese su Precio"<<endl;
        cin>>Manipulador_registro.precio;
        cout<<"Ingrese su Cantidad"<<endl;
        cin>>Manipulador_registro.cant;
        Manipulador_registro.valido=true;
        if(cant<5){
            Buffer.push(Manipulador_registro);
            cant++;
        }
        else{
            Buffer.pop();
            Buffer.push(Manipulador_registro);
            cant--;
        }
        valido=true;
        int posicion_maestro=Zapateria.tellp()/sizeof(Registro);
        Manipulador_indice.ingresar_indice(codigo,posicion_maestro);
        Zapateria.write((char*)&Manipulador_registro,sizeof(Registro));
        Manipulador_indice.ordenar_indice();
        cout<<"Desea ingresar otra marca de calzado"<<endl;
        cin>>otra_op;
    }while(otra_op!='N'&&otra_op!='n');
    Manipulador_indice.ordenar_indice();
}
void Registro::mostrar_especifico(int codigo1){
    for(int i=0;i<cant;i++){
        Manipulador_registro=Buffer.front();
        if(Manipulador_registro.codigo==codigo1){
            cout<<"<----------------------->"<<endl;
            cout<<"Su Codigo: "<<codigo<<endl;
            cout<<"Su Marca: "<<marca<<endl;
            cout<<"Su Precio: "<<precio<<endl;
            cout<<"Su Cantidad: "<<cant<<endl;
        }
        else{

        }

    }
    ifstream Zapateria("data.bin",ios::in|ios::binary);
    int Pos=Manipulador_indice.buscar_indice(0,tam(),codigo1);
    Zapateria.seekg(Pos*sizeof(Registro));
    Zapateria.read((char*)this,sizeof(Registro));
    if(Pos==-1 || !valido){
        cout<<" NO SE ENCONTRO"<<endl;
    }
    else
        if(valido==true){
            cout<<"<----------------------->"<<endl;
            cout<<"Su Codigo: "<<codigo<<endl;
            cout<<"Su Marca: "<<marca<<endl;
            cout<<"Su Precio: "<<precio<<endl;
            cout<<"Su Cantidad: "<<cant<<endl;
        }

    Zapateria.close();
}

void Registro::eliminar(int codigo1){
    fstream Zapateria("data.bin",ios::in|ios::binary|ios::out);
    int Pos=Manipulador_indice.buscar_indice(0,tam(),codigo1);
    Zapateria.seekg(Pos*sizeof(Registro));
    Zapateria.read((char*)this,sizeof(Registro));
    if(Pos==-1 || !valido){
        cout<<" NO SE ENCONTRO"<<endl;
    }
    else
        if(valido==true){
            cout<<"<----------------------->"<<endl;
            cout<<"Su Codigo: "<<codigo<<endl;
            cout<<"Su Marca: "<<marca<<endl;
            cout<<"Su Precio: "<<precio<<endl;
            cout<<"Su Cantidad: "<<cant<<endl;
            valido=false;
            Zapateria.seekp(Pos*sizeof(Registro));
            Zapateria.write((char*)this,sizeof(Registro));
        }
}
int Menu(){
int op;
    cout<<"ZAPATERIA JMO"<<endl;
    cout<<"1)....................REGISTRAR"<<endl;
    cout<<"2)...........MOSTRAR ESPECIFICO"<<endl;
    cout<<"3)............VENDER UN CALZADO"<<endl;
    cout<<"4).....DESINCORPORAR UN CALZADO"<<endl;
    cout<<"5)............MOSTRAR EL INDICE"<<endl;
    cout<<"6)........................SALIR"<<endl<<endl;
    cout<<" Seleccione su opcion? "<<endl;
    cin>>op;
    return op;
}
int main(){
    Registro Zapa;
    char otra_op='s';
    do{
        system("cls");
    switch(Menu()){
        case 1:{
            system("cls");
            Zapa.ingresar();
            break;
        }
        case 2:{
            system("cls");
            int code;
            cout<<"Ingrese el codigo a buscar"<<endl;
            cin>>code;
            Zapa.mostrar_especifico(code);
            break;
        }
        case 3:{
            system("cls");
            int code;
            cout<<"Ingrese el codigo del calzado a comprar"<<endl;
            cin>>code;
            Zapa.vender(code);
            break;
        }
        case 4:{
            system("cls");
            int code;
            cout<<"Ingrese el codigo a eliminar"<<endl;
            cin>>code;
            Zapa.eliminar(code);
            break;
        }
        case 5:{
            system("cls");
            Manipulador_indice.mostrar_indice();
            break;
        }
        case 6:{
            cout<<"Saliendo del programa"<<endl;
            exit(1);
        }
        default:{
            cout<<"Opcion invalida"<<endl;
            break;
        }
    }
    cout<<"Desea retornar al menu principal"<<endl;
    cin>>otra_op;
    }while(otra_op!='N'&&otra_op!='n');

}





