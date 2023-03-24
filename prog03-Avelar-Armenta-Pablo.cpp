#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "grafo.cpp"

enum opcion{
    SALIR,
    INSERTAR_VERTICE, INSERTAR_ARISTA,
    ELIMINAR_VERTICE, ELIMINAR_ARISTA,
    MOSTRAR_TODO, MOSTRAR_VERTICE,
    GUARDAR, CARGAR
};

int main(){
    Graph *graph = new Graph();
    int opc, intIsFinal;
    bool isFinal;
    std::string name, origin, destination, word;

    do{
        system("cls");
        std::cout<<"Creador de Automatas Finitos (Grafo)"<<std::endl<<std::endl;
        std::cout<<INSERTAR_VERTICE<<") Agregar estado"<<std::endl;
        std::cout<<INSERTAR_ARISTA<<") Insertar Arista"<<std::endl;
        std::cout<<ELIMINAR_VERTICE<<") Eliminar estado"<<std::endl;
        std::cout<<ELIMINAR_ARISTA<<") Eliminar Arista"<<std::endl;
        std::cout<<MOSTRAR_TODO<<") Mostrar todo"<<std::endl;
        std::cout<<MOSTRAR_VERTICE<<") Mostrar estado"<<std::endl;
        std::cout<<GUARDAR<<") Guardar"<<std::endl;
        std::cout<<CARGAR<<") Cargar"<<std::endl;
        std::cout<<SALIR<<") Salir"<<std::endl;

        std::cin>>opc;
        fflush(stdin);

        switch(opc){
            case INSERTAR_VERTICE:
                std::cout<<"Identificador del estado: ";
                std::getline(std::cin, name);
                std::cout<<"Es estado final? (0/1): ";
                std::cin>>intIsFinal;
                if(intIsFinal == 0) isFinal = false;
                else isFinal = true;

                graph->insertVertex(name, isFinal);
            break;
            case INSERTAR_ARISTA:
                std::cout<<"Estado origen: ";
                std::getline(std::cin, origin);

                std::cout<<"Estado destino: ";
                std::getline(std::cin, destination);

                std::cout<<"Palabra: ";
                std::getline(std::cin, word);
                graph->insertEdge(origin, destination, word);
            break;
            case ELIMINAR_VERTICE:
                std::cout<<"Identificador del estado: ";
                std::getline(std::cin, name);
                graph->deleteVertex(name);
                system("pause");
             break;
            case ELIMINAR_ARISTA:
                std::cout<<"Estado origen: ";
                std::getline(std::cin, origin);

                std::cout<<"Estado destino: ";
                std::getline(std::cin, destination);

                graph->deleteEdge(origin, destination);
                system("pause");

            break;
            case MOSTRAR_TODO:
                system("cls");
                std::cout<<"Estados (S)"<<std::endl<<std::endl;
                graph->showStates();

                std::cout<<std::endl<<"Funcion de transicion (f)"<<std::endl<<std::endl;
                graph->showTransitionFunction();
                system("pause");
            break;
            case MOSTRAR_VERTICE:{
                system("cls");
                std::cout<<"Identificador: ";
                std::getline(std::cin, name);

                Vertex *state = graph->getVertex(name);
                if(!state){
                    std::cout<<"Error: estado no encontrado..."<<std::endl;
                    system("pause");
                    continue;
                }

                std::cout<<"Identificador: "<<graph->getName(state)<<std::endl;
                system("pause");
            }
            break;
            case GUARDAR:
                system("cls");
                if(graph->save()) std::cout<<"Se ha guardado el grafo satisfactoriamente..."<<std::endl;
                else std::cout<<"Error: no se pudo guardar el grafo."<<std::endl;
                system("pause");
            break;
            case CARGAR:
                system("cls");
                if(graph->load()) std::cout<<"Se ha cargado el grafo satisfactoriamente..."<<std::endl;
                system("pause");
            break;
            case SALIR:
                system("cls");
                std::cout<<"Presione cualquier tecla para cerrar el programa..."<<std::endl;
                system("pause");
            break;
        }

    }while(opc!=0);

    return 0;
}
