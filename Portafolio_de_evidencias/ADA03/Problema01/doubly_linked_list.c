#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "doubly_linked_list.h"

// Inicializa la lista vacía
void init_list(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// Agrega un nodo al final
void append(DoublyLinkedList *list, Movie *movie) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;

    new_node->data = movie;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail) list->tail->next = new_node;
    else list->head = new_node;

    list->tail = new_node;
}

// Borra un nodo y libera su película
void delete_node(DoublyLinkedList *list, Node *node) {
    if (!node) return;

    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;

    free_movie(node->data);
    free(node);
}

// Limpia toda la lista
void clear_list(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        delete_node(list, current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

// Imprime todas las películas
void print_all_movies(const DoublyLinkedList *list) {
    Node *current = list->head;
    int index = 1;
    while (current) {
        printf("\n--- Película %d ---\n", index++);
        print_movie(current->data);
        current = current->next;
    }
}

// Verifica si ya existe una película con el mismo id o imdb_id
bool is_duplicate(const DoublyLinkedList *list, unsigned short id, const char *imdb_id) {
    Node *current = list->head;
    while (current) {
        Movie *m = current->data;
        if (m->id == id) return true;
        if (strcmp(m->imdb_id, imdb_id) == 0) return true;
        current = current->next;
    }
    return false;
}

// Agrega película sólo si no es duplicada
bool add_movie_unique(DoublyLinkedList *list, Movie *m) {
    if (is_duplicate(list, m->id, m->imdb_id)) {
        return false;
    }
    append(list, m);
    return true;
}

// Busca por id y devuelve puntero a película o NULL si no está
Movie *find_by_id(const DoublyLinkedList *list, unsigned short id) {
    Node *current = list->head;
    while (current) {
        if (current->data->id == id) return current->data;
        current = current->next;
    }
    return NULL;
}

// Busca por imdb_id y devuelve puntero a película o NULL si no está
Movie *find_by_imdb_id(const DoublyLinkedList *list, const char *imdb_id) {
    Node *current = list->head;
    while (current) {
        if (strcmp(current->data->imdb_id, imdb_id) == 0) return current->data;
        current = current->next;
    }
    return NULL;
}

// Función auxiliar para búsqueda case-insensitive parcial en título
static int strcasestr_index(const char *haystack, const char *needle) {
    if (!*needle) return 0;
    for (int i = 0; haystack[i]; i++) {
        int j = 0;
        while (tolower((unsigned char)haystack[i + j]) == tolower((unsigned char)needle[j])) {
            if (!needle[j + 1]) return i;
            j++;
        }
    }
    return -1;
}

// Busca películas cuyo título contenga la cadena dada (case-insensitive)
DoublyLinkedList *find_by_title(const DoublyLinkedList *list, const char *title_part) {
    DoublyLinkedList *result = malloc(sizeof(DoublyLinkedList));
    if (!result) return NULL;
    init_list(result);

    Node *current = list->head;
    while (current) {
        if (strcasestr_index(current->data->title, title_part) >= 0) {
            append(result, current->data);
        }
        current = current->next;
    }
    return result;
}

// Busca películas cuya fecha de lanzamiento contenga la cadena dada
DoublyLinkedList *find_by_release_date(const DoublyLinkedList *list, const char *date_part) {
    DoublyLinkedList *result = malloc(sizeof(DoublyLinkedList));
    if (!result) return NULL;
    init_list(result);

    Node *current = list->head;
    while (current) {
        if (strstr(current->data->release_date, date_part) != NULL) {
            append(result, current->data);
        }
        current = current->next;
    }
    return result;
}
