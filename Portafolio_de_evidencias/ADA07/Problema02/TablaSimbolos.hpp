/**
 * @file TablaSimbolos.hpp
 * @brief Declaración de la clase TablaSimbolos y estructuras auxiliares.
 */

#ifndef TABLASIMBOLOS_HPP
#define TABLASIMBOLOS_HPP

#include <iostream>
#include <string>
#include "Atributos.hpp"

#define TABLE_SIZE 100

/**
 * @class TablaSimbolos
 * @brief Implementa una tabla hash con listas enlazadas para almacenar símbolos.
 */
class TablaSimbolos {
private:
    NodoSimbolo* tabla[TABLE_SIZE]; ///< Arreglo principal de bucket.

    /**
     * @brief Función hash basada en multiplicación polinómica.
     * @param clave Identificador al que se le obtiene un índice.
     * @return Índice dentro del rango de la tabla.
     */
    int hash(std::string clave);

public:

    /**
     * @brief Constructor: inicializa las buckets en nullptr.
     */
    TablaSimbolos();

    /**
     * @brief Destructor: libera toda la memoria de los nodos.
     */
    ~TablaSimbolos();

    /**
     * @brief Agrega un símbolo a la tabla.
     * @param clave Nombre del símbolo.
     * @param atributos Información asociada.
     * @return true si fue agregado correctamente, false si ya existía.
     */
    bool agregarSimbolo(std::string clave, Atributos atributos);

    /**
     * @brief Busca un símbolo en la tabla.
     * @param clave Identificador buscado.
     * @return Puntero a los Atributos si existe, nullptr si no.
     */
    Atributos* buscarSimbolo(std::string clave);
    
    /**
     * @brief Elimina un símbolo de la tabla.
     * @param clave Identificador a eliminar.
     * @return true si fue eliminado, false si no existe.
     */
    bool eliminarSimbolo(std::string clave);
    
    /**
     * @brief Muestra en consola todos los símbolos almacenados.
     */
    void mostrarTabla();
};

#endif // TABLASIMBOLOS_HPP