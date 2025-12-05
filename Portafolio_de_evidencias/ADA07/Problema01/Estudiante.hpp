/**
 * @file Estudiante.hpp
 * @brief Define las estructuras usadas por la tabla hash de estudiantes.
 */

#ifndef ESTUDIANTE_HPP
#define ESTUDIANTE_HPP

#include <string>


/**
 * @enum Estado
 * @brief Representa el estado de un espacio dentro de la tabla hash.
 */
enum Estado {
    VACIO,      ///< Slot nunca utilizado.
    OCUPADO,    ///< Slot actualmente ocupado.
    ELIMINADO   ///< Slot utilizado previamente pero borrado.
};

/**
 * @struct Estudiante
 * @brief Contiene la información básica de un estudiante.
 */
struct Estudiante {
    int matricula;      ///< Matrícula única del estudiante.
    std::string nombre; ///< Nombre completo del estudiante.
    std::string carrera;///< Carrera o programa académico.
};

/**
 * @struct NodoHash
 * @brief Representa una entrada dentro de la tabla hash.
 */
struct NodoHash {
    int clave;              ///< Clave hash (matrícula).
    Estudiante estudiante;  ///< Datos del estudiante.
    Estado estado;          ///< Estado del nodo.
};

#endif // ESTUDIANTE_HPP
