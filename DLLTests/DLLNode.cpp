//
// Created by yerik on 8/31/24.
//
#include "../MPointerFiles/MPointer.h"
template <typename T>
class DLLNode {
private:
    T data;
    DLLNode<T>* prev;
    DLLNode<T>* next;

public:
    DLLNode(T valor) : data(valor), prev(nullptr), next(nullptr) {}

    T getData() const {
        return data;
    }

    void setData(T valor) {
        data = valor;
    }

    DLLNode<T>* getPrev() const {
        return prev;
    }

    void setPrev(DLLNode<T>* nodo) {
        prev = nodo;
    }

    DLLNode<T>* getNext() const {
        return next;
    }

    void setNext(DLLNode<T>* nodo) {
        next = nodo;
    }
};
