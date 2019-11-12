#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Cliente.h"
#include "Moto.h"
#include "EcoCityMoto.h"

int main(){    
    
     setlocale(LC_ALL,"es_ES.UTF8"); 
     srand(time(0));
     try{ 
        // 1)creamos estructura y se cargan clientes y motos dentro
        cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;   
        EcoCityMoto eco("clientes_v2.csv","motos.txt");  
    
          // 5) buscamos un cliente, una moto, la utiliza y la deja
        Cliente cliente("52525252X", "yo" , "clave", "miDireccion", 37.5, 3.5, &eco);  //ojo no es puntero
        if (!eco.nuevoCliente(cliente))
            throw invalid_argument("Cliente NO insertado: el cliente ya existe");
        
        Cliente &clienteRef=eco.buscarCliente(cliente.GetDni());
             std::cout << "Cliente: " << clienteRef.GetDni() << " Situado en: " << 
                    clienteRef.getPosicion().GetLatitud() << "," <<
                    clienteRef.getPosicion().GetLongitud() << std::endl;
             Moto *m=clienteRef.buscarMotoCercana();
             std::cout << "Moto mas cercana: " << m->getId() << " situada en: " <<
                     m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;

             std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
             clienteRef.desbloquearMoto(m);
             
             std::cout << "Desbloqueamos la Moto: " << m->getId() << std::endl;
             clienteRef.terminarTrayecto();
             std::cout << "Fin de la Ruta: " << clienteRef.UltimoItinerario().GetFecha().cadena() <<
                     ", Minutos: " << clienteRef.UltimoItinerario().GetMinutos() <<
                     ", Id: " << clienteRef.UltimoItinerario().GetVehiculo()->getId() <<
                     ", Pos Fin: " << clienteRef.UltimoItinerario().GetFin().GetLatitud() << "<-->" <<
                     clienteRef.UltimoItinerario().GetFin().GetLongitud() << std::endl;

             vector<Moto> vecMoto=eco.localizaMotosSinBateria();   
             vector<Moto>::iterator itMoto=vecMoto.begin();
             while(itMoto!=vecMoto.end()){
                 if((*(itMoto)).getId()==m->getId())
                     cout<<"La moto quedo sin Bateria"<<endl;
                 itMoto++;
             }
             
             
             //vector<Moto>::iterator itMoto=find(v.begin(),v.end(),m->getId());
             if (itMoto!=vecMoto.end())
                 cout << "la moto Utilizada quedo sin bateria";  
        //ahora al acceder si se modificó el cliente ya que se hizo con referencias     
        cliente=eco.buscarCliente(cliente.GetDni());  //pruebas
            if (eco.eliminarCliente(cliente.GetDni()))
                cout << "Borrando cliente: " << cliente.GetDni() << endl;
            //saltará excepcion en caso de que no este 
            //asi verificamos que fue borrado
            cliente=eco.buscarCliente(cliente.GetDni());
    
        
     //Tratamiento de errores
     }catch (ErrorFechaIncorrecta &e){
            std::cerr << "Fecha Incorrecta: " << std::endl;
     }catch (std::runtime_error &e){ //std::ifstream::failure &e){
            std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
     }catch (std::bad_alloc &e){
            std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;     
     }catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
     } 
     
     
    return 0;
    
}
