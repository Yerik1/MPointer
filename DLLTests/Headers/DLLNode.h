//
// Created by yerik on 8/31/24.
//

#ifndef DLLNODE_H
#define DLLNODE_H
#include "../../MPointerFiles/MPointer.cpp"
template <typename T>
class DLLNode {
private:
    T data;
    DLLNode<T>* prev;
    DLLNode<T>* next;

public:
    // Constructor
    DLLNode(T valor) : data(valor), prev(nullptr), next(nullptr) {}

    // Métodos para obtener y establecer el dato
    T getData() const;
    void setData(T valor);

    // Métodos para obtener y establecer el nodo anterior
    DLLNode<T>* getPrev() const;
    void setPrev(DLLNode<T>* nodo);

    // Métodos para obtener y establecer el nodo siguiente
    DLLNode<T>* getNext() const;
    void setNext(DLLNode<T>* nodo);
};

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
DLLNode<T>* DLLNode<T>::getPrev() const {
    return prev;
}

template <typename T>
void DLLNode<T>::setPrev(DLLNode<T>* nodo) {
    prev = nodo;
}

template <typename T>
DLLNode<T>* DLLNode<T>::getNext() const {
    return next;
}

template <typename T>
void DLLNode<T>::setNext(DLLNode<T>* nodo) {
    next = nodo;
}

#endif
