/**
 * @file TablaSimbolos.cpp
 * @brief Implementación de la clase TablaSimbolos.
 */

#include "TablaSimbolos.hpp"

using namespace std;

int TablaSimbolos::hash(string clave) {
    int hashVal = 0;
    for (char c : clave) {
        hashVal = (hashVal * 31 + c) % TABLE_SIZE;
    }
    return hashVal;
}

TablaSimbolos::TablaSimbolos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabla[i] = nullptr;
    }
}

TablaSimbolos::~TablaSimbolos() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        NodoSimbolo* actual = tabla[i];
        while (actual != nullptr) {
            NodoSimbolo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
}

bool TablaSimbolos::agregarSimbolo(string clave, Atributos atributos) {
    int indice = hash(clave);
    NodoSimbolo* actual = tabla[indice];

    // Verificar duplicados
    while (actual != nullptr) {
        if (actual->clave == clave) {
            cout << "Error: Identificador ya existe" << endl;
            return false;
        }
        actual = actual->siguiente;
    }

    // Crear nuevo nodo
    NodoSimbolo* nuevoNodo = new NodoSimbolo;
    nuevoNodo->clave = clave;
    nuevoNodo->atributos = atributos;
    nuevoNodo->siguiente = tabla[indice];
    tabla[indice] = nuevoNodo;

    cout << "Símbolo agregado exitosamente" << endl;
    return true;
}

Atributos* TablaSimbolos::buscarSimbolo(string clave) {
    int indice = hash(clave);
    NodoSimbolo* actual = tabla[indice];

    while (actual != nullptr) {
        if (actual->clave == clave) {
            return &actual->atributos;
        }
        actual = actual->siguiente;
    }

    return nullptr;
}

bool TablaSimbolos::eliminarSimbolo(string clave) {
    int indice = hash(clave);
    NodoSimbolo* actual = tabla[indice];
    NodoSimbolo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (anterior == nullptr)
                tabla[indice] = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            delete actual;
            cout << "Símbolo eliminado exitosamente" << endl;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "Error: Símbolo no encontrado" << endl;
    return false;
}

void TablaSimbolos::mostrarTabla() {
    cout << "Contenido de la tabla de símbolos:" << endl;

    for (int i = 0; i < TABLE_SIZE; i++) {
        NodoSimbolo* actual = tabla[i];

        if (actual != nullptr) {
            cout << "Cubeta " << i << ": ";
            while (actual != nullptr) {
                cout << actual->clave << " -> ";
                actual = actual->siguiente;
            }
            cout << "NULL" << endl;
        }
    }
}
