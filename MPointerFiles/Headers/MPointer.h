// MPointer.h
#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"
#include <type_traits> // Necesario para std::is_same_v

using namespace std;

// Plantilla para determinar el tipo de datos
template<typename T>
DataType getType() {
    if (std::is_same_v<T, int>) return DataType::INT;
    if (std::is_same_v<T, double>) return DataType::DOUBLE;
    if (std::is_same_v<T, float>) return DataType::FLOAT;
    return DataType::UNKNOWN;  // Si el tipo no está definido
}

template <typename T>
class MPointer {
    // Se genera la instancia del GC
    MPointerGC* gC = MPointerGC::GetInstance();

private:
    bool hasValue = false;
    int ID;
    T* Mptr = nullptr;  // Se crea en nulo

    // Constructor
    MPointer();

public:
    // Crea una copia del puntero existente
    MPointer(const MPointer & original);

    // Destructor
    ~MPointer();

    // Genera un nuevo Mpointer sin llamar al constructor directamente
    static MPointer<T> New();

    // Sobrecarga de *
    T& operator*();

    // Operador de asignación para el mismo tipo T
    template <typename U>
    MPointer<T>& operator=(const U& valor);

    // Operador de asignación para puntero a tipo T
    MPointer<T>& operator=(T* ptr);

    // Operador de asignación para otro Mpointer<T>
    MPointer<T>& operator=(const MPointer<T>& puntero);

    // Destruye el puntero en caso que ya no tenga referencias
    void deletePtr(bool dtonant);

    // Retorna si el puntero esta apuntando a algo
    bool getHasValue() const;

    // Método para verificar si dos MPointer apuntan a la misma dirección
    bool isSameAddress(const MPointer<T>& other) const;

    // Retorna a lo que este apuntando el puntero
    T* getData();
};

#include "../MPointer.cpp" // Incluye las implementaciones en un archivo .tpp

#endif // MPOINTER_H
