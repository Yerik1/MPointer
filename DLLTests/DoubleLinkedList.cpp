//
// Created by yerik on 8/16/24.
//
#include <iostream>
#include "Headers/DLLNode.h"

template <typename T>
class ListaDobleEnlazada {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int length;

public:
    ListaDobleEnlazada() : head(nullptr), tail(nullptr), length(0) {}

    ~ListaDobleEnlazada() {
        while (head) {
            DLLNode<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    int getLength() const {
        return length;
    }

    DLLNode<T>* getHead() const {
        return head;
    }

    DLLNode<T>* getTail() const {
        return tail;
    }

    void headAppend(T valor) {
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

    void append(T valor) {
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

    void deleteNode(int posicion) {
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

    void replace(int posicion, T nuevoValor) {
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

    void printList() {
        DLLNode<T>* actual = head;
        while (actual) {
            std::cout << actual->getData() << " ";
            actual = actual->getNext();
        }
        std::cout << std::endl;
    }
};


