/* 
 * File:   EcoCityMoto.cpp
 * Author: Alemol
 * 
 * Created on 28 de octubre de 2019, 11:38
 */
#include <fstream>
#include <sstream>
#include "EcoCityMoto.h"

EcoCityMoto::EcoCityMoto(const EcoCityMoto& orig):
    idUltimo(orig.idUltimo),motos(orig.motos),clientes(orig.clientes){}


EcoCityMoto::~EcoCityMoto() {
    guardarClientesItinerarios("prueba.txt");
    std::cout<<"Guardado archivo correctamente"<<std::endl;
}


void EcoCityMoto::cargarMotos(string fileNameMotos){ 

    ifstream fe;               
    string linea;                   
    int total = 0;                 
    
    
    string matricula, latitud, longitud,estado;
    double dlat, dlon;
    int destado;
    tipoEstado tipo;


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
               //std::cout << moto.getId() << ";" << moto.getPosicion().latitud <<std::endl;            
            }              
            getline(fe, linea);     //Toma una línea del fichero
        }    
        cout<<"Total de motos en el fichero: " << total <<endl;
        fe.close();     
        
    }else{
        cerr<<"No se puede abrir el fichero"<<endl;
    }
}

void EcoCityMoto::cargarClientes(const string &fileNameClientes){
    ifstream fe;                    //Flujo de entrada
    string tipofichero,linea;       //Cada línea tiene un clienete
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
        getline(fe, linea); // quitamos la primera línea
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

                   //std::cout << client.GetDni() << ";" << client.GetNombre() <<std::endl;            
                }              
                getline(fe, linea);     //Toma una línea del fichero
            }
            //ToDo: num itinerarios aleatorios
            int numItiAlt= 1+rand()%10;
            crearItinerarios(numItiAlt,UTM(minLat,minLon),UTM(maxLat,maxLon));
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
                    //obtengo un iterador al cliente insertado para asignarle los itinerarios
                    map<string,Cliente>::iterator itCli= clientes.find(dni);
                    string nIti,mot;
                    int id,dia,mes,anio,hora,min,minutos;
                    float iniLat,finLat,iniLon,finLon;
                    getline(ss,nIti,';');               
              
                    for (int i=0; i<stoi(nIti); i++){
                        getline(fe, linea);
                        stringstream ss_;
                        ss_ << linea;
                        ss_ >> id; ss_.ignore(1);
                        ss_ >> iniLat; ss_.ignore(1);
                        ss_ >> iniLon; ss_.ignore(1);
                        ss_ >> finLat; ss_.ignore(1);
                        ss_ >> finLon; ss_.ignore(1);
                        ss_ >> dia; ss_.ignore(1);
                        ss_ >> mes; ss_.ignore(1);
                        ss_ >> anio; ss_.ignore(1);
                        ss_ >> hora; ss_.ignore(1);
                        ss_ >> min; ss_.ignore(1);
                        ss_ >> minutos; ss_.ignore(1);
                        ss_ >> mot;
                        //vector<Moto>::iterator itMoto=find(motos.begin(),motos.end(),mot);
                        vector<Moto>::iterator itMoto=motos.begin();
                        while (itMoto!=motos.end()){
                            if ((*(itMoto)).getId()==mot){                             
                                break;
                            }
                            itMoto++;
                        }
                        Itinerario iti(id,UTM(iniLat,iniLon),UTM(finLat,finLon),Fecha(dia,mes,anio,hora,min),minutos,&(*itMoto));;
                        itCli->second.cargaItinerario(iti);   //agregamos itinerario al cliente                                  
                    }                                                               
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

EcoCityMoto::EcoCityMoto(const string& fileClientes, const string& fileMotos):
    idUltimo(0), clientes(), motos(){
    cargarMotos(fileMotos);
    cargarClientes(fileClientes);
}

    
unsigned EcoCityMoto::GetIdUltimo() const{
        return idUltimo;
}

void EcoCityMoto::SetIdUltimo(unsigned nuevoIdUltimo){
    idUltimo=nuevoIdUltimo;
}


Cliente* EcoCityMoto::buscarCliente(string dni){
    map<string,Cliente>::iterator it;
    it=clientes.find(dni);
    if(it!= clientes.end()){
        //return (&(it->second)); //ToDo: cambiar cabacera referencia por puntero para que esto funcione
        Cliente* encontrado =(&(it->second));
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
    Moto *MotoCer=0;
    double dist=999999999, x;
    for (int i=0; i<motos.size()-1;i++)                  
        if (motos[i].getStatus()==Bloqueado){ 
            x=ubicacion.distancia(motos[i].getPosicion());   //distancia en UTM 
            if (x<dist){
                dist=x;
                MotoCer=&motos[i];
            }                        
        }
    return MotoCer;
}

void EcoCityMoto::crearItinerarios(int num, const UTM& min, const UTM& max) {
    map<string,Cliente>::iterator iterador=clientes.begin();
    while (iterador!=clientes.end()) {
        iterador->second.crearItinerario(num,idUltimo,min,max);
        idUltimo=idUltimo+num;
        ++iterador;
    }
}

void EcoCityMoto::guardarClientesItinerarios(const string& fileName) {
     ofstream fs;                    //Flujo de salida
    //Asociamos el flujo al fichero 
    fs.open(fileName,ofstream::trunc);
    
    if(fs.good()){
        map<string,Cliente>::iterator it=clientes.begin();
        fs << "2;NIF;clave;nomape;dirección;latitud;longitud;nIti;bajar_linea;id;inicioLat;inicioLon;finLat;finLon;dia;mes;anio;hora;minuto;minutos;moto" << endl;
        while (it!=clientes.end()){
            Cliente cli=it->second;
           // if (cli.GetDni()=="52525252X")
             //   cout << ",";
            list<Itinerario> r=cli.getRutas();
            list<Itinerario>::iterator it2=r.begin();
            fs << cli.GetDni() <<";"<< cli.GetPass() <<";"<< cli.GetNombre() <<";"<<
                  cli.GetDireccion() <<";"<< cli.getPosicion().GetLatitud() <<";"<<
                  cli.getPosicion().GetLongitud() <<";"<< cli.getRutas().size() << endl;
            while (it2!=r.end()){
                fs << it2->GetId() <<";"<< it2->GetInicio().GetLatitud() <<";"<<
                   it2->GetInicio().GetLongitud() <<";"<< it2->GetFin().GetLatitud() <<";"<<
                   it2->GetFin().GetLongitud() <<";"<< it2->GetFecha().verDia() <<";"<<
                   it2->GetFecha().verMes() <<";"<< it2->GetFecha().verAnio() <<";"<<
                   it2->GetFecha().verHora() <<";"<< it2->GetFecha().verMin() <<";"<< 
                   it2->GetMinutos() <<";"<< it2->GetVehiculo()->getId() << endl;
                it2++;
            }
            it++;
        }
    
        fs.close(); //Cerramos el flujo de entrada        
    }else{
        std::cerr<<"No se puede crear el fichero"<<endl;
    } 
}

bool EcoCityMoto::nuevoCliente(Cliente& nuevoCli) {
    std::string clave=nuevoCli.GetDni();
    return (clientes.insert(std::pair<std::string,Cliente>(clave,nuevoCli)).second);
}

bool EcoCityMoto::eliminarCliente(std::string borrameid) {
    return clientes.erase(borrameid);
}

vector<Moto> EcoCityMoto::localizaMotosSinBateria() {
    vector<Moto> vecMotos;
        for (int i=0; i<motos.size(); i++)
            if (motos[i].getPorcentajeBateria()<15)
                vecMotos.push_back(motos[i]);
        return vecMotos;
}

