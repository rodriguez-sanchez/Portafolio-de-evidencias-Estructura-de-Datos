#include "Stack.h"

/*
    Funciones de charStack
    La pila de caracteres charStack se usa durante conversión de infija a postfija, para manejar los operadores y paréntesis.
*/
void cs_init(charStack *s) { s->top = -1; }
int cs_empty(charStack *s) { return s->top < 0; }
char cs_peek(charStack *s) { return s->data[s->top]; }
int cs_push(charStack *s, char c) {
    if (s->top + 1 >= STACK_MAX) return 0;
    s->data[++s->top] = c;
    return 1;
}
char cs_pop(charStack *s) { return s->data[s->top--]; }

/*
    Funciones de longStack
    La pila de long longStack se usa durante la evaluación de la expresión postfija, para manejar los operandos.
*/
void ls_init(longStack *s) { s->top = -1; }
int ls_empty(longStack *s) { return s->top < 0; }
int ls_push(longStack *s, long v) {
    if (s->top + 1 >= STACK_MAX) return 0;
    s->data[++s->top] = v;
    return 1;
}
long ls_pop(longStack *s) { return s->data[s->top--]; }