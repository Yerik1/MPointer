//
// Created by yerik on 8/31/24.
//

#ifndef DLLNODE_H
#define DLLNODE_H
#include "../../MPointerFiles/MPointer.h"
template <typename T>
class DLLNode {
private:
    T data;
    MPointer<DLLNode> prev;
    MPointer<DLLNode> next;

public:
    // Constructor
    DLLNode(T valor) : data(valor), prev(MPointer<DLLNode<T>>::New()), next(MPointer<DLLNode<T>>::New()) {}

    // Métodos para obtener y establecer el dato
    T getData() const;
    void setData(T valor);

    // Métodos para obtener y establecer el nodo anterior
    MPointer<DLLNode> getPrev() const;
    void setPrev(MPointer<DLLNode> nodo);

    // Métodos para obtener y establecer el nodo siguiente
    MPointer<DLLNode> getNext() const;
    void setNext(MPointer<DLLNode> nodo);
};
#include "../DLLNode.cpp"
#endif
