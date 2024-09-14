//
// Created by yerik on 9/13/24.
//
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "Headers/SortingAlgorithms.h"

// Prueba 1: Crear y asignar valores a MPointer<int>
TEST(MPointerTest, CreateAndAssignInt) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    EXPECT_EQ(*mp1, 42);
}

// Prueba 2: Crear otro MPointer<int> y asignar su valor
TEST(MPointerTest, CreateAnotherAndAssignValue) {
    MPointer<int> mp2 = MPointer<int>::New();
    *mp2 = 100;
    EXPECT_EQ(*mp2, 100);
}

// Prueba 3: Copia de punteros y comprobación de referencias
TEST(MPointerTest, CopyPointerAndCheckReferences) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    MPointer<int> mp3 = mp1;
    EXPECT_EQ(*mp3, 42);  // Debería tener el mismo valor que mp1
}

// Prueba 4: Reasignación de puntero
TEST(MPointerTest, ReassignPointer) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    MPointer<int> mp2 = MPointer<int>::New();
    *mp2 = 100;
    MPointer<int> mp3 = mp1;
    mp3 = mp2;
    EXPECT_EQ(*mp3, 100);  // mp3 ahora debería tener el valor de mp2
    EXPECT_EQ(*mp2, 100);  // Confirmación adicional
}

// Prueba 5: Manejo de punteros con diferentes tipos primitivos
TEST(MPointerTest, HandleDifferentPrimitiveTypes) {
    MPointer<double> mpD1 = MPointer<double>::New();
    *mpD1 = 3.1415;
    EXPECT_DOUBLE_EQ(*mpD1, 3.1415);
}

// Prueba 6: Desreferenciar y modificar valores
TEST(MPointerTest, DereferenceAndModifyValues) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    MPointer<int> mp2 = MPointer<int>::New();
    *mp2 = 100;
    *mp1 = 21;
    *mp2 = 200;
    EXPECT_EQ(*mp1, 21);
    EXPECT_EQ(*mp2, 200);
}

// Prueba 7: Modificar valores en diferentes tipos primitivos
TEST(MPointerTest, ModifyDifferentPrimitiveTypes) {
    MPointer<double> mpD1 = MPointer<double>::New();
    *mpD1 = 3.1415;
    *mpD1 = 2.718;
    EXPECT_DOUBLE_EQ(*mpD1, 2.718);
}

// Prueba 8: Crear y eliminar múltiples punteros rápidamente
TEST(MPointerTest, CreateAndDeleteMultiplePointers) {
    for (int i = 0; i < 10; i++) {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = i * 10;
        EXPECT_EQ(*tempPtr, i * 10);
    }
    // No hay una expectativa de memoria aquí ya que se gestionará automáticamente
}

// Prueba 9: Reasignación en un bucle y eliminación de referencias anteriores
TEST(MPointerTest, ReassignInLoopAndDeleteOldReferences) {
    MPointer<double> mpD2 = MPointer<double>::New();
    for (int i = 0; i < 5; i++) {
        *mpD2 = i * 0.5;
        EXPECT_DOUBLE_EQ(*mpD2, i * 0.5);
    }
}

TEST(ListaDobleEnlazadaTest, HeadAppend) {
    ListaDobleEnlazada<int> lista;
    lista.headAppend(10);
    lista.headAppend(20);
    EXPECT_EQ(lista.get(0), 20);  // El 20 debería estar al inicio
    EXPECT_EQ(lista.get(1), 10);  // El 10 debería estar en la segunda posición
}

// Prueba 2: append para agregar al final
TEST(ListaDobleEnlazadaTest, Append) {
    ListaDobleEnlazada<int> lista;
    lista.append(30);
    lista.append(40);
    EXPECT_EQ(lista.get(0), 30);  // El 30 debería estar al inicio
    EXPECT_EQ(lista.get(1), 40);  // El 40 debería estar al final
}

// Prueba 3: replace para reemplazar un valor
TEST(ListaDobleEnlazadaTest, Replace) {
    ListaDobleEnlazada<int> lista;
    lista.append(10);
    lista.append(20);
    lista.append(30);
    lista.replace(1, 25);  // Reemplaza el segundo elemento (índice 1) con 25
    EXPECT_EQ(lista.get(1), 25);
}

// Prueba 4: deleteNode para eliminar un nodo
TEST(ListaDobleEnlazadaTest, DeleteNode) {
    ListaDobleEnlazada<int> lista;
    lista.append(10);
    lista.append(20);
    lista.append(30);
    lista.deleteNode(1);  // Elimina el nodo en la posición 1 (debería eliminar 20)
    EXPECT_EQ(lista.get(0), 10);
    EXPECT_EQ(lista.get(1), 30);  // El segundo nodo debería ser ahora 30
}

// Prueba 5: Ordenar la lista con bubbleSort
TEST(ListaDobleEnlazadaTest, BubbleSort) {
    ListaDobleEnlazada<int> lista;
    lista.append(40);
    lista.append(10);
    lista.append(30);
    lista.append(20);
    bubbleSort(lista);  // Debería ordenar la lista
    EXPECT_EQ(lista.get(0), 10);
    EXPECT_EQ(lista.get(1), 20);
    EXPECT_EQ(lista.get(2), 30);
    EXPECT_EQ(lista.get(3), 40);
}

// Prueba 6: Eliminar múltiples nodos
TEST(ListaDobleEnlazadaTest, DeleteMultipleNodes) {
    ListaDobleEnlazada<int> lista;
    lista.append(10);
    lista.append(20);
    lista.append(30);
    lista.deleteNode(0);  // Elimina el primer nodo
    lista.deleteNode(0);  // Elimina el primer nodo restante
    lista.deleteNode(0);  // Elimina el primer nodo restante
    EXPECT_TRUE(lista.isEmpty());  // La lista debería estar vacía
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}