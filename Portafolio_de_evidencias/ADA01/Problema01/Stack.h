#ifndef PILA_H
#define PILA_H

#define MAX_LINE 1024
#define STACK_MAX 1024

// Pila simple para caracteres (operadores y paréntesis)
typedef struct {
    char data[STACK_MAX];
    int top;
} charStack;

// Funciones de la pila de caracteres
void cs_init(charStack *s);
int cs_empty(charStack *s);
char cs_peek(charStack *s);
int cs_push(charStack *s, char c);
char cs_pop(charStack *s);

// Pila simple para long (operandos)
typedef struct {
    long data[STACK_MAX];
    int top;
} longStack;

// Funciones de la pila de long
void ls_init(longStack *s);
int ls_empty(longStack *s);
int ls_push(longStack *s, long v);
long ls_pop(longStack *s);

#endif // PILA_H
