//
// Created by yerik on 8/31/24.
//
#include <iostream>
#include "Headers/DoubleLinkedList.h"
#include "Headers/SortingAlgorithms.h"
#include "../MPointerFiles/MPointerGC.h"

int main() {
    MPointerGC<int>::InitializeGC();
    ListaDobleEnlazada<int> lista;

    lista.headAppend(10);
    lista.headAppend(20);
    lista.append(30);
    lista.append(40);

    std::cout << "Lista: ";
    lista.printList();

    lista.replace(2, 25);
    std::cout << "Después de reemplazar en posición 2: ";
    lista.printList();

    lista.deleteNode(1);
    std::cout << "Después de eliminar en posición 1: ";
    lista.printList();

    lista.replace(1, 50);
    std::cout << "Después de reemplazar en posición 1: ";
    lista.printList();

    quickSort(lista);
    std::cout << "Lista después de QuickSort: ";
    lista.printList();

    MPointerGC<int>::FinalizeGC(); // Finaliza el GC
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Espera para ver los mensajes de GC
    return 0;
}