/* File:   AVL.h
 * Author: Alemol
 *
 * Created on 17 de octubre de 2019, 11:04
 */

#ifndef AVL_H
#define AVL_H

#include <inttypes.h>
#include <iostream>

#include "Nodo.h"


template <class T>
class AVL;

template <class T>
class NodoAVL{   
private:
    NodoAVL<T> *izq;
    NodoAVL<T> *der;
    char bal; // -1, 0 , 1 para un árbol avl
    T dato;
    friend class AVL<T>;
public:
    NodoAVL(const T &ele): izq(0), der(0), bal(0), dato(ele){}
    NodoAVL(const NodoAVL<T> &orig): izq(0), der(0), bal(orig.bal), dato(orig.dato){}
    
};


template <class T>
class AVL {
private:
    NodoAVL<T> *raiz;
    int tamanio=0;
    //FUNCIONES
    void copiaAVL(NodoAVL<T>* &q,NodoAVL<T> *p);
    void inorden(NodoAVL<T> *p, int nivel);
    int insertaDato(NodoAVL<T>* &p,const T &dato);
    void rotDer(NodoAVL<T>* &nod);
    void rotIzq(NodoAVL<T>* &nod);
    NodoAVL<T> *buscaClave (const T &dato, NodoAVL<T> *p);
    
    unsigned int numElementosPr(NodoAVL<T>* p);
    void alturaPr(NodoAVL<T>* p, int nivel, int &result);
    
    void destruyeArbol(NodoAVL<T>* &p);    
    
        
public:
    AVL(): raiz(0),tamanio(0){};
    AVL(const AVL& orig);
    void recorreInorden() { inorden(raiz,0); };
    AVL<T>& operator=(const AVL<T>& orig);
    bool busca (const T &dato, T &result);
    bool buscaIt(const T &dato, T &result);
    unsigned int numElementos();
    unsigned int altura();  
    bool inserta(const T &dato);
    
    ~AVL(){destruyeArbol(raiz); };                     
};

template<class T>
AVL<T>::AVL(const AVL& orig){
    copiaAVL(raiz,orig.raiz),tamanio(orig.tamanio);
};

template<class T>
void AVL<T>::copiaAVL(NodoAVL<T>* &q,NodoAVL<T> *p){
    if (p){
        q= new NodoAVL<T> (*p);
        copiaAVL(q->izq,p->izq);
        copiaAVL(q->der,p->der);
    }else
        q=0;
}

template<class T>
void AVL<T>::inorden(NodoAVL<T> *p, int nivel){
    if (p){
        //Miramos izq
        inorden (p->izq, nivel+1);
        std::cout << p->dato << " en el nivel " << nivel << std::endl;        
        // Miramos der
        inorden (p->der, nivel+1);
    }
};

template<class T>
void AVL<T>::destruyeArbol(NodoAVL<T>*& p){
  if(p){
      destruyeArbol(p->izq);
      destruyeArbol(p->der);
      delete p;
      p=0;
  }  
};

template<class T>
int AVL<T>::insertaDato(NodoAVL<T>*& c, const T& dato){
    NodoAVL<T> *p = c;
    int deltaH = 0;
    if (!p){
        p = new NodoAVL<T>(dato);
        c = p; deltaH=1;
    }else if (dato > p->dato){
        if (insertaDato(p->der, dato)){
            p->bal--;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDer(p->der);
                    rotIzq(c);
            }
        }
    }
    else if (dato < p->dato){
        if (insertaDato(p->izq, dato)){
        p->bal++;
        if (p->bal==1) deltaH = 1;
        else if (p->bal == 2){
            if (p->izq->bal == -1) rotIzq(p->izq);
                rotDer(c);
            }
        }
    }
    return deltaH;
};

template<class T>
void AVL<T>::rotDer(NodoAVL<T>*& nod){
    NodoAVL<T> *q = nod;
    NodoAVL<T> *l;
    nod = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;
};

template<class T>
void AVL<T>::rotIzq(NodoAVL<T>* &nod){
    NodoAVL<T> *q = nod, *r;
    nod = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;
};

template<class T>
AVL<T>& AVL<T>::operator =(const AVL<T>& orig){
    if(this!=&orig){
        destruyeArbol(raiz);
        copiaAVL(raiz,orig.raiz);
    }
    return *this;
};

template<class T>
bool AVL<T>::busca(const T& ele, T& result){
    NodoAVL<T> *p=(buscaClave(ele,raiz));
    if(p){
        result=p->dato;
        return true;
    }
    return false;
};

template <class T>
NodoAVL<T> *AVL<T>::buscaClave (const T &dato, NodoAVL<T> *p){
if (!p)
    return 0;
else{ 
    if (dato < p->dato)
        return buscaClave (dato, p->izq);
     else if (dato > p-> dato)
            return buscaClave (dato, p->der);
     else
            return p;
    }
}

template <class T>
bool AVL<T>::buscaIt(const T& dato, T& result){
    NodoAVL<T>* p = raiz;
    while(p){
        if(dato < p->dato)
            p=p->izq;
        else
            if(dato >p->dato)
                p=p->der;
            else{
                result = p->dato;
                return true;
            }
    }
    return false;
    
};

template <class T>
unsigned int AVL<T>::numElementosPr(NodoAVL<T>* p){
    if(p)
        return numElementosPr(p->izq)+numElementosPr(p->der)+1;
    else
        return 0;
};

template <class T>
unsigned int AVL<T>::numElementos(){
    return numElementosPr(raiz);
};


template <class T>
void AVL<T>::alturaPr(NodoAVL<T>* p, int nivel, int& result){
    if(p){
        alturaPr(p->izq,nivel+1,result);
        if (nivel>result)
            result=nivel;
        alturaPr(p->der,nivel+1,result);
    }
};

template <class T>
unsigned int AVL<T>::altura(){
  int resultado=0;
  alturaPr(raiz,0,resultado);
  return resultado;  
};

template <class T>
bool AVL<T>::inserta(const T& dato){
    T resultado;
    bool encontrado = busca(dato, resultado);
    if (!encontrado){
        insertaDato(raiz, dato);
        ++tamanio;
        return true;
    }
    return false;
};

#endif /* AVL_H */

