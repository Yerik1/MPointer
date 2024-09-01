//
// Created by yerik on 8/31/24.
//
#include <iostream>
#include <thread>
#include <chrono>
#include "MPointer.h"


int main() {
    MPointerGC* garbagecollector = MPointerGC::GetInstance();

    // Prueba 1: Crear y asignar valores a MPointer<int>
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    garbagecollector->debug();  // Verificar estado después de la creación y asignación

    // Prueba 2: Crear otro MPointer<int> y asignar su valor
    MPointer<int> mp2 = MPointer<int>::New();
    *mp2 = 100;
    garbagecollector->debug();

    // Prueba 3: Copia de punteros y comprobación de referencias
    MPointer<int> mp3 = mp1;
    garbagecollector->debug();  // Debe mostrar que mp3 apunta a la misma dirección que mp1

    // Prueba 4: Reasignación de puntero
    mp3 = mp2;  // mp3 ahora debería apuntar a la misma dirección que mp2
    garbagecollector->debug();  // Verificar cambios en las referencias

    // Prueba 5: Manejo de punteros con diferentes tipos primitivos
    MPointer<double> mpD1 = MPointer<double>::New();
    *mpD1 = 3.1415;
    garbagecollector->debug();

    // Prueba 6: Desreferenciar y modificar valores
    *mp1 = 21;  // Cambiar valor al que apunta mp1
    *mp2 = 200;  // Cambiar valor al que apunta mp2
    *mpD1 = 2.718;
    garbagecollector->debug();  // Verificar cambios en valores


    // Prueba 8: Crear y eliminar múltiples punteros rápidamente
    for (int i = 0; i < 10; i++) {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = i * 10;
    }
    garbagecollector->debug();  // Verificar la correcta liberación de todos los punteros

    // Prueba 9: Reasignación en un bucle y eliminación de referencias anteriores
    MPointer<double> mpD2 = MPointer<double>::New();
    for (int i = 0; i < 5; i++) {
        *mpD2 = i * 0.5;
        garbagecollector->debug();
    }
    garbagecollector->debug();  // Verificar que solo queda una referencia

    // Simulación de tiempo de espera para verificar la salida de la consola
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    garbagecollector->debug();
    return 0;
}
