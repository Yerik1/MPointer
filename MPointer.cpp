#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
class MPointer {
    T* ptr;
    int* refCount; // Contador de referencias

    // Constructor privado para evitar instanciación directa
    MPointer() : ptr(nullptr), refCount(nullptr) {}

public:
    // Destructor
    ~MPointer() {
        if (refCount && --(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    // Método estático para crear un nuevo MPointer
    static MPointer<T> New() {
        static_assert(std::is_arithmetic<T>::value || std::is_same<T, char>::value, "MPointer only supports primitive types.");
        MPointer<T> mp;
        mp.ptr = new T();
        mp.refCount = new int(1); // Inicializar contador de referencias
        return mp;
    }

    // Operador de desreferencia
    T& operator*() {
        return *ptr;
    }

    // Operador de acceso a miembros
    T* operator->() {
        return ptr;
    }

    // Sobrecarga del operador &
    T operator&() {
        return *ptr;
    }

    // Sobrecarga del operador =
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            // Reducir la referencia actual
            if (refCount && --(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }

            // Asignar la dirección de memoria y el contador de otras instancias
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    // Sobrecarga del operador = para tipos primitivos
    MPointer<T>& operator=(const T& value) {
        if (ptr == nullptr) {
            ptr = new T();
            refCount = new int(1); // Inicializar contador de referencias
        }
        *ptr = value;
        return *this;
    }

    // Prohibir la copia para evitar problemas de doble liberación
    MPointer(const MPointer&) = delete;

    // Permitimos el movimiento
    MPointer(MPointer&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    MPointer& operator=(MPointer&& other) noexcept {
        if (this != &other) {
            if (refCount && --(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }
};

int main() {
    MPointer<int> myPtr = MPointer<int>::New();
    MPointer<int> myPtr2 = MPointer<int>::New();

    *myPtr = 5;
    myPtr2 = myPtr;  // Ahora myPtr2 apunta a la misma dirección que myPtr

    std::cout << *myPtr2 << std::endl;  // Debería imprimir 5

    myPtr2 = 10;  // Equivalente a *myPtr2 = 10
    std::cout << *myPtr << std::endl;  // Debería imprimir 10

    return 0;
}