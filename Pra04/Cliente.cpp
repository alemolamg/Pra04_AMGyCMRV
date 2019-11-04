/* 
 * File:   Cliente.cpp
 * Author: molej
 * 
 * Created on 26 de septiembre de 2019, 11:29
 */
#include "Cliente.h"
#include "Moto.h"
#include "EcoCityMoto.h"


Cliente::Cliente(const Cliente& orig):
        dni(orig.dni),pass(orig.pass), nombre(orig.nombre),
        direccion(orig.direccion),rutas(orig.rutas), acceso(orig.acceso),posicion(orig.posicion)
{}


bool Cliente::operator<(  Cliente& otro)const {
    return dni<otro.dni;
}

bool Cliente::operator== ( const Cliente &otro) {
    //return nombre==otro.nombre;// solo compara nombre completo
    //return nombre.find(otro.GetNombre())!=std::string::npos;//buscar subcadena dentro string 
    return dni==otro.dni;
}

Cliente& Cliente:: operator=(const Cliente &orig) {
    if(this!=&orig){
        nombre=orig.nombre;
        dni=orig.dni;
        pass=orig.pass;
        direccion=orig.direccion;
        posicion=orig.posicion;
        rutas=orig.rutas;
        acceso=orig.acceso;
    }
    return *this;
    }

std::string Cliente::GetDireccion() const {
    return direccion;
}

std::string Cliente::GetNombre() const {
    return nombre;
}

std::string Cliente::GetPass() const {
    return pass;
}

std::string Cliente::GetDni() const {
    return dni;
}

UTM Cliente::getPosicion() const {
    return posicion;
}

double Cliente::distancia(const Cliente& otro) {
    return sqrt(pow((otro.posicion.latitud-posicion.latitud),2)+pow((otro.posicion.longitud-posicion.longitud),2));
}

void Cliente::crearItinerario(int num, int idUltimo, UTM min, UTM max) {
    // pagina: https://blog.martincruz.me/2012/09/obtener-numeros-aleatorios-en-c-rand.html
    //Calcula la Fecha aleatoria
    srand(time(NULL));
    int mes=1+rand()%(13-1);
    int dia;
    int anio=2019+rand()%(11-1);
    if(mes==2){
        dia=1+rand()%(29-1);
    }else 
        if(mes==4||mes==6||mes==9||mes==11){
            dia=1+rand()%(31-1);
        }else
            dia=1+rand()%(32-1);
    
    Fecha fecha(dia,mes,anio);
    
    //Calcula dos UTM aleatorios dentro del rango
    int cont=0;
    double iniY,iniZ,finalY,finalZ;
    do{
        int x=rand()%(10000),xx=rand()%(10000); 
        double y=x/10000, z=xx/10000;
        y=y*(max.latitud-min.latitud)+min.latitud;
        z=z*(max.longitud-min.longitud)+min.longitud;
        if(cont==0){
            iniY=y;
            iniZ=z;
        }else{
            finalY=y;
            finalZ=z;
        }
        ++cont;
    }while(cont<2);  
    
    UTM iniNuevo(iniY,iniZ);
    UTM finNuevo(finalY,finalZ);
    
    //generamos un id aleatorio
    int idNuevo=++idUltimo;
    
    //generamos minutos aleatorios
    int minNuevo=1+rand();
    Itinerario iti(fecha,iniNuevo,finNuevo,idNuevo,minNuevo);
    rutas.push_back(iti);
};

 bool Cliente::operator >( Cliente &otro) const{
     return dni>otro.dni;
 }
 Moto* Cliente::buscarMotoCercana(){
     Moto* m=acceso->LocMotoCercana(posicion);
     return m;
 };
 
 void Cliente::desbloquearMoto(Moto* m){
     Fecha fecha;
     acceso->desbloqueaMoto(m,this);
     UTM inicio=m->getPosicion();
     int y=37000+rand()%(1000), z=3000+rand()%(1000);
     double yy=y/1000,zz=z/1000;
        UTM fin(yy,zz);

     int min = 0;
     rutas.push_back(Itinerario(fecha,inicio,fin,acceso->GetIdUltimo(),min,m));
 };
 
 void Cliente::terminarTrayecto(){ //ToDo: adaptar para porcentaje bateria, Pra04
     list<Itinerario>::iterator i=rutas.end();
     i--;
        i->GetVehiculo()->seDesactiva();  //bloquea la moto y la desvincula del cliente
        Fecha f1= i->GetFecha(); 
        Fecha f2;    
        //ToDo: agregar practica 04 porcentaje bateria
        //int minutos=rand()%(int)i->GetVehiculo().getPorcentajeBateria();
        
        int minutos= (f2.verHora()*60 + f2.verMin())- (f1.verHora()*60 + f1.verMin()); 
        i->SetMinutos(minutos);
        
 }
 
 std::ostream& operator<<(std::ostream& out, const Cliente& f){
        return out << f.GetDni() ;
    }
 /*Itinerario& Cliente::UltimoItinerario() {
     return rutas.end()-1;
}*/
