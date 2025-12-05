/**
 * @file TablaHashEstudiantes.hpp
 * @brief Declaración de la clase TablaHashEstudiantes.
 */

#ifndef TABLAHASHESTUDIANTES_HPP
#define TABLAHASHESTUDIANTES_HPP

#include <iostream>
#include <string>
#include "Estudiante.hpp"

#define TABLE_SIZE 1009

/**
 * @class TablaHashEstudiantes
 * @brief Implementa una tabla hash con sondeo lineal para almacenar estudiantes.
 *
 * Cada estudiante se almacena usando su matrícula como clave primaria.
 * Las colisiones se resuelven usando sondeo lineal.
 */
class TablaHashEstudiantes {
private:
    NodoHash* tabla;    ///< Arreglo dinámico de nodos hash.
    int tableSize;      ///< Tamaño actual de la tabla hash.

    /**
     * @brief Función hash simple basada en módulo.
     * @param clave Matrícula del estudiante.
     * @return Índice dentro de la tabla hash.
     */
    int hash(int clave);

public:
    /**
     * @brief Constructor de la tabla hash.
     * @param size Tamaño inicial de la tabla (por defecto TABLE_SIZE).
     */
    TablaHashEstudiantes(int size = TABLE_SIZE);
    
    /**
     * @brief Destructor que libera memoria.
     */
    ~TablaHashEstudiantes();

    /**
     * @brief Inserta un estudiante en la tabla.
     * @param matricula Matrícula única.
     * @param nombre Nombre del estudiante.
     * @param carrera Carrera académica.
     * @return true si el estudiante fue agregado.
     * @return false si la matrícula ya existe o la tabla está llena.
     */
    bool agregarEstudiante(int matricula, std::string nombre, std::string carrera);
    
    /**
     * @brief Busca un estudiante por matrícula.
     * @param matricula Identificador a buscar.
     * @return Puntero al estudiante si se encuentra; nullptr si no.
     */
    Estudiante* buscarEstudiante(int matricula);
    
    /**
     * @brief Elimina lógicamente un estudiante.
     * @param matricula Matrícula a eliminar.
     * @return true si se eliminó correctamente.
     * @return false si no se encontró.
     */
    bool eliminarEstudiante(int matricula);
    
    /**
     * @brief Muestra en consola todos los estudiantes almacenados.
     */
    void mostrarTabla();
};

#endif // TABLAHASHESTUDIANTES_HPP