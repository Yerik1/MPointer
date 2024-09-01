//
// Created by yerik on 8/31/24.
//

#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "DLLNode.h"
#include "DoubleLinkedList.h"

// Función para intercambiar manualmente los datos de dos nodos
template <typename T>
void swap(DLLNode<T>* a, DLLNode<T>* b);

// Algoritmo de QuickSort
template <typename T>
DLLNode<T>* partition(DLLNode<T>* bajo, DLLNode<T>* alto);

template <typename T>
void quickSortRec(DLLNode<T>* bajo, DLLNode<T>* alto);

template <typename T>
void quickSort(ListaDobleEnlazada<T>& lista);

// Algoritmo de Bubble Sort
template <typename T>
void bubbleSort(ListaDobleEnlazada<T>& lista);

// Algoritmo de Insertion Sort
template <typename T>
void insertionSort(ListaDobleEnlazada<T>& lista);

#include "../SortingAlgorithms.cpp"
#endif // SORTING_ALGORITHMS_H

