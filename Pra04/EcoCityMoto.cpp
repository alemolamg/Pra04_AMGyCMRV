/* 
 * File:   EcoCityMoto.cpp
 * Author: Alemol
 * 
 * Created on 28 de octubre de 2019, 11:38
 */
#include <fstream>
#include <sstream>
#include "EcoCityMoto.h"


EcoCityMoto::~EcoCityMoto() {
}


void EcoCityMoto::cargarMotos(string fileNameMotos){
    ifstream fe;               
    string linea;                   
    int total = 0;                 
    
    
    string matricula, latitud, longitud,estado;
    double dlat, dlon;
    int destado; tipoEstado tipo;


    fe.open(fileNameMotos);
    
    if(fe.good()){
        //Mientras no se haya llegado al final del fichero
        getline(fe, linea); //lee la primera, que es informativa
        getline(fe, linea);     //Toma una línea del fichero
        while(!fe.eof()){            
            stringstream ss;               
            if(linea!=""){
                ++total;
            }            
  
            if(total>=1){                
                
                ss << linea;
                
                //Leemos Matricula
                getline(ss,matricula,';');    //El carácter ; se lee y se elimina de ss
                
                //Leemos estado moto
                getline(ss,estado,';');          
                // Leemos estado
                destado = stoi(estado);
                switch (destado){
                    case 0: tipo=Bloqueado; break;
                    case 1: tipo=Activo; break;
                    case 2: tipo=SinBateria; break;
                    case 3: tipo=Rota; break;
                }
                //Leemos la latitud y longitud
                getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss

                dlat = stod(latitud);       //tranforma en double
                dlon = stod(longitud);      //tranforma en double
                
                //con todos los atributos leídos, se crea la moto
                Moto moto(tipo, matricula, dlat, dlon);
                motos.insertar(moto);
                //comprobacion lectura
               //std::cout << moto.getId() << ";" << moto.getStatus() <<std::endl;            
            }              
            getline(fe, linea);     //Toma una línea del fichero
        }    
        cout<<"Total de motos en el fichero: " << total <<endl;
        fe.close();     
        
    }else{
        cerr<<"No se puede abrir el fichero"<<endl;
    }
}

void EcoCityMoto::cargarClientes(string fileNameClientes){
    std::ifstream fe;                    
    string linea;                   
    int total = 0;                  
    
    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon; 


    fe.open(fileNameClientes);
    
    if(fe.good()){
        //Mientras no se haya llegado al final del fichero
        getline(fe, linea); //Se salta la primera linea, solo info
        getline(fe, linea);     //Toma una línea del fichero
        while(!fe.eof()){            
            stringstream ss;             
            if(linea!=""){
                ++total;
            }            
  
            if(total>=1){                
                //Inicializamos el contenido de ss
                ss << linea;
                
                //Leemos el DNI
                getline(ss,dni,';');            //El carácter ; se lee y se elimina de ss
                
                //Leemos el pass
                getline(ss,pass,';');           //El caráter ; se lee y se elimina de ss

                //Leemos el nombre
                getline(ss,nombre,';');         //El caráter ; se lee y se elimina de ss
                
                //Leemos la dirección
                getline(ss,direccion,';');      //El caráter ; se lee y se elimina de ss
                
                //Leemos la latitud y longitud
                getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss

                dlat = stod(latitud);
                dlon = stod(longitud);
                
                //con todos los atributos leídos, se crea el cliente
                Cliente client (dni, nombre, pass, direccion,dlat, dlon, this);
                clientes.inserta(client);
              
                //mostramos los clientes;
                //std::cout << client.GetDni() << ";" << client.GetNombre() <<std::endl;            
            }              
            getline(fe, linea);     //Toma una línea del fichero
        }    
        cout<<"Total de clientes en el fichero: " << total <<endl;
        fe.close(); //Cerramos el flujo de entrada        
    }else{
        cerr<<"No se puede abrir el fichero"<<endl;
    }
}


EcoCityMoto::EcoCityMoto(const string& file1, const string& file2){
    cargarMotos(file2);
    cargarClientes(file1);
}

    
unsigned EcoCityMoto::GetIdUltimo() const{
        return idUltimo;
}

void EcoCityMoto::SetIdUltimo(unsigned nuevoIdUltimo){
    idUltimo=nuevoIdUltimo;
}


Cliente EcoCityMoto::buscarCliente(string dni){
    Cliente clnt(dni);
    Cliente encontrado;
    if(clientes.busca(clnt,encontrado))
        return encontrado;
    throw std::invalid_argument("No esta este cliente");
}

AVL<Cliente>& EcoCityMoto::getClientes(){
    return clientes;
}

VDinamico<Moto>& EcoCityMoto::getMotos(){
    return motos;
}

void EcoCityMoto::desbloqueaMoto(Moto* moto, Cliente* cli) {
    moto->seActiva(cli);
    ++idUltimo;
}

Moto* EcoCityMoto::LocMotoCercana(UTM& ubicacion) {
    Moto *moto;
    
    double dist=999999999, x;
    for (int i=0; i<motos.tamLogico()-1;i++)                  
        if (motos[i].getStatus()==Bloqueado){
            x=ubicacion.distancia(motos[i].getPosicion());   //distancia en UTM 
            if (x<dist){
                dist=x;
                moto=&motos[i];
            }                        
        }
    return moto;
}