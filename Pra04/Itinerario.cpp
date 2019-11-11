/* 
 * File:   Itinerario.cpp
 * Author: Cayetano
 * 
 * Created on 10 de octubre de 2019, 10:51
 */
#include "Itinerario.h"

Itinerario::Itinerario(Fecha fecha,UTM _inicio,UTM _final, int _id,int _minutos,Moto *m):
fecha(fecha),inicio(_inicio),fin(_final),id(_id),minutos(_minutos),vehiculo(m){
};

Itinerario::Itinerario(int _id, const UTM& _inicio, const UTM& _fin, const Fecha& _fecha, int _minutos, Moto* m ):
        id(_id), inicio(_inicio), fin(_fin), 
        fecha(_fecha), minutos(_minutos), vehiculo(m) {}


Itinerario::Itinerario(const Itinerario& orig):
fecha(orig.fecha),inicio(orig.inicio),fin(orig.fin),
        id(orig.id),minutos(orig.minutos),vehiculo(orig.vehiculo){
};

Itinerario::~Itinerario() {
}

Moto* Itinerario::GetVehiculo() const {
    return vehiculo;
}

void Itinerario::SetFecha(Fecha fecha) {
    this->fecha = fecha;
}

Fecha Itinerario::GetFecha() const {
    return fecha;
}

void Itinerario::SetFin(UTM fin) {
    this->fin = fin;
}

UTM Itinerario::GetFin() const {
    return fin;
}

UTM Itinerario::GetInicio() const {
    return inicio;
}

void Itinerario::SetMinutos(int minutos) {
    this->minutos = minutos;
}

int Itinerario::GetMinutos() const {
    return minutos;
}

int Itinerario::GetId() const {
    return id;
}





