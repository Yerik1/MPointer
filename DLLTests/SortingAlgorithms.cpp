//
// Created by yerik on 8/31/24.
//

#include "Headers/DLLNode.h"
#include "Headers/DoubleLinkedList.h"

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(DLLNode<T>* a, DLLNode<T>* b) {
    T temp = a->getData();  // Corrección aquí
    a->setData(b->getData());  // Corrección aquí
    b->setData(temp);  // Corrección aquí
}

// Algoritmo de QuickSort
template <typename T>
DLLNode<T>* partition(DLLNode<T>* bajo, DLLNode<T>* alto) {
    T pivote = alto->getData();  // Corrección aquí
    DLLNode<T>* i = bajo->getPrev();  // Corrección aquí

    for (DLLNode<T>* j = bajo; j != alto; j = j->getNext()) {  // Corrección aquí
        if (j->getData() <= pivote) {  // Corrección aquí
            i = (i == nullptr) ? bajo : i->getNext();  // Corrección aquí
            swap(i, j);  // Corrección aquí
        }
    }
    i = (i == nullptr) ? bajo : i->getNext();  // Corrección aquí
    swap(i, alto);  // Corrección aquí
    return i;
}


template <typename T>
void quickSortRec(DLLNode<T>* bajo, DLLNode<T>* alto) {
    if (alto != nullptr && bajo != alto && bajo != alto->getNext()) {  // Corrección aquí
        DLLNode<T>* p = partition(bajo, alto);  // Corrección aquí
        quickSortRec(bajo, p->getPrev());  // Corrección aquí
        quickSortRec(p->getNext(), alto);  // Corrección aquí
    }
}

template <typename T>
void quickSort(ListaDobleEnlazada<T>& lista) {
    quickSortRec(lista.getHead(), lista.getTail());  // Corrección aquí
}

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(ListaDobleEnlazada<T>& lista) {
    if (!lista.getHead()) return;  // Corrección aquí

    bool swapped;
    DLLNode<T>* actual;

    do {
        swapped = false;
        actual = lista.getHead();  // Corrección aquí

        while (actual->getNext() != nullptr) {  // Corrección aquí
            if (actual->getData() > actual->getNext()->getData()) {  // Corrección aquí
                std::swap(actual->getData(), actual->getNext()->getData());  // Corrección aquí
                swapped = true;
            }
            actual = actual->getNext();  // Corrección aquí
        }
    } while (swapped);
}

// Algoritmo de Insertion Sort
template <typename T>
void insertionSort(ListaDobleEnlazada<T>& lista) {
    if (!lista.getHead()) return;  // Corrección aquí

    DLLNode<T>* actual = lista.getHead()->getNext();  // Corrección aquí
    while (actual != nullptr) {
        T clave = actual->getData();  // Corrección aquí
        DLLNode<T>* anterior = actual->getPrev();  // Corrección aquí

        while (anterior != nullptr && anterior->getData() > clave) {  // Corrección aquí
            anterior->getNext()->setData(anterior->getData());  // Corrección aquí
            anterior = anterior->getPrev();  // Corrección aquí
        }
        if (anterior == nullptr) {
            lista.getHead()->setData(clave);  // Corrección aquí
        } else {
            anterior->getNext()->setData(clave);  // Corrección aquí
        }

        actual = actual->getNext();  // Corrección aquí
    }
}
