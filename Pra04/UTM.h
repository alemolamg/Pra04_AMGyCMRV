/* 
 * File:   UTM.h
 * Author: Cayetano
 * Created on 10 de octubre de 2019, 11:03
 */

#ifndef UTM_H
#define UTM_H
#include <cmath>
class UTM {

public:
    double latitud;
    double longitud;
    
    UTM (double _lat, double _long): latitud(_lat), longitud (_long){};
    UTM(const UTM& orig): latitud(orig.latitud),longitud(orig.longitud){};
    double GetLongitud() const {
        return longitud;
    }

    double GetLatitud() const {
        return latitud;
    }
     
    double distancia(const UTM &utm){
        return sqrt(pow(utm.latitud-this->latitud,2)+pow(utm.longitud-this->longitud,2));
    }
    
    virtual ~UTM(){};

private:

      

};

#endif /* UTM_H */

