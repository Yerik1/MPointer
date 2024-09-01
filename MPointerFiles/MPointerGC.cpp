//
// Created by yerik on 8/18/24.
//

#include "MPointerGC.h"
#include <iostream>
#include <mutex>

// Inicialización de miembros estáticos
MPointerGC* MPointerGC::pinstance_{nullptr};
std::mutex MPointerGC::mutexx;

// Método para obtener la instancia Singleton
MPointerGC* MPointerGC::GetInstance() {
    std::lock_guard<std::mutex> lock(mutexx);  // Asegurar acceso exclusivo
    if (pinstance_ == nullptr) {
        pinstance_ = new MPointerGC();
    }
    return pinstance_;
}

// Método para registrar memoria y generar un ID
int MPointerGC::registerMemory(void* address) {
    this->autoid++;
    int iD = this->autoid;
    this->list.newMpointer(iD, address);  // Supone que newMpointer es correcto en LinkedList
    return iD;
}

// Método para añadir una referencia a un puntero
void MPointerGC::add_ref(int id) {
    list.addRef(id);  // Supone que addRef es correcto en LinkedList
}

// Método para eliminar una referencia a un puntero
bool MPointerGC::delete_ref(int id) {
    int ref = list.deleteRef(id);  // Supone que deleteRef es correcto en LinkedList
    return (ref == 0);  // Devolver true si no hay más referencias
}

// Método de depuración para imprimir información
void MPointerGC::debug() {
    list.print();  // Supone que print es correcto en LinkedList
}