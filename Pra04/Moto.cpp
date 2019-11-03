/* 
 * File:   Moto.cpp
 * Author: Cayetano
 * Created on 28 de octubre de 2019, 9:10
 */

#include "Moto.h"

Moto::Moto(tipoEstado _status,string _id,double _dlat,double _dlon ):
    status(_status),id(_id),posicion(_dlat,_dlon),usadoPor(nullptr)
{
}

Moto::Moto(const Moto& orig):
    status(orig.status),id(orig.id),posicion(orig.posicion),usadoPor(orig.usadoPor){
}

Moto::~Moto() {
}

bool Moto::operator==(const Moto& orig) {
    return id==orig.id;
}
bool Moto::operator<(const Moto &orig){
    return id<orig.id;
}
Moto& Moto::operator=(const Moto& orig) {
    if(this!=&orig){
        status=orig.status;
        id=orig.id;
        posicion=orig.posicion;
        usadoPor=orig.usadoPor;
    }
    return *this;
}

void Moto::seActiva(Cliente *cli){
    usadoPor=cli;
    status = Activo;
}
void Moto::seDesactiva(){
    usadoPor=0;
    status=Bloqueado;
}

UTM Moto::getPosicion() const {
    return posicion;
}

tipoEstado Moto::getStatus() const {
    return status;
}

string Moto::getId() const {
    return id;
}