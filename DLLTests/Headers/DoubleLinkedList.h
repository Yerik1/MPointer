//
// Created by yerik on 8/31/24.
//

#ifndef LISTADOBLEENLAZADA_H
#define LISTADOBLEENLAZADA_H

#include <iostream>
#include "DLLNode.h"

template <typename T>
class ListaDobleEnlazada {
private:
    MPointer<DLLNode<T>> head= MPointer<DLLNode<T>>::New();  // Puntero al primer nodo
    MPointer<DLLNode<T>> tail= MPointer<DLLNode<T>>::New(); // Puntero al último nodo
    int length;        // Longitud de la lista

public:
    // Constructor
    ListaDobleEnlazada();

    // Destructor
    ~ListaDobleEnlazada();

    // Obtiene la longitud de la lista
    int getLength() const;

    // Obtiene el nodo de la cabeza de la lista
    MPointer<DLLNode<T>> getHead() const;

    // Obtiene el nodo de la cola de la lista
    MPointer<DLLNode<T>>getTail() const;

    // Agrega un nuevo nodo al inicio de la lista
    void headAppend(T valor);

    // Agrega un nuevo nodo al final de la lista
    void append(T valor);

    // Elimina un nodo en la posición especificada
    void deleteNode(int posicion);

    // Reemplaza el valor de un nodo en la posición especificada
    void replace(int posicion, T nuevoValor);

    // Imprime la lista
    void printList();

    T get(int posicion) const;

    bool isEmpty() const;
};

#include "../DoubleLinkedList.cpp"
#endif // LISTADOBLEENLAZADA_H

