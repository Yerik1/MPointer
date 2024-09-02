//
// Created by yerik on 8/16/24.
//
#include <iostream>
#include "Headers/DoubleLinkedList.h"
template <typename T>
ListaDobleEnlazada<T>::ListaDobleEnlazada() : length(0) {}

template <typename T>
ListaDobleEnlazada<T>::~ListaDobleEnlazada() {
    while (!head.getHasValue()) {
        MPointer<DLLNode<T>> temp = head;
        DLLNode<T> headNode=*head;
        head = headNode.getNext();
        temp.deletePtr(true);
    }
}

template <typename T>
int ListaDobleEnlazada<T>::getLength() const {
    return length;
}

template <typename T>
MPointer<DLLNode<T>> ListaDobleEnlazada<T>::getHead() const {
    return head;
}

template <typename T>
MPointer<DLLNode<T>> ListaDobleEnlazada<T>::getTail() const {
    return tail;
}

template <typename T>
void ListaDobleEnlazada<T>::headAppend(T valor) {
    MPointer<DLLNode<T>> nuevoNodo= MPointer<DLLNode<T>>::New();
    nuevoNodo = new DLLNode<T>(valor);
    if (!head.getHasValue()) {
        head = tail = nuevoNodo;
    } else {
        (*nuevoNodo).setNext(head);
        (*head).setPrev(nuevoNodo);
        head = nuevoNodo;
    }
    length++;
}

template <typename T>
void ListaDobleEnlazada<T>::append(T valor) {
    MPointer<DLLNode<T>> nuevoNodo= MPointer<DLLNode<T>>::New();
    nuevoNodo = new DLLNode<T>(valor);
    if (!tail.getHasValue()) {
        head = tail = nuevoNodo;
    } else {
        (*tail).setNext(nuevoNodo);
        (*nuevoNodo).setPrev(tail);
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

    MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();
    int indice;

    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = (*actual).getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (*actual).getPrev();
            indice--;
        }
    }

    if (actual.getHasValue()) {
        if (actual.isSameAddress(head)) {
            head = (*head).getNext();
            if (head.getHasValue()) {
                (*head).setPrev(MPointer<DLLNode<T>>::New());
            }
        } else if (actual.isSameAddress(tail)) {
            tail = (*tail).getPrev();
            if (tail.getHasValue()) {
                (*tail).setNext(MPointer<DLLNode<T>>::New());
            }
        } else {
            MPointer<DLLNode<T>> temp=(*actual).getPrev();
            (*temp).setNext((*actual).getNext());
            temp=(*actual).getNext();
            (*temp).setPrev((*actual).getPrev());

        }

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

    MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();
    int indice;

    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = (*actual).getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (*actual).getPrev();
            indice--;
        }
    }

    if (actual.getHasValue()) {
        (*actual).setData(nuevoValor);
    } else {
        std::cerr << "Error al intentar reemplazar en posición." << std::endl;
    }
}

template <typename T>
void ListaDobleEnlazada<T>::printList() {
    MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();
    actual = head;
    while (!actual.isSameAddress((*tail).getNext())) {
        std::cout << (*actual).getData() << std::endl;
        actual = (*actual).getNext();
    }
    std::cout << std::endl;
}



