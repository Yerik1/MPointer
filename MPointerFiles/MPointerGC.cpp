//
// Created by yerik on 8/18/24.
//

#include "Headers/MPointerGC.h"
#include <iostream>
#include <mutex>


// Inicialización de miembros estáticos
MPointerGC* MPointerGC::RECOLECTOR{nullptr};
std::mutex MPointerGC::mutexx;

// Constructor del recolector de basura
MPointerGC::MPointerGC() {
    // Iniciar el hilo del recolector de basura
    gcThread = std::thread(&MPointerGC::verifyReferences, this);
}

// Destructor del recolector de basura
MPointerGC::~MPointerGC() {
    stop();  // Detener el hilo del recolector de basura
    if (gcThread.joinable()) {
        gcThread.join();  // Unir el hilo para una finalización ordenada
    }
    debug();
}


// Método para obtener la instancia Singleton
MPointerGC* MPointerGC::GetInstance() {
    std::lock_guard<std::mutex> lock(mutexx);  // Asegurar acceso exclusivo
    if (RECOLECTOR == nullptr) {
        RECOLECTOR = new MPointerGC();
    }
    return RECOLECTOR;
}

// Método para registrar memoria y generar un ID
int MPointerGC::registerMPointer(void* address, DataType type) {
    this->autoid++;
    int iD = this->autoid;
    this->list.newMpointer(iD, address, type);
    return iD;
}

// Método para añadir una referencia a un puntero
void MPointerGC::addRef(int id) {
    list.addRef(id);
}

// Método para eliminar una referencia a un puntero
bool MPointerGC::deleteRef(int id) {
    int ref = list.substractRef(id);
    return (ref == 0);  // Devolver true si no hay más referencias
}

void MPointerGC::changeAddress(int id, void* address) {
    list.changeAddress(id, address);
}


// Método de depuración para imprimir información
void MPointerGC::debug() {
    list.print();
}

// Método para detener el hilo del GC
void MPointerGC::stop() {
    running = false;  // Detener el ciclo del hilo
}

// Método para verificar referencias y eliminar nodos sin referencias
void MPointerGC::verifyReferences() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Esperar medio segundo

        std::lock_guard<std::mutex> lock(mutexx);  // Sincronización

        // lógica para verificar y eliminar punteros sin referencias
        for (int i = 0; i < list.getSize(); ++i) {
            int id = list.getIDAt(i);
            if (list.getRefCount(id) <= 0) {
                list.remove(id);  // Eliminar el nodo del puntero sin referencias
                std::cout << "GC: Nodo con ID " << id << " eliminado por falta de referencias." << std::endl;
            }
        }
    }
}