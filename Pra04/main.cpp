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
        //0)creamos estructura y se cargan clientes y motos dentro
        cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;   
        //EcoCityMoto eco("clientes_v2.csv","motos.txt"); 
        //EcoCityMoto eco("clientes_v5.csv","motos2.txt"); 
        EcoCityMoto eco("prueba.txt","motos2.txt");  
    
        //1) Añadir a la empresa un nuevo cliente que no exista previamente
        Cliente cliente("50617459W", "Pepito Hernandez" , "passph", "Universidad", 37.5, 3.5, &eco);
        
        //2) Localizar el cliente anterior en la empresa por su DNI y buscar una moto cercana
        if (!eco.nuevoCliente(cliente))
            throw invalid_argument("Cliente NO insertado: el cliente ya existe");
        
        Cliente *cliente1=eco.buscarCliente(cliente.GetDni());
             std::cout << "Cliente: " << cliente1->GetDni() << " Situado en: " << 
                    cliente1->getPosicion().GetLatitud() << "," <<
                    cliente1->getPosicion().GetLongitud() << std::endl;
             Moto *m=cliente1->buscarMotoCercana();
             std::cout << "Moto mas cercana: " << m->getId() << " situada en: " <<
                   m->getPosicion().GetLatitud() << "," << m->getPosicion().GetLongitud() << std::endl;

        //3) Realizar un itinerario con la moto localizada
             std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
             cliente1->desbloquearMoto(m);
             
             std::cout << "Desbloqueamos la Moto: " << m->getId() << std::endl;
             cliente1->terminarTrayecto();
             std::cout << "Fin de la Ruta: " << cliente1->UltimoItinerario().GetFecha().cadena() <<
                     ", Minutos: " << cliente1->UltimoItinerario().GetMinutos() <<
                     ", Id: " << cliente1->UltimoItinerario().GetVehiculo()->getId() <<
                     ", Pos Fin: " << cliente1->UltimoItinerario().GetFin().GetLatitud() << "<-->" <<
                     cliente1->UltimoItinerario().GetFin().GetLongitud() << std::endl;

             
             //4) Localizar las motos sin batería e indicar si la moto utilizada está en esa situación.
             vector<Moto> v=eco.localizaMotosSinBateria();             
             vector<Moto>::iterator itMoto=v.begin();
             while (itMoto!=v.end()){
                 if ((itMoto)->getId()==m->getId()){
                     cout << "la moto Utilizada quedo sin bateria"<<endl;
                     break;
                 }
                 itMoto++;
             }
         
             //5) Borrar el cliente que se insertó en el punto 1 
            if (eco.eliminarCliente(cliente.GetDni()))
                 cout << "Borrando cliente: " << cliente.GetDni() << endl;            
            Cliente* cliente2=eco.buscarCliente(cliente.GetDni()); //comprobación
            
    
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
