/**
 * @file TablaHashEstudiantes.cpp
 * @brief Implementación de la clase TablaHashEstudiantes.
 */

#include "TablaHashEstudiantes.hpp"

using namespace std;

int TablaHashEstudiantes::hash(int clave) {
    return clave % tableSize;
}

TablaHashEstudiantes::TablaHashEstudiantes(int size) {
    tableSize = size;
    tabla = new NodoHash[tableSize];
    for (int i = 0; i < tableSize; i++) {
        tabla[i].estado = VACIO;
    }
}

TablaHashEstudiantes::~TablaHashEstudiantes() {
    delete[] tabla;
}

bool TablaHashEstudiantes::agregarEstudiante(int matricula, string nombre, string carrera) {
    int indice = hash(matricula);
    int indiceOriginal = indice;
    int i = 0;

    while (tabla[indice].estado == OCUPADO && i < tableSize) {
        if (tabla[indice].clave == matricula) {
            cout << "Error: Matrícula ya existe" << endl;
            return false;
        }
        indice = (indiceOriginal + i) % tableSize;
        i++;
    }

    if (i == tableSize) {
        cout << "Error: Tabla llena" << endl;
        return false;
    }

    tabla[indice].clave = matricula;
    tabla[indice].estudiante.matricula = matricula;
    tabla[indice].estudiante.nombre = nombre;
    tabla[indice].estudiante.carrera = carrera;
    tabla[indice].estado = OCUPADO;

    cout << "Estudiante agregado exitosamente" << endl;
    return true;
}

Estudiante* TablaHashEstudiantes::buscarEstudiante(int matricula) {
    int indice = hash(matricula);
    int indiceOriginal = indice;
    int i = 0;

    while (tabla[indice].estado != VACIO && i < tableSize) {
        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == matricula) {
            return &tabla[indice].estudiante;
        }
        indice = (indiceOriginal + i) % tableSize;
        i++;
    }

    return nullptr;
}

bool TablaHashEstudiantes::eliminarEstudiante(int matricula) {
    int indice = hash(matricula);
    int indiceOriginal = indice;
    int i = 0;

    while (tabla[indice].estado != VACIO && i < tableSize) {
        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == matricula) {
            tabla[indice].estado = ELIMINADO;
            cout << "Estudiante eliminado exitosamente" << endl;
            return true;
        }
        indice = (indiceOriginal + i) % tableSize;
        i++;
    }

    cout << "Error: Estudiante no encontrado" << endl;
    return false;
}

void TablaHashEstudiantes::mostrarTabla() {
    cout << "Contenido de la tabla hash:" << endl;
    for (int i = 0; i < tableSize; i++) {
        if (tabla[i].estado == OCUPADO) {
            cout << "Posición " << i << ": "
                 << tabla[i].clave << " - "
                 << tabla[i].estudiante.nombre << endl;
        }
    }
}
