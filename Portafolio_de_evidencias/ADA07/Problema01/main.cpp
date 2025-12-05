#include <iostream>
#include <locale>
#include "TablaHashEstudiantes.hpp"

using namespace std;

int main() {
    TablaHashEstudiantes tabla;
    int opcion, matricula;
    string nombre, carrera;
    Estudiante* estudiante;

    do {
        cout << "\n--- Sistema de Registro de Estudiantes ---" << endl;
        cout << "1. Agregar estudiante" << endl;
        cout << "2. Buscar estudiante" << endl;
        cout << "3. Eliminar estudiante" << endl;
        cout << "4. Mostrar tabla" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Matrícula: ";
                cin >> matricula;
                cout << "Nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Carrera: ";
                getline(cin, carrera);
                tabla.agregarEstudiante(matricula, nombre, carrera);
                break;

            case 2:
                cout << "Matrícula a buscar: ";
                cin >> matricula;
                estudiante = tabla.buscarEstudiante(matricula);
                if (estudiante != nullptr) {
                    cout << "Estudiante encontrado:" << endl;
                    cout << "Matrícula: " << estudiante->matricula << endl;
                    cout << "Nombre: " << estudiante->nombre << endl;
                    cout << "Carrera: " << estudiante->carrera << endl;
                } else {
                    cout << "Estudiante no encontrado" << endl;
                }
                break;

            case 3:
                cout << "Matrícula a eliminar: ";
                cin >> matricula;
                tabla.eliminarEstudiante(matricula);
                break;

            case 4:
                tabla.mostrarTabla();
                break;

            case 5:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida" << endl;
        }
    } while (opcion != 5);

    return 0;
}
