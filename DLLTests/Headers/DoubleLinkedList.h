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
    DLLNode<T>* head;  // Puntero al primer nodo
    DLLNode<T>* tail;  // Puntero al último nodo
    int length;        // Longitud de la lista

public:
    // Constructor
    ListaDobleEnlazada();

    // Destructor
    ~ListaDobleEnlazada();

    // Obtiene la longitud de la lista
    int getLength() const;

    // Obtiene el nodo de la cabeza de la lista
    DLLNode<T>* getHead() const;

    // Obtiene el nodo de la cola de la lista
    DLLNode<T>* getTail() const;

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
};
//Aqui termina el header sin templates







// Implementación de los métodos de la clase plantilla

template <typename T>
ListaDobleEnlazada<T>::ListaDobleEnlazada() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
ListaDobleEnlazada<T>::~ListaDobleEnlazada() {
    while (head) {
        DLLNode<T>* temp = head;
        head = head->getNext();
        delete temp;
    }
}

template <typename T>
int ListaDobleEnlazada<T>::getLength() const {
    return length;
}

template <typename T>
DLLNode<T>* ListaDobleEnlazada<T>::getHead() const {
    return head;
}

template <typename T>
DLLNode<T>* ListaDobleEnlazada<T>::getTail() const {
    return tail;
}

template <typename T>
void ListaDobleEnlazada<T>::headAppend(T valor) {
    DLLNode<T>* nuevoNodo = new DLLNode<T>(valor);
    if (!head) {
        head = tail = nuevoNodo;
    } else {
        nuevoNodo->setNext(head);
        head->setPrev(nuevoNodo);
        head = nuevoNodo;
    }
    length++;
}

template <typename T>
void ListaDobleEnlazada<T>::append(T valor) {
    DLLNode<T>* nuevoNodo = new DLLNode<T>(valor);
    if (!tail) {
        head = tail = nuevoNodo;
    } else {
        tail->setNext(nuevoNodo);
        nuevoNodo->setPrev(tail);
        tail = nuevoNodo;
    }
    length++;
}

template <typename T>
void ListaDobleEnlazada<T>::deleteNode(int posicion) {
    if (posicion < 0 || posicion >= length) {
        std::cerr << "Posición inválida." << std::endl;
        return;
    }

    DLLNode<T>* actual;
    int indice;

    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = actual->getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = actual->getPrev();
            indice--;
        }
    }

    if (actual) {
        if (actual == head) {
            head = head->getNext();
            if (head) {
                head->setPrev(nullptr);
            }
        } else if (actual == tail) {
            tail = tail->getPrev();
            if (tail) {
                tail->setNext(nullptr);
            }
        } else {
            actual->getPrev()->setNext(actual->getNext());
            actual->getNext()->setPrev(actual->getPrev());
        }
        delete actual;
        length--;
    } else {
        std::cerr << "Error al intentar eliminar en posición." << std::endl;
    }
}

template <typename T>
void ListaDobleEnlazada<T>::replace(int posicion, T nuevoValor) {
    if (posicion < 0 || posicion >= length) {
        std::cerr << "Posición inválida." << std::endl;
        return;
    }

    DLLNode<T>* actual;
    int indice;

    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = actual->getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = actual->getPrev();
            indice--;
        }
    }

    if (actual) {
        actual->setData(nuevoValor);
    } else {
        std::cerr << "Error al intentar reemplazar en posición." << std::endl;
    }
}

template <typename T>
void ListaDobleEnlazada<T>::printList() {
    DLLNode<T>* actual = head;
    while (actual) {
        std::cout << actual->getData() << " ";
        actual = actual->getNext();
    }
    std::cout << std::endl;
}

#endif // LISTADOBLEENLAZADA_H

