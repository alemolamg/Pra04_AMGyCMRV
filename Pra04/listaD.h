#ifndef LISTAD_H_INCLUDED
#define LISTAD_H_INCLUDED

#include <stdexcept>


template<class T>
class ListaD {
   
    template<class X>
    class Nodo {

    public:
        X dato;
        Nodo *ant, *sig;
        Nodo(const X &aDato, Nodo *aAnt = 0, Nodo *aSig = 0):
            dato(aDato), ant(aAnt), sig(aSig) {}
        ~Nodo() {}
    };

    Nodo<T> *cabecera, *cola;
    unsigned tama;

 public:
     

    class Iterador {
    public:
        Nodo<T> *nodo;

        Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}

        bool hayAnterior() { return nodo !=0; }
        bool haySiguiente() { return nodo !=0; }

        bool fin() { return nodo == 0; }
        void anterior() {
             nodo = nodo->ant;
        }
        void siguiente() {
             nodo = nodo->sig;
        }
     
        T &dato() { return nodo->dato; }
        ~Iterador() {}
    };

    ListaD() : cabecera(0), cola(0), tama(0) {}
    ListaD(const ListaD<T> &l);
    ListaD<T> &operator=(const ListaD<T> &l);
    ~ListaD();
    Iterador iterador() const;
    Iterador iteradorFin() const;
        
    void insertarInicio(const T &dato);
    void insertarFinal(const T &dato);
    void insertar(Iterador &p,const T &dato);
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador *p);
    ListaD<T> concatena(const ListaD<T> &l);
    T &inicio();
    T &fin();
    unsigned tam();
   
};


template<class T>
ListaD<T>::ListaD(const ListaD<T> &l):tama(0){

    Nodo<T> *p;
    cabecera=0;
    cola=0;
    p=l.cabecera;    
    
    while (p!=0){
        insertarFinal(p->dato);
        p=p->sig;
    }
};

template<class T>
ListaD<T> &ListaD<T>::operator=(const ListaD<T> &l){

    Nodo<T> *p=cabecera;
    
    while (p!=0){
        borrarInicio();
        p=cabecera;
    }
    cabecera=0;
    cola=0;
    p=l.cabecera;
    tama=0;
    while (p!=0){
        insertarFinal(p->dato); 
        p=p->sig;
    }
    return (*this);
}

template<class T>
ListaD<T>::~ListaD(){
    if (cabecera) {
        Nodo<T> *borra = cabecera;
        while ( borra ){
            cabecera= cabecera->sig;
            delete borra;
            borra=cabecera;
        }
        cola = cabecera = 0;
        tama=0;
    }
};


template<class T>
typename ListaD<T>::Iterador ListaD<T>::iterador() const { 
    return Iterador (cabecera);}

template<class T>
typename ListaD<T>::Iterador ListaD<T>::iteradorFin() const { 
    return Iterador (cola);}


template<class T>
void ListaD<T>::insertarInicio(const T &dato){
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0, cabecera);
    tama++;
   
    if (cola == 0)
        cola = nuevo;

    if (cabecera != 0)  
        cabecera->ant = nuevo;

    cabecera = nuevo;
};

template<class T>
void ListaD<T>::insertarFinal(const T &dato){
    Nodo<T> *nuevo;
    tama++;
    nuevo = new Nodo<T>(dato, cola, 0);
   
    if (cabecera == 0)
        cabecera = nuevo;  

    if (cola != 0)
        cola->sig = nuevo;

    cola = nuevo;
};

template<class T>
void ListaD<T>::insertar(Iterador &p,const T &dato){

 if (!p.fin()) {
    if (p.nodo==cabecera){
        this->insertarInicio();
    } else {       
            Nodo<T> *nuevo;
            nuevo = new Nodo<T>(dato, p.nodo->ant, p);

            p.nodo->ant->sig = nuevo;
            p.nodo->ant = nuevo;
            tama++;
       
    }
 }
}

template<class T>
void ListaD<T>::borrarInicio(){
 if (cabecera) {
     tama--;
    Nodo<T> *borrado = cabecera;
    cabecera= cabecera->sig;
    delete borrado;
    if (cabecera != 0)
        cabecera->ant = 0;
    else
        cola = 0;
 }
}

template<class T>
void ListaD<T>::borrarFinal(){
 if (cola) {
     tama--;
    Nodo<T> *borrado = cola;
    cola= cola->ant;
    delete borrado;
    
    if (cola != 0)
        cola->sig = 0;
    else
        cabecera = 0;
 }
}

template<class T>
void ListaD<T>::borrar(Iterador *p){

	if (p.nodo!=0 && cabecera !=0){
		if (cabecera==cola){
			cabecera=cola= 0;
		} else {
			if (p.nodo==cabecera){    
				cabecera=cabecera->sig;
				p.nodo->sig->ant=0;

			} else {
				if (p.nodo==cola){   
					cola=cola->ant;
					p.nodo->ant->sig=0;

				} else{
					p.nodo->ant->sig=p.nodo->sig;
					p.nodo->sig->ant=p.nodo->ant;
				}
			}
		}
		delete p;
                tama--;
	}
}

template<class T>
T & ListaD<T>::inicio(){ 
    if (!cabecera) 
        throw std::logic_error("No existe valor inicial");
    return cabecera->dato;
};

template<class T>
T & ListaD<T>::fin(){ 
    if (!cola) 
        throw std::logic_error("No existe valor final");
    return cola->dato;
};

template<class T>
unsigned ListaD<T>::tam() {
    return tama;
};

template<class T>
ListaD<T> ListaD<T>::concatena(const ListaD<T> &l){
    
    if ((*this).tama==0 && l.tama!=0)  //por acabar antes pero no es obligatorio
        return l;
    if ((*this).tama!=0 && l.tama==0)  //por acabar antes pero no es obligatorio
        return *this;
    ListaD<T> ret(*this);
    Iterador it=l.iterador();
    while (!it.fin()){
        ret.insertarFinal(it.dato());
        it.siguiente();
    }
    ret.tama=this->tam+l.tama;  //no necesario
    return ret;
}


 
#endif // LISTAD_H_INCLUDED
