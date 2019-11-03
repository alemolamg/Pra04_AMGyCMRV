/* 
 * File:   ListaDEnlazada.h
 * Author: molej
 *
 * Created on 3 de octubre de 2019, 10:52
 */

#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include <propidl.h>
#include "Nodo.h"

/*template<class T>
class ListaDEnlazada;*/

template<class T>
class ListaDEnlazada{
    


    class Iterador{
        Nodo<T> *nodo=nullptr;
        //friend class ListaDEnlazada<T>;
        public:
            
            Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
            bool fin() { return nodo == 0; }
            void siguiente() {nodo = nodo->siguiente; }
            void anterior() {nodo = nodo->anterior; }
            bool hayAnterior() { return nodo !=0; }
            bool haySiguiente() { return nodo !=0; }
            T &dato() { return nodo->dato; }
    ~Iterador() {}
        
    };

public:
        
    ListaDEnlazada();
    ListaDEnlazada(const ListaDEnlazada &l);
    void insertarInicio(T &dato);
    void insertarFinal(T &dato);
    //Iterador iteradorInicio() { return Iterador<T>(cabecera); };
    //Iterador iteradorFinal() { return Iterador<T>(cola); };
    void insertar(Iterador &i, T &dato); //hay un mini busca; REVISAR JUNTO LA PRACTICA
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador *i);
    ListaDEnlazada &operator=(ListaDEnlazada<T> &l);
    
    T &inicio() { return cabecera->dato; };
    T &fin() { return cola->dato; };
    
    
    virtual ~ListaDEnlazada(){};    
    
    //No TERMINADAS
    //void buscaEnLista(Iterador<T> & ite, T &dato);//AYUDA

private:
    Nodo<T> *cabecera=0, *cola=0;
    unsigned tam=0;

};

template<class T>
ListaDEnlazada<T>::ListaDEnlazada():
    cabecera(nullptr),cola(nullptr), tam(0){
};

template<class T>
void ListaDEnlazada<T>::insertarInicio(T &dato){
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0, cabecera);
    tam++;
    if(cabecera){   
        nuevo->siguiente=cabecera->siguiente;
        nuevo->siguiente->anterior=nuevo;
    }else{
        cola=nuevo;
        nuevo->siguiente=nullptr;
    }   
    cabecera=nuevo;
    nuevo->anterior=nullptr;
    tam++;
};

template<typename T>
void ListaDEnlazada<T>::insertarFinal(T &dato){
    Nodo<T> *nuevoN=new Nodo<T>(dato,cola,0);
    if(cola){
        nuevoN->anterior=cola;
        cola=nuevoN;
        
    }else{
        cabecera->siguiente=nuevoN;
        }
    nuevoN->anterior->siguiente=nuevoN;
    tam++;
    
};

template<typename T>
void ListaDEnlazada<T>::insertar(Iterador &i, T &dato){
    bool existeEnLista=false;
    Nodo<T> nuevo(dato);
    Iterador *p=cabecera;
    do{
        if(i==p)
            existeEnLista=true;
        p=p->siguiente();
    }while(p->siguiente()!=nullptr);
    
    if(existeEnLista){
        if(cabecera!=nullptr){
            i.nodo->anterior->siguiente=nuevo;
            nuevo.anterior=i.nodo->anterior;
            nuevo.siguiente=i;
            i.nodo->anterior=nuevo;
            ++tam;
       
        }else
            insertarInicio(dato);
    }
};

template<typename T>
void ListaDEnlazada<T>::borrarInicio(){
    if(cabecera){
        Iterador *borrame=cabecera;
    
        cabecera=cabecera->siguiente;
        cabecera->siguiente->anterior=nullptr;
    
        delete borrame->nodo;
        tam--;
    }
};

template<typename T>
void ListaDEnlazada<T>::borrarFinal(){
    if(cola){
        Iterador *borrame=cola;
    
        cola=cola->anterior;
        cola->siguiente=nullptr;
        
    
        delete borrame;
        tam--;
    }
};

template <class T>
void ListaDEnlazada<T>::borrar(Iterador *i){
    if (i.nodo!=0 && cabecera !=0){
		if (cabecera==cola){
			cabecera=cola= 0;
		} else {
			if (i->nodo==cabecera){
                            borrarInicio();
			} else {
				if (i->nodo==cola){   
                                    borrarFinal();
				} else{
					i->nodo->anterior->siguiente=i->nodo->siguiente;
					i->nodo->siguiente->anterior=i->nodo->anterior;
				}
			}
		}
		delete i->nodo                                                                                                     ;
                tam--;
	}

};

template<class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada& l): tam(l.tam){
    Nodo<T> *p;
    cabecera=0;
    cola=0;
    p=l.cabecera;
    
    while (p!=0){
        insertarInicio(p->dato);
        p=p->siguiente;
    }
};

template <class T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator= (ListaDEnlazada<T>& l){
    Nodo<T> *p=cabecera;
    
    while (p!=0){
        borrarInicio();
        p=cabecera;
    }
    cabecera=0;
    cola=0;
    p=l.cabecera;
    tam=0;
    while (p!=0){
        insertarFinal(p->dato);
        p=p->siguiente;
    }
    return (*this);
};


#endif /* LISTADENLAZADA_H */

