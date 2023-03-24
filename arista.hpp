#ifndef ARISTA_HPP
#define ARISTA_HPP
#include <string>

// Prototipo que evita la paradoja del include
class Vertex;

class Edge{
private:
    Vertex *destination;
    Edge *next;
    std::string word;

    //friend class Graph; // Para acceder a sus atributos privados

public:
    // constructores
    Edge(){
        destination=nullptr;
        next=nullptr;
        word="";
    }
    Edge(Vertex* destination, Edge* next, std::string word){
        //std::cout<<"Destino: "<<_destination<<std::endl;
        this->destination=destination;
        this->next=next;
        this->word=word;
    }

    // getters
    Vertex* getDestination() const;
    Edge* getNext() const;
    std::string getWord() const;

    // setters
    void setDestination(Vertex*);
    void setNext(Edge*);
    void setWord(const std::string);
};


#endif // ARISTA_HPP
