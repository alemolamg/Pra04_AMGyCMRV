/* 
 * File:   Itinerario.h
 * Author: Cayetano
 * Created on 10 de octubre de 2019, 10:51
 */

#ifndef ITINERARIO_H
#define ITINERARIO_H
#include "fecha.h"
#include "UTM.h"
#include "Moto.h"

class Itinerario {
private:
    int id;
    int minutos;
    UTM inicio;
    UTM fin;
    Fecha fecha;
    Moto *vehiculo;
    
public:
    Itinerario(Fecha fecha ,UTM _inicio,UTM _final, int _id,int _minutos,Moto* m=0);
    Itinerario(int _id, const UTM &_inicio, const UTM &_fin, const Fecha &_fecha, int _minutos, Moto* m=0);//NUEVO
    Itinerario(const Itinerario& orig);
    virtual ~Itinerario();
    Moto* GetVehiculo() const;
    void SetFecha(Fecha fecha);
    Fecha GetFecha() const;
    void SetFin(UTM fin);
    UTM GetFin() const;
    UTM GetInicio() const;
    void SetMinutos(int minutos);
    int GetMinutos() const;
    int GetId() const;
};

#endif /* ITINERARIO_H */

