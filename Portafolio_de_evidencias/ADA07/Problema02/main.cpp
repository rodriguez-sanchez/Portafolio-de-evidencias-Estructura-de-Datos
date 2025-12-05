#include <iostream>
#include <locale>
#include "TablaSimbolos.hpp"

using namespace std;

int main() {
    TablaSimbolos tabla;
    int opcion;
    string clave, tipo, valor, ambito;
    Atributos* atributos;

    do {
        cout << "\n--- Tabla de Símbolos del Compilador ---" << endl;
        cout << "1. Agregar símbolo" << endl;
        cout << "2. Buscar símbolo" << endl;
        cout << "3. Eliminar símbolo" << endl;
        cout << "4. Mostrar tabla" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Identificador: ";
                cin >> clave;

                cout << "Tipo: ";
                cin >> tipo;

                cout << "Valor: ";
                cin >> valor;

                cout << "Ámbito: ";
                cin >> ambito;

                tabla.agregarSimbolo(clave, {tipo, valor, ambito});
                break;

            case 2:
                cout << "Identificador a buscar: ";
                cin >> clave;
                atributos = tabla.buscarSimbolo(clave);

                if (atributos != nullptr) {
                    cout << "Símbolo encontrado:" << endl;
                    cout << "Identificador: " << clave << endl;
                    cout << "Tipo: " << atributos->tipo << endl;
                    cout << "Valor: " << atributos->valor << endl;
                    cout << "Ámbito: " << atributos->ambito << endl;
                } else {
                    cout << "Símbolo no encontrado" << endl;
                }
                break;

            case 3:
                cout << "Identificador a eliminar: ";
                cin >> clave;
                tabla.eliminarSimbolo(clave);
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
