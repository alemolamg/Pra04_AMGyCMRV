/* 
 * File:   Moto.h
 * Author: Cayetano
 * Created on 27 de octubre de 2019, 12:10
 */

#ifndef MOTO_H
#define MOTO_H
#include "UTM.h"
//#include "Cliente.h"
#include <iostream>
using namespace std;

class Cliente; 

enum tipoEstado{Bloqueado,Activo,SinBateria,Rota};


class Moto {
public:
    Moto(tipoEstado status=Bloqueado,string _id="",double dlat=0.0,double dlon=0.0 );
    
    Moto(const Moto& orig);
    
    virtual ~Moto();
    
    bool operator==(const Moto &orig);
    
    bool operator<(const Moto &orig);
    
    Moto& operator=(const Moto &orig);
    
    void seActiva(Cliente *cli);
    
    void seDesactiva();
    
    UTM getPosicion() const;
    
    tipoEstado getStatus() const;
    
    string getId() const;
    
private:
    string id="";
    tipoEstado status;
    Cliente  *usadoPor; 
    UTM posicion;
};

#endif /* MOTO_H */

