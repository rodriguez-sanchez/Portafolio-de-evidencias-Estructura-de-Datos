#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>

typedef struct Movie {
    unsigned short id;
    float vote_average;
    unsigned short vote_count;
    unsigned long revenue;
    unsigned short runtime;
    bool adult;
    unsigned long budget;
    float popularity;

    char *title;
    char *status;
    char *release_date;
    char *imdb_id;
    char *original_language;
    char *original_title;
    char *overview;
    char *tagline;
    char *genres;
    char *production_companies;
    char *production_countries;
    char *spoken_languages;
    char *keywords;
} Movie;

typedef struct Node {
    Movie *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} DoublyLinkedList;

// Lista y manejo de películas
void init_list(DoublyLinkedList *list);
Movie *create_movie();
void append(DoublyLinkedList *list, Movie *movie);
void delete_node(DoublyLinkedList *list, Node *node);
void clear_list(DoublyLinkedList *list);
void print_all_movies(const DoublyLinkedList *list);

bool is_duplicate(const DoublyLinkedList *list, unsigned short id, const char *imdb_id);
bool add_movie_unique(DoublyLinkedList *list, Movie *m);

Movie *find_by_id(const DoublyLinkedList *list, unsigned short id);
Movie *find_by_imdb_id(const DoublyLinkedList *list, const char *imdb_id);

DoublyLinkedList *find_by_title(const DoublyLinkedList *list, const char *title_part);
DoublyLinkedList *find_by_release_date(const DoublyLinkedList *list, const char *date_part);

// Funciones de movie_utils.c (prototipos para integración)
bool fill_movie_strings(Movie *m);
bool fill_movie_numbers(Movie *m);
bool read_string_field(const char *prompt, char **field);
bool read_number_field(const char *prompt, const char *format, void *out);
bool read_bool_field(const char *prompt, bool *out);
void print_movie(const Movie *m);
void free_movie(Movie *m);
bool update_movie_field(Movie *m);

#endif // DOUBLY_LINKED_LIST_H
