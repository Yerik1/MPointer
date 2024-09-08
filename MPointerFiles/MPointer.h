//
// Created by yerik on 8/31/24.
//
#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

using namespace std;
template<typename T>
    DataType getType() {
    if (std::is_same_v<T, int>) return DataType::INT;
    if (std::is_same_v<T, double>) return DataType::DOUBLE;
    if (std::is_same_v<T, float>) return DataType::FLOAT;
    return DataType::UNKNOWN;  // Si el tipo no está definido
}
template <typename T>
class MPointer {
    //Se genera la instancia del GC
    MPointerGC* gC = MPointerGC::GetInstance();

private:
    bool hasValue = false;
    int ID;
    T* Mptr = nullptr;  // Se crea en nulo

    //Constructor
    MPointer(){
        //Mptr = new T();
        ID = gC->registerMPointer(Mptr, getType<T>()); // Asigna un id
    }
public:

    //Crea una copia del puntero existente
    MPointer(const MPointer & original){
        Mptr = (original.Mptr);
        ID = (original.ID); // Asignar el mismo ID para añadir una ref
        gC->addRef(ID);
    }

    // Destructor
    ~MPointer(){
        if (gC->deleteRef(ID)) {
            //delete ptr;
            Mptr = nullptr;
        }
    }

public:
    // Genera un nuevo Mpointer sin llamar al constructor directamente
    static MPointer<T> New()
    {
        MPointer<T> mp;
        //mp.gC->registerMPointer(mp.Mptr, getType<T>()); // Pasa el tipo correcto
        return mp;
    }


    // Sobrecarga de *
    T& operator*(){
        return *Mptr;
    }




    // Operador de asignación para el mismo tipo T
    template <typename U> //Tipo a comparar

    MPointer<T>& operator=(const U& valor) {
        //se compara que el tipo de U sea el mismo del MPointer
        //static_assert(std::is_same_v<T, U>, "Tipos incompatibles");
        hasValue = true;
        *Mptr = valor;
        return *this;
    }

    // Operador de asignación para puntero a tipo T
    MPointer<T>& operator=(T* ptr) {
        if (Mptr != ptr) {
            hasValue = true;
            if (Mptr) {
                bool dtonant = gC->deleteRef(ID);
                deletePtr(dtonant);
            }
            Mptr = ptr;
        }
        return *this;
    }

    // Operador de asignación para otro Mpointer<T>
    MPointer<T>& operator=(const MPointer<T>& puntero) {
        if (this != &puntero) {
            hasValue = true;
            Mptr = (puntero.Mptr); //Hace una copia
            gC->addRef(puntero.ID);
            bool dtonant = gC->deleteRef(ID);
            //deletePtr(dtonant);
            ID = puntero.ID;
        }
        return *this;
    }

    // Destruye el puntero en caso que ya no tenga referencias
    void deletePtr(bool dtonant) {
        if (dtonant == true) {
            delete Mptr;
            Mptr = nullptr;
        }
    }

    bool getHasValue() const{
        return hasValue;
    }

    // Método para verificar si dos MPointer apuntan a la misma dirección
    bool isSameAddress(const MPointer<T>& other) const {
        return this->Mptr == other.Mptr;
    }

    T* getData() {
        return this->Mptr;
    }
};
#endif // MPOINTER_H