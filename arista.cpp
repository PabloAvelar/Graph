#include "arista.hpp"
#include <string>

// getters

Vertex* Edge::getDestination() const{
    return this->destination;
}

Edge* Edge::getNext() const{
    return this->next;
}

std::string Edge::getWord() const{
    return this->word;
}

// setters

void Edge::setDestination(Vertex* dest){
    this->destination = dest;
}

void Edge::setNext(Edge* edge){
    this->next = edge;
}

void Edge::setWord(const std::string word){
    this->word = word;
}
