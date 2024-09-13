//
// Created by yerik on 8/31/24.
//

#include "Headers/SortingAlgorithms.h"

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(MPointer<DLLNode<T>> a, MPointer<DLLNode<T>> b) {
    T temp = (a.getData())->getData();
    (a.getData())->setData((b.getData())->getData());
    (b.getData())->setData(temp);
}

// Algoritmo de QuickSort
template <typename T>
MPointer<DLLNode<T>> partition(MPointer<DLLNode<T>> bajo, MPointer<DLLNode<T>> alto) {
    T pivote = (alto.getData())->getData();
    MPointer<DLLNode<T>> i = (bajo.getData())->getPrev();

    for (MPointer<DLLNode<T>> j = bajo; !j.isSameAddress(alto); j = (j.getData())->getNext()) {
        if ((j.getData())->getData() <= pivote) {
            i = (!i.getHasValue()) ? bajo : (i.getData())->getNext();
            swap(i, j);
        }
    }
    i = (!i.getHasValue()) ? bajo : (i.getData())->getNext();
    swap(i, alto);
    return i;
}


template <typename T>
void quickSortRec(MPointer<DLLNode<T>> bajo, MPointer<DLLNode<T>> alto) {
    if (alto.getHasValue() && !bajo.isSameAddress(alto) && !bajo.isSameAddress((alto.getData())->getNext())) {
        MPointer<DLLNode<T>> p = partition(bajo, alto);
        quickSortRec(bajo, (p.getData())->getPrev());
        quickSortRec((p.getData())->getNext(), alto);
    }
}

template <typename T>
void quickSort(ListaDobleEnlazada<T>& lista) {
    quickSortRec(lista.getHead(), lista.getTail());
}

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(ListaDobleEnlazada<T>& lista) {
    if (!lista.getHead().getHasValue()) return;

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
    if (!lista.getHead()) return;

    MPointer<DLLNode<T>> actual = lista.getHead()->getNext();
    while (actual != nullptr) {
        T clave = actual->getData();
        MPointer<DLLNode<T>> anterior = actual->getPrev();

        while (anterior != nullptr && anterior->getData() > clave) {
            anterior->getNext()->setData(anterior->getData());
            anterior = anterior->getPrev();
        }
        if (anterior == nullptr) {
            lista.getHead()->setData(clave);
        } else {
            anterior->getNext()->setData(clave);
        }

        actual = actual->getNext();
    }
}
