//
// Created by yerik on 8/31/24.
//
#include "Headers/DLLNode.h"

// Definiciones de las funciones miembro deben estar también en el .h

template <typename T>
T DLLNode<T>::getData() const {
    return data;
}

template <typename T>
void DLLNode<T>::setData(T valor) {
    data = valor;
}

template <typename T>
MPointer<DLLNode<T>> DLLNode<T>::getPrev() const {
    return prev;
}

template <typename T>
void DLLNode<T>::setPrev(MPointer<DLLNode<T>> nodo) {
    prev = nodo;
}

template <typename T>
MPointer<DLLNode<T>> DLLNode<T>::getNext() const {
    return next;
}

template <typename T>
void DLLNode<T>::setNext(MPointer<DLLNode<T>> nodo) {
    next = nodo;
}