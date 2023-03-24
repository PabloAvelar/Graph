#ifndef VERTICE_HPP
#define VERTICE_HPP
#include <iostream>
#include "arista.hpp"

// Prototipo que evita la paradoja del include
class Edge;

class Vertex{
private:
    std::string name;
    Vertex* next;
    Edge* edge;
    bool isFinal;
    //friend class Graph; // Para acceder a sus atributos privados

public:
    // constructores
    Vertex(){
        this->name="";
        this->next=nullptr;
        this->edge=nullptr;
        this->isFinal = false;
        }
    Vertex(std::string nombre, Vertex* next, Edge* edge, bool isFinal){
        this->name=nombre;
        this->next=next;
        this->edge=edge;
        this->isFinal = isFinal;
    }

    // getters
    Vertex* getNext() const;
    Edge* getEdge() const;
    std::string getName() const;
    bool getIsFinal();

    // setters
    void setNext(Vertex*);
    void setEdge(Edge*);
    void setName(std::string);
    void setIsFinal(bool);
};

#endif // VERTICE_HPP
