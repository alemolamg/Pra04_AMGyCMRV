/* File:   EcoCityMoto.h
 * Author: Alemol
 * Created on 28 de octubre de 2019, 11:38
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H


#include "Cliente.h"
#include "Moto.h"
#include <vector>
#include <map>


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
    
    
public:
    EcoCityMoto(const string &file1,const string &file2);
    EcoCityMoto(const EcoCityMoto& orig);
    
    
    unsigned GetIdUltimo() const;
    void SetIdUltimo(unsigned nuevoIdUltimo);
    
    Moto* LocMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);   
    
    Cliente& buscarCliente(string dni);
    map<string,Cliente>& getClientes();
    vector<Moto>& getMotos();
    
    virtual ~EcoCityMoto();
    
        
    
};

#endif /* ECOCITYMOTO_H */

