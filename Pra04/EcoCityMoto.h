/* File:   EcoCityMoto.h
 * Author: Alemol
 * Created on 28 de octubre de 2019, 11:38
 */
// Borra esto luego
#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H


#include "VDinamico.h"
#include "Cliente.h"
#include "Moto.h"
#include "AVL.h"

using namespace std;

class EcoCityMoto {
private:
    unsigned idUltimo;
    VDinamico<Moto> motos;
    AVL<Cliente> clientes;
    
    //---FUNCIONES----------//
    void cargarMotos(string fileNameMotos);
    void cargarClientes(string fileNameClientes);

    
    
    
public:
    EcoCityMoto(const string &file1,const string &file2);
    EcoCityMoto(const EcoCityMoto& orig);
    
    
    unsigned GetIdUltimo() const;
    void SetIdUltimo(unsigned nuevoIdUltimo);
    
    Moto* LocMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);   
    
    Cliente buscarCliente(string dni);
    AVL<Cliente>& getClientes();
    VDinamico<Moto>& getMotos();
    
    virtual ~EcoCityMoto();
    
        
    
};

#endif /* ECOCITYMOTO_H */

