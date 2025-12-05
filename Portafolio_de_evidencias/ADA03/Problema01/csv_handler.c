#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "csv_handler.h"
#include "doubly_linked_list.h"

// Función para quitar comillas iniciales y finales si existen
static void strip_quotes(char *str) {
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        // Mover hacia adelante y truncar
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

// Reemplazar comillas dobles internas por una sola comilla
static void fix_inner_quotes(char *str) {
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src == '"' && *(src+1) == '"') {
            *dst++ = '"';
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

// Función para escapar comillas dobles para CSV (duplica las comillas dobles internas)
static char* escape_quotes(const char *str) {
    if (!str) return strdup("");  // Si es NULL, retorna cadena vacía

    size_t len = strlen(str);
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '"') count++;
    }

    // Reservar espacio para la cadena escapada
    char *escaped = malloc(len + count + 1);
    if (!escaped) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '"') {
            escaped[j++] = '"';  // duplicar comilla
        }
        escaped[j++] = str[i];
    }
    escaped[j] = '\0';

    return escaped;
}

bool load_movies_from_csv(const char *filename, DoublyLinkedList *list) {
    FILE *file = fopen(filename, "r");
    if (!file) return false;

    char line[8192];
    // Leer la primera línea (cabecera)
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        // Línea completa -> procesar CSV
        Movie *m = create_movie();
        if (!m) {
            fclose(file);
            return false;
        }

        // Separar la línea en tokens respetando comillas dobles (simplificado)
        // Aquí usaremos strtok y algunos ajustes para campos con comillas

        char *fields[21] = {0};
        int field_index = 0;

        char *ptr = line;
        bool in_quotes = false;
        char *start = ptr;
        char *cur = ptr;

        while (*cur && field_index < 21) {
            if (*cur == '"') in_quotes = !in_quotes;

            if (*cur == ',' && !in_quotes) {
                *cur = '\0';
                fields[field_index++] = start;
                start = cur + 1;
            }
            cur++;
        }
        if (field_index < 21) {
            fields[field_index++] = start;
        }

        // Ahora limpiar comillas de cada campo
        for (int i = 0; i < field_index; i++) {
            strip_quotes(fields[i]);
            fix_inner_quotes(fields[i]);
        }

        // Asignar campos
        m->id = (unsigned short)atoi(fields[0]);
        m->title = strdup(fields[1]);
        m->vote_average = (float)atof(fields[2]);
        m->vote_count = (unsigned short)atoi(fields[3]);
        m->status = strdup(fields[4]);
        m->release_date = strdup(fields[5]);
        m->revenue = (unsigned long)strtoul(fields[6], NULL, 10);
        m->runtime = (unsigned short)atoi(fields[7]);
        m->adult = (strcmp(fields[8], "True") == 0 || strcmp(fields[8], "true") == 0);
        m->budget = (unsigned long)strtoul(fields[9], NULL, 10);
        m->imdb_id = strdup(fields[10]);
        m->original_language = strdup(fields[11]);
        m->original_title = strdup(fields[12]);
        m->overview = strdup(fields[13]);
        m->popularity = (float)atof(fields[14]);
        m->tagline = strdup(fields[15]);
        m->genres = strdup(fields[16]);
        m->production_companies = strdup(fields[17]);
        m->production_countries = strdup(fields[18]);
        m->spoken_languages = strdup(fields[19]);
        m->keywords = strdup(fields[20]);

        append(list, m);
    }

    fclose(file);
    return true;
}

bool save_movies_to_csv(const char *filename, const DoublyLinkedList *list) {
    FILE *file = fopen(filename, "w");
    if (!file) return false;

    // Cabecera CSV
    fprintf(file, "id,title,vote_average,vote_count,status,release_date,revenue,runtime,adult,budget,imdb_id,original_language,original_title,overview,popularity,tagline,genres,production_companies,production_countries,spoken_languages,keywords\n");

    Node *current = list->head;
    while (current) {
        Movie *m = current->data;

        // Escapar campos de texto
        char *title = escape_quotes(m->title);
        char *status = escape_quotes(m->status);
        char *release_date = escape_quotes(m->release_date);
        char *imdb_id = escape_quotes(m->imdb_id);
        char *original_language = escape_quotes(m->original_language);
        char *original_title = escape_quotes(m->original_title);
        char *overview = escape_quotes(m->overview);
        char *tagline = escape_quotes(m->tagline);
        char *genres = escape_quotes(m->genres);
        char *production_companies = escape_quotes(m->production_companies);
        char *production_countries = escape_quotes(m->production_countries);
        char *spoken_languages = escape_quotes(m->spoken_languages);
        char *keywords = escape_quotes(m->keywords);

        fprintf(file, "%hu,\"%s\",%.2f,%hu,\"%s\",\"%s\",%lu,%hu,%s,%lu,\"%s\",\"%s\",\"%s\",\"%s\",%.2f,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            m->id, title, m->vote_average, m->vote_count, status, release_date,
            m->revenue, m->runtime, m->adult ? "True" : "False", m->budget, imdb_id,
            original_language, original_title, overview, m->popularity,
            tagline, genres, production_companies, production_countries,
            spoken_languages, keywords
        );

        free(title);
        free(status);
        free(release_date);
        free(imdb_id);
        free(original_language);
        free(original_title);
        free(overview);
        free(tagline);
        free(genres);
        free(production_companies);
        free(production_countries);
        free(spoken_languages);
        free(keywords);

        current = current->next;
    }

    fclose(file);
    return true;
}
