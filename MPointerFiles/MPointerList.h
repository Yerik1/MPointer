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
    void remove(int identifier);
    void print();
    int getSize();                      // Devuelve el número de nodos en la lista
    int getIDAt(int index);          // Devuelve el ID del nodo en el índice dado
    int getRefCount(int id);         // Devuelve el conteo de referencias para un nodo con un ID dado
};

// Añade un nuevo puntero a la lista
void LinkedList::newMpointer(int id, void* address, DataType type) {
    Node* newNode = new Node(id, address, 1, nullptr, type);  // Crea un nuevo nodo con una referencia
    if (head == nullptr) {
        head = newNode;  // Si la lista está vacía, el nuevo nodo es la cabeza
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;  // Avanza al final de la lista
        }
        current->next = newNode;  // El nuevo nodo se convierte en el último nodo
    }
}

// Aumenta el conteo de referencias de un nodo específico
void LinkedList::addRef(int identifier) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == identifier) {
            current->refCount++;
            return;
        }
        current = current->next;
    }
}

// Disminuye el conteo de referencias de un nodo específico
int LinkedList::substractRef(int identifier) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == identifier) {
            current->refCount--;
            return current->refCount;
        }
        current = current->next;
    }
    return -1;  // Retorna un valor no válido si no se encuentra
}

// Imprime la lista para depuración
void LinkedList::print() {
    cout << "-----------INICIO--LISTA-----------" << endl;
    Node* current = head;
    while (current != nullptr) {
        // Imprimir basado en el tipo
        switch (current->type) {
            case DataType::INT: {
                int* intPtr = static_cast<int*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *intPtr
                     << endl;
                break;
            }
            case DataType::DOUBLE: {
                double* doublePtr = static_cast<double*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *doublePtr
                     << endl;
                break;
            }
            case DataType::FLOAT: {
                float* floatPtr = static_cast<float*>(current->address);
                cout << "ID: " << current->id
                     << ", Direccion: " << current->address
                     << ", Referencias: " << current->refCount
                     << ", Valor: " << *floatPtr
                     << endl;
                break;
            }
        }
        current = current->next;
    }
    cout << "------------FIN--LISTA------------" << endl;
}

// Retorna el número de nodos en la lista
int LinkedList::getSize() {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Devuelve el ID del nodo en el índice dado
int LinkedList::getIDAt(int index) {
    Node* current = head;
    int count = 0;
    while (current != nullptr) {
        if (count == index) {
            return current->id;
        }
        count++;
        current = current->next;
    }
    return -1;  // Retorna -1 si el índice está fuera de rango
}

// Devuelve el conteo de referencias para un nodo con un ID dado
int LinkedList::getRefCount(int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current->refCount;
        }
        current = current->next;
    }
    return -1;  // Retorna -1 si el nodo no se encuentra
}

// Elimina un nodo de la lista basado en el identificador (ID)
void LinkedList::remove(int identifier) {
    Node* current = head;
    Node* previous = nullptr;

    // Encuentra el nodo a eliminar
    while (current != nullptr && current->id != identifier) {
        previous = current;
        current = current->next;
    }

    // Nodo no encontrado
    if (current == nullptr) return;

    // Nodo encontrado, actualizar punteros
    if (previous == nullptr) {  // Si es el primer nodo
        head = current->next;   // Mueve la cabeza al siguiente nodo
    } else {
        previous->next = current->next;  // Salta el nodo actual
    }

    delete current;  // Libera la memoria del nodo eliminado
}

#endif // MPOINTERLIST_H