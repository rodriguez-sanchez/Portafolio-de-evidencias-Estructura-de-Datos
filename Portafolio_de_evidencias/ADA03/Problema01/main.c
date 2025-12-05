#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "csv_handler.h"
#include "doubly_linked_list.h"

void print_search_results(DoublyLinkedList *);
void movie_menu(DoublyLinkedList *);

int main() {
    if (setlocale(LC_ALL, "es_ES.UTF-8") == NULL) {
        printf("No se pudo establecer locale es_ES.UTF-8\n");
    }

    
    DoublyLinkedList movie_list;
    init_list(&movie_list);

    if (!load_movies_from_csv("Movies.csv", &movie_list)) {
        printf("No se pudo cargar el archivo CSV o no existe.\n");
    } else {
        printf("Películas cargadas exitosamente.\n");
    }

    movie_menu(&movie_list);

    clear_list(&movie_list);
    return 0;
}

void print_search_results(DoublyLinkedList *results) {
    if (!results || !results->head) {
        printf("No se encontraron películas.\n");
        if (results) clear_list(results);
        free(results);
        return;
    }
    print_all_movies(results);
    clear_list(results);
    free(results);
}

void movie_menu(DoublyLinkedList *list) {
    int opcion;
    while (1) {
        printf("\n=== Menú de Películas ===\n");
        printf("1. Agregar nueva película\n");
        printf("2. Ver todas las películas\n");
        printf("3. Eliminar película por ID\n");
        printf("4. Actualizar película por ID\n");
        printf("5. Buscar película por ID\n");
        printf("6. Buscar película por imdb_id\n");
        printf("7. Buscar películas por título (parcial)\n");
        printf("8. Buscar películas por fecha de lanzamiento (parcial)\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("Entrada inválida.\n");
            continue;
        }
        while (getchar() != '\n');

        if (opcion == 1) {
            Movie *m = create_movie();
            if (!m) {
                printf("Error al crear película.\n");
                continue;
            }
            if (!fill_movie_numbers(m) || !fill_movie_strings(m)) {
                printf("Error al llenar la información.\n");
                free_movie(m);
                continue;
            }
            if (!add_movie_unique(list, m)) {
                printf("Error: Película con mismo ID o imdb_id ya existe.\n");
                free_movie(m);
                continue;
            }
            printf("Película agregada exitosamente.\n");
            if (!save_movies_to_csv("Movies.csv", list)) {
                printf("Error al guardar cambios en el archivo CSV.\n");
            }
        }
        else if (opcion == 2) {
            print_all_movies(list);
        }
        else if (opcion == 3) {
            unsigned short id;
            printf("Ingrese ID de la película a eliminar: ");
            if (scanf("%hu", &id) != 1) {
                while (getchar() != '\n');
                printf("Entrada inválida.\n");
                continue;
            }
            while (getchar() != '\n');
            Node *current = list->head;
            bool found = false;
            while (current) {
                if (current->data->id == id) {
                    found = true;
                    printf("\n--- Detalles de la película ---\n");
                    print_movie(current->data);
                    printf("\n¿Desea eliminar esta película? (Y/n): ");
                    char respuesta = getchar();
                    while (getchar() != '\n');
                    if (respuesta == 'Y' || respuesta == 'y' || respuesta == '\n') {
                        delete_node(list, current);
                        printf("Película eliminada.\n");
                        if (!save_movies_to_csv("Movies.csv", list)) {
                            printf("Error al guardar cambios en el archivo CSV.\n");
                        }
                    } else {
                        printf("Operación cancelada.\n");
                    }
                    break;
                }
                current = current->next;
            }
            if (!found) {
                printf("Película no encontrada.\n");
            }
        }
        else if (opcion == 4) {
            unsigned short id;
            printf("Ingrese ID de la película a actualizar: ");
            if (scanf("%hu", &id) != 1) {
                while (getchar() != '\n');
                printf("Entrada inválida.\n");
                continue;
            }
            while (getchar() != '\n');
            Node *current = list->head;
            bool found = false;
            while (current) {
                if (current->data->id == id) {
                    found = true;
                    if (update_movie_field(current->data)) {
                        printf("Película actualizada.\n");
                        if (!save_movies_to_csv("Movies.csv", list)) {
                            printf("Error al guardar cambios en el archivo CSV.\n");
                        }
                    } else {
                        printf("Actualización cancelada o fallida.\n");
                    }
                    break;
                }
                current = current->next;
            }
            if (!found) {
                printf("Película no encontrada.\n");
            }
        }
        else if (opcion == 5) {
            unsigned short id;
            printf("Ingrese ID a buscar: ");
            if (scanf("%hu", &id) != 1) {
                while (getchar() != '\n');
                printf("Entrada inválida.\n");
                continue;
            }
            while (getchar() != '\n');
            Movie *m = find_by_id(list, id);
            if (m) {
                print_movie(m);
            } else {
                printf("Película no encontrada.\n");
            }
        }
        else if (opcion == 6) {
            char imdb_id[256];
            printf("Ingrese imdb_id a buscar: ");
            if (!fgets(imdb_id, sizeof(imdb_id), stdin)) {
                printf("Entrada inválida.\n");
                continue;
            }
            imdb_id[strcspn(imdb_id, "\n")] = 0;
            Movie *m = find_by_imdb_id(list, imdb_id);
            if (m) {
                print_movie(m);
            } else {
                printf("Película no encontrada.\n");
            }
        }
        else if (opcion == 7) {
            char title_part[256];
            printf("Ingrese parte del título a buscar: ");
            if (!fgets(title_part, sizeof(title_part), stdin)) {
                printf("Entrada inválida.\n");
                continue;
            }
            title_part[strcspn(title_part, "\n")] = 0;
            DoublyLinkedList *results = find_by_title(list, title_part);
            print_search_results(results);
        }
        else if (opcion == 8) {
            char date_part[256];
            printf("Ingrese parte de la fecha de lanzamiento a buscar (formato dd/mm/aaaa o parte): ");
            if (!fgets(date_part, sizeof(date_part), stdin)) {
                printf("Entrada inválida.\n");
                continue;
            }
            date_part[strcspn(date_part, "\n")] = 0;
            DoublyLinkedList *results = find_by_release_date(list, date_part);
            print_search_results(results);
        }
        else if (opcion == 0) {
            printf("Saliendo del programa.\n");
            break;
        }
        else {
            printf("Opción inválida.\n");
        }
    }
}
