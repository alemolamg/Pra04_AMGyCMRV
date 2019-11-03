/* 
 * File:   nodo.h
 * Author: molej
 *
 * Created on 3 de octubre de 2019, 10:58
 */

#ifndef NODO_H
#define NODO_H
#include <stdio.h>

template<typename T>
class Nodo {
public:
    friend class ListaDEnlazada;
    T dato;
    Nodo *anterior=0,*siguiente=0;
    
    Nodo(T &datoE, Nodo *AntE=0, Nodo *SigE=0);
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    //bool operator==(const nodo<T>& otro);
    

};
//template<typename T>
//Nodo<T>::Nodo():dato(0), anterior(nullptr),siguiente(nullptr) {};

template<typename T>
Nodo<T>::Nodo(T &datoE, Nodo *AntE, Nodo *SigE):
    dato(datoE), anterior(AntE),siguiente(SigE) {};

/*template<typename T>
nodo<T>::operator ==(const nodo<T>& otro){
    //Opcion 1
    return (dato==otro.dato);
    //Opcion 2
    /*if(this->anterior==otro.anterior && this->siguiente==otro.siguiente)
        return (dato==otro.dato);};*/   

template<typename T>
Nodo<T>::Nodo(const Nodo& orig):
    dato(orig.dato),anterior(orig.anterior),siguiente(orig.siguiente){};    
    
#endif /* NODO_H */

