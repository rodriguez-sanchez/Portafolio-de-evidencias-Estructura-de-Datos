#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <stdbool.h>
#include "doubly_linked_list.h"

bool load_movies_from_csv(const char *filename, DoublyLinkedList *list);
bool save_movies_to_csv(const char *filename, const DoublyLinkedList *list);
#endif // CSV_HANDLER_H
