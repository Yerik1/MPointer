cmake_minimum_required(VERSION 3.10)
project(MPointer)

# Especifica la versión de C++
set(CMAKE_CXX_STANDARD 17)

# Añade tu archivo fuente
add_executable(MPointer DLLTests/Gtest.cpp)

# Busca Google Test (esto necesita que Google Test esté instalado en tu sistema)
find_package(GTest REQUIRED)

# Incluye los directorios de cabeceras de GTest
include_directories(${GTEST_INCLUDE_DIRS})

# Enlaza las bibliotecas de GTest y pthread (hilos)
target_link_libraries(MPointer ${GTEST_LIBRARIES} pthread)