#include "Headers/MPointer.h"


template <typename T>
MPointer<T>::MPointer() {
    ID = gC->registerMPointer(Mptr, getType<T>()); // Asigna un id
}

template <typename T>
MPointer<T>::MPointer(const MPointer & original) {
    Mptr = (original.Mptr);
    ID = (original.ID); // Asignar el mismo ID para añadir una ref
    gC->addRef(ID);
}

template <typename T>
MPointer<T>::~MPointer() {
    if (gC->deleteRef(ID)) {
        //delete Mptr;
        Mptr = nullptr;
    }
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    return mp;
}

template <typename T>
T& MPointer<T>::operator*() {
    return *Mptr;
}

template <typename T>
template <typename U>
MPointer<T>& MPointer<T>::operator=(const U& valor) {
    hasValue = true;
    *Mptr = valor;
    return *this;
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(T* ptr) {
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

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& puntero) {
    if (this != &puntero) {
        hasValue = true;
        Mptr = (puntero.Mptr); // Hace una copia
        gC->addRef(puntero.ID);
        bool dtonant = gC->deleteRef(ID);
        ID = puntero.ID;
    }
    return *this;
}

template <typename T>
void MPointer<T>::deletePtr(bool dtonant) {
    if (dtonant) {
        delete Mptr;
        Mptr = nullptr;
    }
}

template <typename T>
bool MPointer<T>::getHasValue() const {
    return hasValue;
}

template <typename T>
bool MPointer<T>::isSameAddress(const MPointer<T>& other) const {
    return this->Mptr == other.Mptr;
}

template <typename T>
T* MPointer<T>::getData() {
    return this->Mptr;
}

