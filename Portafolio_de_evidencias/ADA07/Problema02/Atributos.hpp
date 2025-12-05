/**
 * @file Atributos.hpp
 * @brief Define la estructura Atributos usada por la tabla de símbolos.
 */

#ifndef ATRIBUTOS_HPP
#define ATRIBUTOS_HPP

#include <string>

/**
 * @struct Atributos
 * @brief Representa la información asociada a un símbolo en un compilador.
 *
 * Contiene datos importantes sobre cada identificador como:
 * - tipo de dato
 * - valor asignado
 * - ámbito al que pertenece
 */
struct Atributos {
    std::string tipo;   ///< Tipo del símbolo (int, float, string, etc.)
    std::string valor;  ///< Valor del símbolo.
    std::string ambito; ///< Ámbito al que pertenece: global, local, función, etc.
};

/**
 * @struct NodoSimbolo
 * @brief Nodo usado en las listas enlazadas de cada cubeta de la tabla hash.
 *
 * Cada nodo representa un símbolo con su clave y atributos.
 */
struct NodoSimbolo {
    std::string clave;      ///< Nombre del identificador.
    Atributos atributos;    ///< Atributos asociados al identificador.
    NodoSimbolo* siguiente; ///< Puntero al siguiente nodo (listas enlazadas).
};

#endif // ATRIBUTOS_HPP