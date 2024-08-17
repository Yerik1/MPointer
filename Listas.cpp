//
// Created by yerik on 8/16/24.
//
#include <iostream>

template <typename T>
class Node {
private:
    T data;
    Node<T>* prev;
    Node<T>* next;

public:
    Node(T valor) : data(valor), prev(nullptr), next(nullptr) {}

    T getData() const {
        return data;
    }

    void setData(T valor) {
        data = valor;
    }

    Node<T>* getPrev() const {
        return prev;
    }

    void setPrev(Node<T>* nodo) {
        prev = nodo;
    }

    Node<T>* getNext() const {
        return next;
    }

    void setNext(Node<T>* nodo) {
        next = nodo;
    }
};

template <typename T>
class ListaDobleEnlazada {
private:
    Node<T>* head;
    Node<T>* tail;
    int length;

public:
    ListaDobleEnlazada() : head(nullptr), tail(nullptr), length(0) {}

    ~ListaDobleEnlazada() {
        while (head) {
            Node<T>* temp = head;
            head = head->getNext();  // Corrección aquí
            delete temp;
        }
    }

    int getLength() const {
        return length;
    }

    Node<T>* getHead() const {
        return head;
    }

    Node<T>* getTail() const {
        return tail;
    }

    void headAppend(T valor) {
        Node<T>* nuevoNodo = new Node<T>(valor);
        if (!head) {
            head = tail = nuevoNodo;
        } else {
            nuevoNodo->setNext(head);  // Corrección aquí
            head->setPrev(nuevoNodo);  // Corrección aquí
            head = nuevoNodo;
        }
        length++;
    }

    void append(T valor) {
        Node<T>* nuevoNodo = new Node<T>(valor);
        if (!tail) {
            head = tail = nuevoNodo;
        } else {
            tail->setNext(nuevoNodo);  // Corrección aquí
            nuevoNodo->setPrev(tail);  // Corrección aquí
            tail = nuevoNodo;
        }
        length++;
    }

    void deleteNode(int posicion) {
        if (posicion < 0 || posicion >= length) {
            std::cerr << "Posición inválida." << std::endl;
            return;
        }

        Node<T>* actual;
        int indice;

        if (posicion < length / 2) {
            actual = head;
            indice = 0;
            while (indice < posicion) {
                actual = actual->getNext();  // Corrección aquí
                indice++;
            }
        } else {
            actual = tail;
            indice = length - 1;
            while (indice > posicion) {
                actual = actual->getPrev();  // Corrección aquí
                indice--;
            }
        }

        if (actual) {
            if (actual == head) {
                head = head->getNext();  // Corrección aquí
                if (head) {
                    head->setPrev(nullptr);  // Corrección aquí
                }
            } else if (actual == tail) {
                tail = tail->getPrev();  // Corrección aquí
                if (tail) {
                    tail->setNext(nullptr);  // Corrección aquí
                }
            } else {
                actual->getPrev()->setNext(actual->getNext());  // Corrección aquí
                actual->getNext()->setPrev(actual->getPrev());  // Corrección aquí
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

        Node<T>* actual;
        int indice;

        if (posicion < length / 2) {
            actual = head;
            indice = 0;
            while (indice < posicion) {
                actual = actual->getNext();  // Corrección aquí
                indice++;
            }
        } else {
            actual = tail;
            indice = length - 1;
            while (indice > posicion) {
                actual = actual->getPrev();  // Corrección aquí
                indice--;
            }
        }

        if (actual) {
            actual->setData(nuevoValor);  // Corrección aquí
        } else {
            std::cerr << "Error al intentar reemplazar en posición." << std::endl;
        }
    }

    void printList() {
        Node<T>* actual = head;
        while (actual) {
            std::cout << actual->getData() << " ";  // Corrección aquí
            actual = actual->getNext();  // Corrección aquí
        }
        std::cout << std::endl;
    }
};

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(Node<T>* a, Node<T>* b) {
    T temp = a->getData();  // Corrección aquí
    a->setData(b->getData());  // Corrección aquí
    b->setData(temp);  // Corrección aquí
}

// Algoritmo de QuickSort
template <typename T>
Node<T>* partition(Node<T>* bajo, Node<T>* alto) {
    T pivote = alto->getData();  // Corrección aquí
    Node<T>* i = bajo->getPrev();  // Corrección aquí

    for (Node<T>* j = bajo; j != alto; j = j->getNext()) {  // Corrección aquí
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
void quickSortRec(Node<T>* bajo, Node<T>* alto) {
    if (alto != nullptr && bajo != alto && bajo != alto->getNext()) {  // Corrección aquí
        Node<T>* p = partition(bajo, alto);  // Corrección aquí
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
    Node<T>* actual;

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

    Node<T>* actual = lista.getHead()->getNext();  // Corrección aquí
    while (actual != nullptr) {
        T clave = actual->getData();  // Corrección aquí
        Node<T>* anterior = actual->getPrev();  // Corrección aquí

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

int main() {
    ListaDobleEnlazada<int> lista;

    lista.headAppend(10);
    lista.headAppend(20);
    lista.append(30);
    lista.append(40);

    std::cout << "Lista: ";
    lista.printList();  // Corrección aquí

    lista.replace(2, 25);
    std::cout << "Después de reemplazar en posición 2: ";
    lista.printList();  // Corrección aquí

    lista.deleteNode(1);
    std::cout << "Después de eliminar en posición 1: ";
    lista.printList();  // Corrección aquí

    lista.replace(1, 50);
    std::cout << "Después de reemplazar en posición 1: ";
    lista.printList();  // Corrección aquí

    quickSort(lista);
    std::cout << "Lista después de QuickSort: ";
    lista.printList();  // Corrección aquí

    return 0;
}
