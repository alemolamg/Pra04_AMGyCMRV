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


void EcoCityMoto::cargarMotos(string fileNameMotos){ //ToDo: adaptar para map

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

                motos.push_back(moto);
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

/*void EcoCityMoto::cargarClientes(string fileNameClientes){//ToDo: adaptar para map
    std::ifstream fe;                    
    string linea,tipofichero;                   
    int total = 0;                  
    
    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon; 


    fe.open(fileNameClientes);
    
    if(fe.good()){
        double maxLon=-9999999, maxLat=-9999999, minLon=9999999, minLat=9999999;
        //Mientras no se haya llegado al final del fichero
        stringstream ss1;
        getline(fe, linea); //Se salta la primera linea, solo info
        ss1 << linea;
         //leemos la clave
        getline(ss1,tipofichero,';');     
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
                //clientes.inserta(client); //No Sirve ya
              
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
}*/


void EcoCityMoto::cargarClientes(const string &fileNameClientes){
    ifstream fe;                    //Flujo de entrada
    string tipofichero,linea;                   //Cada línea tiene un clienete
    int total = 0;                  //Contador de líneas o clientes
    
    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon; 

    //Asociamos el flujo al fichero 
    fe.open(fileNameClientes);
    
    if(fe.good()){
        double maxLon=-9999999, maxLat=-9999999, minLon=9999999, minLat=9999999;
        //Mientras no se haya llegado al final del fichero
        stringstream ss1;
        getline(fe, linea); //ojo
        ss1 << linea;
        //Leemos clave de fichero
        getline(ss1,tipofichero,';');       
        if (tipofichero=="1"){
            
            getline(fe, linea);     //Toma una línea del fichero
            while(!fe.eof()){            
                stringstream ss;        //Stream que trabaja sobre buffer interno         
                if(linea!=""){
                    ++total;
                }            
                if(total>=1){                
                    //Inicializamos el contenido de ss
                    ss << linea;
                    //Leemos el NIF
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
                    //calculamos Latitud y longitud max y min
                    if (dlon>maxLon)
                        maxLon=dlon;
                    else
                        if (dlon<minLon)
                            minLon=dlon;

                    if (dlat>maxLat)
                        maxLat=dlat;
                    else
                        if (dlat<minLat)
                            minLat=dlat;
                    //con todos los atributos leídos, se crea el cliente
                    Cliente client (dni, nombre, pass, direccion,dlat, dlon, this);
                    clientes[dni]=client;                

                 //   std::cout << client.GetDni() << ";" << client.GetNombre() <<std::endl;            
                }              
                getline(fe, linea);     //Toma una línea del fichero
            }
            crearItinerarios(3,UTM(minLat,minLon),UTM(maxLat,maxLon));
        }else{
            getline(fe, linea);     //Toma una línea del fichero
            while(!fe.eof()){            
                stringstream ss;        //Stream que trabaja sobre buffer interno         
                if(linea!=""){
                    ++total;
                }            
                if(total>=1){                
                    //Inicializamos el contenido de ss
                    ss << linea;
                    //Leemos el NIF
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
                    clientes[dni]=client;                
                    map<string,Cliente>::iterator itCli= clientes.find(dni);
                    string nIti,mot;
                    int id,dia,mes,anio,hora,min,minutos;
                    float iniLat,finLat,iniLon,finLon;
                    getline(ss,nIti,';');               
                    //stringstream ss3;
                    for (int i=0; i<stoi(nIti); i++){
                        getline(fe, linea);
                        stringstream ss3;
                        ss3 << linea;
                        ss3 >> id; ss3.ignore(1);
                        ss3 >> iniLat; ss3.ignore(1);
                        ss3 >> iniLon; ss3.ignore(1);
                        ss3 >> finLat; ss3.ignore(1);
                        ss3 >> finLon; ss3.ignore(1);
                        ss3 >> dia; ss3.ignore(1);
                        ss3 >> mes; ss3.ignore(1);
                        ss3 >> anio; ss3.ignore(1);
                        ss3 >> hora; ss3.ignore(1);
                        ss3 >> min; ss3.ignore(1);
                        ss3 >> minutos; ss3.ignore(1);
                        ss3 >> mot;
                        vector<Moto>::iterator itMoto=find(motos.begin(),motos.end(),mot);
                        Itinerario iti(id,UTM(iniLat,iniLon),UTM(finLat,finLon),Fecha(dia,mes,anio,hora,min),minutos,&(*itMoto));;
                        itCli->second.cargaItinerario(iti);
                                               
               //id;inicioLat;inicioLon;finLat;finLon;dia;mes;anio;hora;minuto;minutos;moto
                        
                    }                    
                    
                 //   std::cout << client.GetDni() << ";" << client.GetNombre() <<std::endl;            
                }              
                getline(fe, linea);     //Toma una línea del fichero
            }
        }
        
        std::cout<<"Total de clientes en el fichero: " << total <<endl;
        fe.close(); //Cerramos el flujo de entrada        
    }else{
        std::cerr<<"No se puede abrir el fichero"<<endl;
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


Cliente& EcoCityMoto::buscarCliente(string dni){
    map<string,Cliente>::iterator it;
    it=clientes.find(dni);
    if(it!= clientes.end()){
        Cliente &encontrado =(it->second);
        std::cout << it->second.getRutas().size() << std::endl;
        return encontrado;
    }
        
    throw std::invalid_argument("No esta este cliente");
}

map<string,Cliente>& EcoCityMoto::getClientes(){
    return clientes;
}

vector<Moto>& EcoCityMoto::getMotos(){
    return motos;
}

void EcoCityMoto::desbloqueaMoto(Moto* moto, Cliente* cli) {
    moto->seActiva(cli);
    ++idUltimo;
}

Moto* EcoCityMoto::LocMotoCercana(UTM& ubicacion) {
    Moto *moto;
    
    double dist=999999999, x;
    for (int i=0; i<motos.capacity()-1;i++)                  
        if (motos[i].getStatus()==Bloqueado){
            x=ubicacion.distancia(motos[i].getPosicion());   //distancia en UTM 
            if (x<dist){
                dist=x;
                moto=&motos[i];
            }                        
        }
    return moto;
}

void EcoCityMoto::crearItinerarios(int num, const UTM& min, const UTM& max) {
    map<string,Cliente>::iterator iterador=clientes.begin();
    while (iterador!=clientes.end()) {
        iterador->second.crearItinerario(num,idUltimo,min,max);
        idUltimo+=num;
        ++iterador;
    }
}
