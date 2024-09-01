//
// Created by yerik on 8/31/24.
//
#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <iostream>
#include <mutex>
#include <thread>  // Incluye la librería para usar hilos
#include <chrono>
#include "MPointerList.h"  // Lista enlazada

class MPointerGC {
private:
    LinkedList list;
    static MPointerGC* RECOLECTOR;  // Puntero a la instancia Singleton
    static std::mutex mutexx;       // Mutex para la sincronización de acceso
    int autoid = 0;                 // ID autogenerado para los punteros
    std::thread gcThread;          // Hilo para la verificación de referencias
    bool running = true;

    // Constructor y destructor protegidos para asegurar el Singleton
    MPointerGC();
    ~MPointerGC();

    // Método para el ciclo del hilo de verificación
    void verifyReferences();

public:
    // Elimina los métodos de copia y asignación para asegurar el Singleton
    MPointerGC(MPointerGC& other) = delete;  // Evitar clonación
    void operator=(const MPointerGC&) = delete;  // Evitar asignación de copia

    // Métodos públicos
    static MPointerGC* GetInstance();    // Obtener la instancia singleton
    int registerMPointer(void* address, DataType type);   // Registrar un puntero y generar un ID
    void addRef(int id);                // Añadir una referencia
    bool deleteRef(int id);             // Eliminar una referencia
    void debug();                        // Función de depuración

    // Método para detener el hilo del GC
    void stop();
};
#include "MPointerGC.cpp"
#endif // MPOINTERGC_H
