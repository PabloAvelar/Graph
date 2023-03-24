#include "vertice.hpp"

// getters
Vertex* Vertex::getNext() const{
    return this->next;
}

Edge* Vertex::getEdge() const{
    return this->edge;
}

std::string Vertex::getName() const{
    return this->name;
}

bool Vertex::getIsFinal(){
    return this->isFinal;
}

// setters
void Vertex::setNext(Vertex* vertex){
    this->next = vertex;
}

void Vertex::setEdge(Edge* edge){
    this->edge = edge;
}

void Vertex::setName(std::string name){
    this->name = name;
}

void Vertex::setIsFinal(bool isFinal){
    this->isFinal = isFinal;
}