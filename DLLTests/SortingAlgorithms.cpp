//
// Created by yerik on 8/31/24.
//

#include "Headers/SortingAlgorithms.h"

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(MPointer<DLLNode<T>> a, MPointer<DLLNode<T>> b) {
    T temp = (a.getData())->getData();  // Corrección aquí
    (a.getData())->setData((b.getData())->getData());  // Corrección aquí
    (b.getData())->setData(temp);  // Corrección aquí
}

// Algoritmo de QuickSort
template <typename T>
MPointer<DLLNode<T>> partition(MPointer<DLLNode<T>> bajo, MPointer<DLLNode<T>> alto) {
    T pivote = (alto.getData())->getData();  // Corrección aquí
    MPointer<DLLNode<T>> i = (bajo.getData())->getPrev();  // Corrección aquí

    for (MPointer<DLLNode<T>> j = bajo; !j.isSameAddress(alto); j = (j.getData())->getNext()) {  // Corrección aquí
        if ((j.getData())->getData() <= pivote) {  // Corrección aquí
            i = (!i.getHasValue()) ? bajo : (i.getData())->getNext();  // Corrección aquí
            swap(i, j);  // Corrección aquí
        }
    }
    i = (!i.getHasValue()) ? bajo : (i.getData())->getNext();  // Corrección aquí
    swap(i, alto);  // Corrección aquí
    return i;
}


template <typename T>
void quickSortRec(MPointer<DLLNode<T>> bajo, MPointer<DLLNode<T>> alto) {
    if (alto.getHasValue() && !bajo.isSameAddress(alto) && !bajo.isSameAddress((alto.getData())->getNext())) {  // Corrección aquí
        MPointer<DLLNode<T>> p = partition(bajo, alto);  // Corrección aquí
        quickSortRec(bajo, (p.getData())->getPrev());  // Corrección aquí
        quickSortRec((p.getData())->getNext(), alto);  // Corrección aquí
    }
}

template <typename T>
void quickSort(ListaDobleEnlazada<T>& lista) {
    quickSortRec(lista.getHead(), lista.getTail());  // Corrección aquí
}

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(ListaDobleEnlazada<T>& lista) {
    if (!lista.getHead().getHasValue()) return;  // Corrección aquí

    bool swapped;
    MPointer<DLLNode<T>> actual = MPointer<DLLNode<T>>::New();

    do {
        swapped = false;
        actual = lista.getHead();

        while (actual.getData()->getNext().getHasValue()) {
            if (actual.getData()->getData() > actual.getData()->getNext().getData()->getData()) {
                swap(actual, actual.getData()->getNext());
                swapped = true;
            }
            actual = actual.getData()->getNext();
        }
    } while (swapped);
}

// Algoritmo de Insertion Sort
template <typename T>
void insertionSort(ListaDobleEnlazada<T>& lista) {
    if (!lista.getHead()) return;  // Corrección aquí

    MPointer<DLLNode<T>> actual = lista.getHead()->getNext();  // Corrección aquí
    while (actual != nullptr) {
        T clave = actual->getData();  // Corrección aquí
        MPointer<DLLNode<T>> anterior = actual->getPrev();  // Corrección aquí

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
