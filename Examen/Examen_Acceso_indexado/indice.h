#ifndef indice
#define indice
class Indice{
private:
    int clave; //Campo clave del registro
    int pos_R; //este es la posicion en el registro maestro
public:
    void ingresar_indice(int codigo, int pos);
    void ordenar_indice();
    int buscar_indice(int,int,int);
    void mostrar_indice();
    void Limpiar_indice();
    friend int tam();

};

    ofstream Err("Errores.txt",ios::out|ios::app);

int tam(){ //retorna el tamaño maximo del archivo
    ifstream Arch_Indice("Indice.bin",ios::binary|ios::in);
    Arch_Indice.seekg(0,ios::end);
    int Tam=Arch_Indice.tellg()/sizeof(Indice);
    Arch_Indice.close();
    return Tam;
}
void Indice::Limpiar_indice(){
ofstream Arch_Indice("indice.bin",ios::out|ios::binary);
Arch_Indice.close();
}
void Indice::ingresar_indice(int codigo, int pos){
    ofstream Arch_Indice("Indice.bin",ios::out|ios::binary|ios::app);
    Arch_Indice.seekp(0,ios::end);
    clave=codigo;
    pos_R=pos;
    Arch_Indice.write((char*)this,sizeof(Indice));
    Arch_Indice.close();

}
int Indice::buscar_indice(int primero,int ultimo, int codigo){
    ifstream Arch_Indice("Indice.bin",ios::in|ios::binary);
        if(primero>ultimo)
            return -1;
        else{
            int mitad=(primero+ultimo)/2;
            Arch_Indice.seekg(mitad*sizeof(Indice));
            Arch_Indice.read((char*)this,sizeof(Indice));
            if(clave==codigo)
            return pos_R;
              else{
                if(clave>codigo)
                    return buscar_indice(primero,mitad-1,codigo);
                else
                    return buscar_indice(mitad+1,ultimo,codigo);
            }
        }
}
void Indice::mostrar_indice(){
    ifstream Arch_Indice("Indice.bin",ios::in|ios::binary);
    Arch_Indice.seekg(0,ios::end);
    int Nreg=Arch_Indice.tellg()/sizeof(Indice);
    Arch_Indice.seekg(0,ios::beg);
    for(int i=0;i<Nreg;i++){
        Arch_Indice.read((char*)this,sizeof(Indice));
        cout<<" clave: "<<clave<<" Posicion en maestro: "<<pos_R<<endl;
    }
    Arch_Indice.close();
}

void Indice::ordenar_indice(){
    Indice Aux_i, Aux_j;
    fstream Arch_Indice("Indice.bin",ios::out|ios::in|ios::binary);
    Arch_Indice.seekg(0,ios::end);
    int Nreg=Arch_Indice.tellg()/sizeof(Indice);
    for(int i=0;i<Nreg-1;i++){
            Arch_Indice.seekg(i*sizeof(Indice));
            Arch_Indice.read((char*)&Aux_i,sizeof(Indice));
        for(int j=i+1;j<Nreg;j++){
            Arch_Indice.seekg(j*sizeof(Indice));
            Arch_Indice.read((char*)&Aux_j,sizeof(Indice));
            if(Aux_i.clave>Aux_j.clave){
                Arch_Indice.seekp(i*sizeof(Indice));
                Arch_Indice.write((char*)&Aux_j,sizeof(Indice));
                Arch_Indice.seekp(j*sizeof(Indice));
                Arch_Indice.write((char*)&Aux_i,sizeof(Indice));
            }
        }
    }
    Arch_Indice.close();
}
#endif

