#ifndef VDinamico_H
#define VDinamico_H


#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>



template<typename T>
class VDinamico{

private:
    void aumenta();
    void disminuye();
    void tamaBase2(unsigned long int &t);
    unsigned long int fisico=1,logico=0;  
    T *v;
    
public:
    VDinamico();
    VDinamico(unsigned long int tama);      
    VDinamico(const VDinamico<T> &orig);
    VDinamico(const VDinamico<T> &origen, unsigned long int inicio, unsigned long int num);
    
    virtual ~VDinamico();
    
    
    VDinamico<T> &operator=(const VDinamico<T> &arr);
    T &operator[](unsigned long int pos);
    void insertar (const T &dato, unsigned long int pos=UINT_MAX);
    T borrar( unsigned long int pos=UINT_MAX);
    unsigned long int tamLogico();
    
    int busquedaBin( T& dato);
    void ordenar();    

};

template<typename T>
VDinamico<T>::VDinamico(){
    logico=0;
    v=new T[fisico=1];
    
};

template<typename T>
VDinamico<T>:: VDinamico(unsigned long int tama){
    logico=0;
    tamaBase2(tama);
    v=new T[fisico=tama];
    
};

template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig):logico(orig.logico){
    v = new T[fisico = orig.fisico];
    for (unsigned long int i=0; i<logico; i++) 
        v[i] = orig.v[i];
};


template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned long int inicio, unsigned long int num){
    /*if(inicio>=origen.logico || num+inicio>origen.logico)
        throw ErrorRango();*/  //terminar luego
    
    int nTam=num;
    tamaBase2(nTam);
    v= new T[fisico=nTam];
    logico=num;
    for (unsigned long int c = inicio;c<inicio+num;c++)
        v[c-inicio]=origen.v[c];
            
};

template <typename T>
VDinamico<T> &VDinamico<T>::operator =(const VDinamico<T>& arr){
    if (this!=&arr){
        delete[] v;
        logico=arr.logico;
        v=new T[fisico=arr.fisico];
        for(unsigned long int c=0; c< logico; c++)
            v[c]=arr.v[c];
    }
    return *this;
};

template<typename T>
//void VDinamico<T>::insertar(const T &dato, unsigned long int pos = UINT_MAX){
void VDinamico<T>::insertar(const T& dato, unsigned long int pos){  
    if(pos==UINT_MAX){
        if(logico==fisico)
            aumenta();
        v[logico]=dato;
    }else{
        /*if(pos>logico)
            throw ErrorRango();*/
        if(logico==fisico)
            aumenta();
        for (unsigned long int i=logico-1;i>=pos;i--)
            v[i+1]=v[i];      
    
        v[pos]=dato;
    }
    logico++;
};


template<typename T>
T VDinamico<T>::borrar (unsigned long int pos){
      T aux;
      /*if (logico==0)
          throw ErrorNoDatos();*/
      if (pos==UINT_MAX){
          if(logico*3<fisico)
              disminuye();
          aux=v[logico-1];
      }else{
          /*if(pos>=logico)
              throw errorRango();*/
          
          if(logico*3<fisico){
              disminuye();
          }
          aux=v[pos];
          for(unsigned i=pos;i<logico-1;i++){
              v[i]=v[i+1];
          }
          
      }
      
    logico--;
    return aux;

};


template<typename T>
void VDinamico<T>::tamaBase2(unsigned long int& tfis){
    int base=2;
        int res=1;
        
        do{
            if(res>=fisico){
                tfis++;
                res=base*res;
            }
        } while (res>fisico);
        logico=tfis;
};

template<typename T>
    int VDinamico<T>::busquedaBin( T& dato){
    int inf=0;
    int sup=logico-1;
    int posIn;
    while (inf<= sup){
       posIn = (inf + sup) / 2;
      
        if (v[posIn] == dato)
        {
            return posIn;
        }
        else 
        {
            if (v[posIn] < dato) 
            {
                inf = posIn + 1;
            }
            else 
            {
                sup = posIn - 1;
            }
        }
    }
    return -1;
};


template<typename T>
void VDinamico<T>::ordenar (){
    sort(v,v+logico);
};


template<typename T>
unsigned long int VDinamico<T>::tamLogico(){
    return logico;
};




template<typename T>
VDinamico<T>::~VDinamico(){
    delete []v;
    v=nullptr;        
    logico=0;
};

template<typename T>
T& VDinamico<T>::operator [](unsigned long int pos){
     return v[pos];
}     

template<class T>
void VDinamico<T>::aumenta(){
    T *vaux;
    vaux= new T[fisico=fisico*2];
    for(unsigned i=0;i<logico;i++)
        vaux[i]=v[i];
    
    delete []v;//eliminamos el vector antiguo
    v=vaux;
}; 

template<class T>
void VDinamico<T>::disminuye(){
    fisico=fisico/3;
    T *vaux = new T[fisico];
    for(unsigned i=0;i<logico;i++){
        vaux[i]=v[i];
    };
    delete []v;
    v=vaux;
}; 


#endif //VDinamico<T>