//
// Created by yerik on 8/31/24.
//
#include "MPointerList.h"

// Añade un nuevo puntero a la lista
void LinkedList::newMpointer(int id, void* address) {
    Node* newNode = new Node(id, address, 1);  // Crea un nuevo nodo con una referencia
    newNode->next = head;  // El nuevo nodo apunta al primer nodo actual
    head = newNode;  // El nuevo nodo se convierte en el primer nodo
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
    // Manejo de error si el nodo no se encuentra (opcional)
}

// Disminuye el conteo de referencias de un nodo específico
int LinkedList::deleteRef(int identifier) {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == identifier) {
            current->refCount--;
            return current->refCount;
        }
        current = current->next;
    }
    // Manejo de error si el nodo no se encuentra (opcional)
    return -1;  // Retorna un valor no válido si no se encuentra
}

// Elimina un puntero de la lista (no utilizado en tu código actual)
void LinkedList::deleteMpointer(int identifier) {
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
    if (previous == nullptr) {  // Si es el primero
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;  // Libera memoria
}

// Imprime la lista para depuración
void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id
             << ", Address: " << current->address
             << ", RefCount: " << current->refCount
             << endl;
        current = current->next;
    }
}
