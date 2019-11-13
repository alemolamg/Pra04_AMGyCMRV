/* File:   EcoCityMoto.h
 * Author: Alemol
 * Created on 28 de octubre de 2019, 11:38
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include <algorithm>
#include "Cliente.h"
#include "Moto.h"
#include <vector>
#include <map>
#include<stdlib.h>
#include<time.h>

using namespace std;

class EcoCityMoto {
private:
    unsigned idUltimo;
    vector <Moto> motos;
    map <string,Cliente> clientes;
    
    //---FUNCIONES----------//
    void cargarMotos(string fileNameMotos);
    void cargarClientes(const string &fileNameClientes);
    void crearItinerarios(int num,const UTM &min,const UTM &max);
    void guardarClientesItinerarios(const string &fileName);    
    //bool nuevoCliente(Cliente& nuevoCli);
        
public:
    EcoCityMoto(const string &fileClientes,const string &fileMotos);
    EcoCityMoto(const EcoCityMoto& orig);
    
    unsigned GetIdUltimo() const;
    void SetIdUltimo(unsigned nuevoIdUltimo);
    
    vector<Moto> localizaMotosSinBateria();
    Moto* LocMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);   
    
    bool nuevoCliente(Cliente& nuevoCli);
    Cliente* buscarCliente(string dni);
    map<string,Cliente>& getClientes();
    vector<Moto>& getMotos();
    bool eliminarCliente(std::string borrameid);
    
    virtual ~EcoCityMoto();
          
};

#endif /* ECOCITYMOTO_H */