#ifndef GRAFO_HPP
#define GRAFO_HPP
#include "vertice.cpp"
#include "arista.cpp"

class Graph{
private:
    Vertex *init;
    int length;
    int finalStates;
public:
    // constructor
    Graph(){init=nullptr; length=0; finalStates=0;}

    // operaciones
    int getLength(); // devuelve el numero de vertices en el grafo
    void insertVertex(std::string, bool);
    void insertEdge(std::string, std::string, std::string); // origen, destino ponderacion
    void showTransitionFunction() const; // muestra sus vertices, aristas y ponderacion
    void showStates() const;
    void deleteVertex(std::string);
    void deleteEdge(std::string, std::string); // origen - destino
    void destroyEdge(Edge*);
    void destroyVertex(Vertex*);

    bool save() const;
    bool load();

    std::string getName(Vertex*) const;
    Vertex *getVertex(std::string) const; // Retorna el vertice que tenga el nombre especificado

};

#endif // GRAFO_HPP
