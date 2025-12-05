#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "doubly_linked_list.h"

Movie *create_movie() {
    Movie *m = malloc(sizeof(Movie));
    if (!m) return NULL;
    memset(m, 0, sizeof(Movie)); // Inicializa a 0 y punteros a NULL
    return m;
}

bool read_string_field(const char *prompt, char **field) {
    printf("%s", prompt);
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) return false;

    buffer[strcspn(buffer, "\n")] = 0;

    *field = malloc(strlen(buffer) + 1);
    if (!*field) return false;
    strcpy(*field, buffer);
    return true;
}

bool read_number_field(const char *prompt, const char *format, void *out) {
    printf("%s", prompt);
    char buffer[100];
    if (!fgets(buffer, sizeof(buffer), stdin)) return false;
    return sscanf(buffer, format, out) == 1;
}

bool read_bool_field(const char *prompt, bool *out) {
    char buffer[10];
    printf("%s (0 = No, 1 = Sí): ", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin)) return false;

    int val;
    if (sscanf(buffer, "%d", &val) != 1 || (val != 0 && val != 1)) return false;

    *out = (val == 1);
    return true;
}

bool fill_movie_numbers(Movie *m) {
    return read_number_field("ID: ", "%hu", &m->id)
        && read_number_field("Promedio de votos: ", "%f", &m->vote_average)
        && read_number_field("Cantidad de votos: ", "%hu", &m->vote_count)
        && read_number_field("Ingresos: ", "%lu", &m->revenue)
        && read_number_field("Duración (min): ", "%hu", &m->runtime)
        && read_bool_field("¿Es para adultos?", &m->adult)
        && read_number_field("Presupuesto: ", "%lu", &m->budget)
        && read_number_field("Popularidad: ", "%f", &m->popularity);
}

bool fill_movie_strings(Movie *m) {
    return read_string_field("Título: ", &m->title)
        && read_string_field("Estado: ", &m->status)
        && read_string_field("Fecha de lanzamiento: ", &m->release_date)
        && read_string_field("ID de IMDB: ", &m->imdb_id)
        && read_string_field("Idioma original: ", &m->original_language)
        && read_string_field("Título original: ", &m->original_title)
        && read_string_field("Resumen: ", &m->overview)
        && read_string_field("Eslogan: ", &m->tagline)
        && read_string_field("Géneros: ", &m->genres)
        && read_string_field("Compañías productoras: ", &m->production_companies)
        && read_string_field("Países de producción: ", &m->production_countries)
        && read_string_field("Idiomas hablados: ", &m->spoken_languages)
        && read_string_field("Palabras clave: ", &m->keywords);
}

void print_movie(const Movie *m) {
    printf("ID: %hu\n", m->id);
    printf("Promedio de votos: %.2f\n", m->vote_average);
    printf("Cantidad de votos: %hu\n", m->vote_count);
    printf("Ingresos: %lu\n", m->revenue);
    printf("Duración: %hu minutos\n", m->runtime);
    printf("Adulto: %s\n", m->adult ? "Sí" : "No");
    printf("Presupuesto: %lu\n", m->budget);
    printf("Popularidad: %.2f\n", m->popularity);

    printf("Título: %s\n", m->title);
    printf("Estado: %s\n", m->status);
    printf("Fecha de lanzamiento: %s\n", m->release_date);
    printf("ID de IMDB: %s\n", m->imdb_id);
    printf("Idioma original: %s\n", m->original_language);
    printf("Título original: %s\n", m->original_title);
    printf("Resumen: %s\n", m->overview);
    printf("Eslogan: %s\n", m->tagline);
    printf("Géneros: %s\n", m->genres);
    printf("Compañías productoras: %s\n", m->production_companies);
    printf("Países de producción: %s\n", m->production_countries);
    printf("Idiomas hablados: %s\n", m->spoken_languages);
    printf("Palabras clave: %s\n", m->keywords);
}

void free_movie(Movie *m) {
    if (!m) return;

    free(m->title);
    free(m->status);
    free(m->release_date);
    free(m->imdb_id);
    free(m->original_language);
    free(m->original_title);
    free(m->overview);
    free(m->tagline);
    free(m->genres);
    free(m->production_companies);
    free(m->production_countries);
    free(m->spoken_languages);
    free(m->keywords);

    free(m);
}

bool update_movie_field(Movie *m) {
    printf("¿Qué campo desea actualizar?\n");
    printf("1. Título\n2. Eslogan\n3. Promedio de votos\n0. Cancelar\n");

    int opcion;
    if (scanf("%d", &opcion) != 1) {
        while (getchar() != '\n');
        return false;
    }
    while (getchar() != '\n');

    switch (opcion) {
        case 1:
            free(m->title);
            return read_string_field("Nuevo título: ", &m->title);
        case 2:
            free(m->tagline);
            return read_string_field("Nuevo eslogan: ", &m->tagline);
        case 3:
            return read_number_field("Nuevo promedio de votos: ", "%f", &m->vote_average);
        case 0:
            return false;
        default:
            printf("Opción inválida.\n");
            return false;
    }
}
