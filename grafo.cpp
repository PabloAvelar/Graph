#include "grafo.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int Graph::getLength(){
    return length;
}

std::string Graph::getName(Vertex* vertex) const{
    return vertex->getName();
}

// Vertices

Vertex* Graph::getVertex(std::string name) const{
    Vertex *aux = init;
    bool flag = true;
    while(aux && flag){
        if(aux->getName() == name) flag = false;
        else aux = aux->getNext();
    }

    return aux;
}

void Graph::insertVertex(std::string name, bool isFinal){
    Vertex *vertex = new Vertex(name, nullptr, nullptr, isFinal);
    Vertex *auxVertex = init;

    // Si el grafo esta vacio
    if(!auxVertex) init=vertex;
    else{
        while(auxVertex->getNext()) auxVertex = auxVertex->getNext();
        auxVertex->setNext(vertex);
    }

    length++;
}

void Graph::destroyVertex(Vertex* vertex){
    // Destruimos cada arista de su lista
    Edge* edge = vertex->getEdge();
    while(edge){
        deleteEdge(vertex->getName(), edge->getDestination()->getName());
        edge = edge->getNext();
    }

    // Destruimos el vértice
    vertex->setNext(nullptr);
    delete vertex;
    vertex = nullptr;
}

void Graph::deleteVertex(std::string name){
    Vertex* vertex = init;
    Vertex* auxVertex = nullptr;
    bool flag = true;

    if(!vertex){    // Si el grafo esta vacio
        std::cout<<"Error: el grafo esta vacio."<<std::endl;
        return;
    }

    // Primero se eliminan TODAS las aristas que conectan al vértice a eliminar
        // Pasa por todos y cada uno de los vértices de la lista del grafo.

    while(vertex){
        deleteEdge(vertex->getName(), name);
        vertex = vertex->getNext();
    }

    // Ahora se elimina el vértice de la lista del grafo.

    // Caso 1: eliminacion de la primera posicion

    vertex = init; // Reciclamos este puntero para empezar de nuevo.
    if(vertex->getName() == name){
        auxVertex = vertex;
        init = vertex->getNext();
        destroyVertex(auxVertex);
    }else{  // Caso 2: eliminacion en cualquier posicion menos al inicio
        while(vertex->getNext() && flag){
            if(vertex->getNext()->getName() == name) flag = false;
            else vertex = vertex->getNext();
        }
        auxVertex = vertex->getNext();
        vertex->setNext(vertex->getNext()->getNext());
        destroyVertex(auxVertex);
    }

    length--;

}

// Aristas

void Graph::destroyEdge(Edge* edge){
    edge->setDestination(nullptr);
    edge->setNext(nullptr);
    delete edge;
    edge = nullptr;
}

void Graph::insertEdge(std::string origin, std::string destination, std::string word){
    Vertex* vertexOrigin = init;
    Edge* edgeAux = nullptr;

    //Busqueda del vertice origen
    if(vertexOrigin){
       vertexOrigin = getVertex(origin);

       // Comprobando que existe el origen
       if(!vertexOrigin) std::cout<<"Error: no existe el origen."<<std::endl;
       else{
        // Buscando el destino
        Vertex* destinationVertex = getVertex(destination);
        //std::cout<<"Destino: "<<destinationVertex->name<<std::endl;
        if(!destinationVertex) std::cout<<"Error: no existe el destino"<<std::endl;
        else{
            Edge* edge = new Edge(destinationVertex, nullptr, word);

            edgeAux = vertexOrigin->getEdge();

            // Comprobando si existe o no una arista en ese vertice origen
            if(!edgeAux) vertexOrigin->setEdge(edge);
            else{
                // Buscando el final de la lista del nodo
                while(edgeAux->getNext()) edgeAux = edgeAux->getNext();

                edgeAux->setNext(edge);
            }

        }
       }

    }
}

void Graph::deleteEdge(std::string origin, std::string destination){
    // Obtenemos el vertice origen
    Vertex* originVertex = getVertex(origin);

    // Verificamos que existe el vértice origen
    if(!originVertex){
        std::cout<<"Error: no se encontro el vertice"<<std::endl;
        return;
    }

    Edge* edge = originVertex->getEdge();
    Edge* auxEdge = nullptr;
    bool flag=true;

    // Si el vértice origen tiene a la arista a eliminar
    if(edge){
        // Caso 1: eliminación de la primera posición
            // Para saber cuántas aristas hay en un grafo: E = V - 1
        if(edge->getDestination()->getName() == destination){
            auxEdge = edge;
            originVertex->setEdge(edge->getNext());
            destroyEdge(auxEdge);
        }
        // Caso 2: eliminación en cualquier otra posición
        else{
            while(edge->getNext() && flag){
                if(edge->getNext()->getDestination()->getName() == destination) flag = false;
                else edge = edge->getNext();
            }
            auxEdge = edge->getNext();
            // Si se encontró el destino de la arista a eliminar...
            if(auxEdge){
                edge->setNext(edge->getNext()->getNext());
                destroyEdge(auxEdge);
            }
        }

    }
}

void Graph::showStates() const{
    Vertex* vertex = init;
    size_t finalStatesLength=0;

    std::cout<<"S = {";
    while(vertex){
        std::cout<<vertex->getName();
        if(vertex->getNext()) std::cout<<", ";
        if(vertex->getIsFinal()) finalStatesLength++;
        vertex = vertex->getNext();
    }
    std::cout<<"}"<<std::endl<<std::endl;

    // Estado inicial (el primer vertice agregado)
    if(init){
        std::cout<<"Estado inicial (S0)"<<std::endl;
        std::cout<<"S0 = {"<<init->getName()<<"}"<<std::endl<<std::endl;
    }

    // Estados de aceptación
    vertex = init; // reutilizando la variable vertex
    std::cout<<"Estados de aceptacion (A)"<<std::endl;
    std::cout<<"A = {";
    while(vertex){
        if(vertex->getIsFinal()){
            std::cout<<vertex->getName();
            if(vertex->getNext()) std::cout<<", ";
        }
        vertex = vertex->getNext();
    }
    std::cout<<"}"<<std::endl;
    
}

void Graph::showTransitionFunction() const{
    Vertex* auxVertex = init;
    Edge* auxEdge = nullptr;

    while(auxVertex){
        auxEdge = auxVertex->getEdge();
        while(auxEdge){
            std::cout<<"f("
                     <<auxVertex->getName()
                     <<", "
                     <<auxEdge->getWord()
                     <<") = "
                     <<auxEdge->getDestination()->getName()
                     <<std::endl;
            auxEdge = auxEdge->getNext();
        }
        std::cout<<std::endl;
        auxVertex = auxVertex->getNext();
    }

}

bool Graph::save() const{
    // Se guardarán dos archivos, uno de vertices y otro de aristas
    Vertex* vertex = init;
    if(!vertex) return false;

    std::ofstream fileV("file01_vertices.txt", std::ios::out); // Constructor
    std::ofstream fileE("file01_edges.txt", std::ios::out); // Constructor

    if(fileV.fail()) return false;
    if(fileE.fail()) return false;

    while(vertex){
        Edge* edge = vertex->getEdge();
        // Guardando los vértices
        fileV << vertex->getName() << "|"
              << vertex->getIsFinal() << "|"
              << "*";
        // Guardando las aristas (aqui sí pido el origen porque se ese dato se te pide en el menu)
        while(edge){
            fileE << vertex->getName() << "|"
                  << edge->getDestination()->getName() << "|"
                  << edge->getWord() << "|"
                  << "*";
            edge = edge->getNext();
        }
        vertex = vertex->getNext();
    }

    return true;

}



bool Graph::load(){
    // Primero se insertan los vértices y luego las aristas.
    
    int length;
    std::ifstream fileV;
    std::ifstream fileE;
    fileV.open("file01_vertices.txt", std::ios::in); // Constructor
    fileE.open("file01_edges.txt", std::ios::in); // Constructor
    std::string myregister;

    if(fileV.fail()) return false;
    if(fileE.fail()) return false;

    
    // Creación del buffer de vértices

    // Obteniendo la longitud del archivo para el buffer
    fileV.seekg(0, fileV.end);
    length = fileV.tellg();
    fileV.seekg(0, fileV.beg); // Regresa al inicio del archivo
    char *bufferV = new char[length];
    fileV.read(bufferV, length);

    // Creación del buffer de aristas

    // Obteniendo la longitud del archivo para el buffer
    fileE.seekg(0, fileE.end);
    length = fileE.tellg();
    fileE.seekg(0, fileE.beg); // Regresa al inicio del archivo
    char *bufferE = new char[length];
    fileE.read(bufferE, length);

    std::string vFields[2];
    std::string eFields[3];

    // Se convierte el buffer en formato de flujo de cadena
    std::stringstream stringV(bufferV);
    std::stringstream stringE(bufferE);

    // Cargando los vértices

    int i = 0;
    while(std::getline(stringV, myregister, '*') && !stringV.eof()){
            try{
                std::stringstream stringReg(myregister);
                i=0;
                while(std::getline(stringReg, vFields[i], '|')) i++;

                insertVertex(vFields[0], stoi(vFields[1]));
            }catch(...){

            }
    }

    // Cargando las aristas

    while(std::getline(stringE, myregister, '*') && !stringE.eof()){
            try{
                std::stringstream stringReg(myregister);
                i=0;
                while(std::getline(stringReg, eFields[i], '|')) i++;

                insertEdge(eFields[0], eFields[1], eFields[2]);
            }catch(...){

            }
    }

    return true;
}