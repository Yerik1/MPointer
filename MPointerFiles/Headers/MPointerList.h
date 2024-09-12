//
// Created by yerik on 8/31/24.
//
#ifndef MPOINTERLIST_H
#define MPOINTERLIST_H
#include <iostream>
using namespace std;

// Enum para el tipo de datos
enum class DataType {
    INT,
    DOUBLE,
    FLOAT,
    UNKNOWN
};

// Node, tiene todos los datos que necesita
struct Node {
    int id;
    void* address = nullptr;
    int refCount = 0;
    Node* next = nullptr;
    DataType type;  // Para guardar el tipo de datos

    //Constructor del Nodo
    Node(int id = 0, void* address = nullptr, int refCount = 0, Node* next = nullptr, DataType type = DataType::INT) : id(id), address(address), refCount(refCount), next(next), type(type) {}
};

// Lista enlazada
class LinkedList {
private:
    Node* head;  // Puntero al primer nodo de la lista
    int size;

public:
    // Constructor de la lista
    LinkedList() : head(nullptr) {}

    // Destructor de la lista
    ~LinkedList() = default;

    void newMpointer(int id, void* address, DataType type);
    void addRef(int identifier);
    int substractRef(int identifier);
    void changeAddress(int identifier, void* address);
    void remove(int identifier);
    void print();
    int getSize();                      // Devuelve el número de nodos en la lista
    int getIDAt(int index);          // Devuelve el ID del nodo en el índice dado
    int getRefCount(int id);         // Devuelve el conteo de referencias para un nodo con un ID dado
};
#include "../MPointerList.cpp"
#endif // MPOINTERLIST_H