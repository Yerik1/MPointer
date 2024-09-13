//
// Created by yerik on 8/16/24.
//
#include <iostream>
#include "Headers/DoubleLinkedList.h"
template <typename T>
ListaDobleEnlazada<T>::ListaDobleEnlazada() : length(0) {}

template <typename T>
ListaDobleEnlazada<T>::~ListaDobleEnlazada() {

    // Recorre la lista hasta que el tamaño sea 0
    while (length > 0) {

        // Guarda el nodo actual en un puntero temporal
        MPointer<DLLNode<T>> temp = head;

        // Mueve head al siguiente nodo
        head = (head.getData())->getNext();

        // Elimina el nodo actual y lo elimina del GC
        temp.deletePtr(true);

        // Decrementa el tamaño de la lista
        length--;
    }
    // Asegura que tail también sea nullptr al final
    tail = MPointer<DLLNode<T>>::New();
    MPointerGC* garbagecollector = MPointerGC::GetInstance();
    head.deletePtr(true);
    tail.deletePtr(true);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    garbagecollector->debug();
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
        (nuevoNodo.getData())->setNext(head);
        (head.getData())->setPrev(nuevoNodo);
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
        (tail.getData())->setNext(nuevoNodo);
        (nuevoNodo.getData())->setPrev(tail);
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
    if (length == 1 && posicion == 0) {
        head.deletePtr(true);  // Liberar head y tail
        head = MPointer<DLLNode<T>>::New();
        tail = MPointer<DLLNode<T>>::New();
        length--;
        return;
    }
    MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();
    int indice;

    if (posicion < length / 2) {
        actual = head;
        indice = 0;
        while (indice < posicion) {
            actual = (actual.getData())->getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (actual.getData())->getPrev();
            indice--;
        }
    }

    if (actual.getHasValue()) {
        if (actual.isSameAddress(head)) {
            head = (head.getData())->getNext();
            if (head.getHasValue()) {
                (head.getData())->setPrev(MPointer<DLLNode<T>>::New());
            }
        } else if (actual.isSameAddress(tail)) {
            tail = (tail.getData())->getPrev();
            if (tail.getHasValue()) {
                (tail.getData())->setNext(MPointer<DLLNode<T>>::New());
            }
        } else {
            MPointer<DLLNode<T>> temp = (actual.getData())->getPrev();
            (temp.getData())->setNext((actual.getData())->getNext());
            temp = (actual.getData())->getNext();
            (temp.getData())->setPrev((actual.getData())->getPrev());
        }

        actual.deletePtr(true);
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
            actual = (actual.getData())->getNext();
            indice++;
        }
    } else {
        actual = tail;
        indice = length - 1;
        while (indice > posicion) {
            actual = (actual.getData())->getPrev();
            indice--;
        }
    }

    if (actual.getHasValue()) {
        (actual.getData())->setData(nuevoValor);
    } else {
        std::cerr << "Error al intentar reemplazar en posición." << std::endl;
    }
}

template <typename T>
void ListaDobleEnlazada<T>::printList() {
    if(length>0) {
        MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();
        actual = head;
        while (!actual.isSameAddress((tail.getData())->getNext())) {
            std::cout << (actual.getData())->getData() << std::endl;
            actual = (actual.getData())->getNext();
        }
        std::cout << std::endl;
    }

}


