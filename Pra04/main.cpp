/* 
 * File:   main.cpp
 * Author: Cayetano
 * Created on 11 de octubre de 2019, 11:16
 */

#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>

#include "VDinamico.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include "Vdinamico.h"
#include "AVL.h"
#include "Cliente.h"
#include "Moto.h"
#include "EcoCityMoto.h"
/*
void rutaMotoCliente(EcoCityMoto& eco,Cliente& nuestroCliente){
    	Moto *m=nuestroCliente.buscarMotoCercana();
        std::cout << "Moto mas cercana: " << m->getId() << " situada en: " <<
					m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;

        std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
        nuestroCliente.desbloquearMoto(m);        
        std::cout << "Desbloqueamos la Moto: " << m->getId() << std::endl;
		
        nuestroCliente.terminarTrayecto();
		
        std::cout << "Fin de la Ruta: " << nuestroCliente.UltimoItinerario().GetFecha().cadena() <<
					", Minutos: " << nuestroCliente.UltimoItinerario().GetMinutos() <<
					", Id: " << nuestroCliente.UltimoItinerario().GetVehiculo()->getId() <<
					", Pos Fin: " << nuestroCliente.UltimoItinerario().GetFin().GetLatitud() << "<--->" <<
					nuestroCliente.UltimoItinerario().GetFin().GetLongitud() << std::endl;
            
};

void encuentraCliente(EcoCityMoto& eco,std::string& dniCli){
    Cliente* nuestroCliente;
       
        nuestroCliente = eco.buscarCliente(dniCli);   //si no esta salta excepcion
        
        std::cout << "Cliente: " << nuestroCliente->GetDni() <<", "<<nuestroCliente->GetNombre() <<" Situado en: " << 
					nuestroCliente->getPosicion().GetLatitud() << "," <<
					nuestroCliente->getPosicion().GetLongitud() << std::endl;
        rutaMotoCliente(eco,*nuestroCliente);
        
};
*/

int main(){    
     
     setlocale(LC_ALL,"es_ES.UTF8"); 
     srand(time(0));
     try{ 
	 
		///Paso 1: creamos un AVL con los clientes y también un vector dinamico de motos
        EcoCityMoto eco("clientes_v2.csv","motos.txt");             
       
                /// Paso 2: Mostramos Arbol en inorden &
       //eco.getClientes().recorreInorden();     // ToDo: funciona (comentado para tardar menos)      
       std::cout << "--->Total de clientes del Arbol: " << eco.getClientes().size() << std::endl; // nos aseguramos
              
             /// Paso 3: Mostramos tamaño del arbol
       //std::cout << "--->Altura del Arbol: " << eco.getClientes().altura() << std::endl;       
             
          ///  Paso 4: buscamos un cliente,luego simulamos el uso de una moto 
        
       std::string dniNuestroCliente= "70409350R";
       //encuentraCliente(eco,dniNuestroCliente);
                            
     }catch (ErrorFechaIncorrecta &e){
            std::cerr << "Fecha Incorrecta: " << std::endl;
     }catch (std::runtime_error &e){ 
            std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
     }catch (std::bad_alloc &e){
            std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;     
     
     }catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
    }
       
    return 0;
    
}