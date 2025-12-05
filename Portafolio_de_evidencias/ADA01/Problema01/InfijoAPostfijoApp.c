/*
    InfijoAPostfijoApp.c
    Convierte expresiones aritméticas de notación infija a postfija y las evalúa.
    Soporta números enteros y operadores +, -, *, /, ^, paréntesis.
    Lee expresiones desde un archivo de texto (una por línea, terminada en ';') y escribe resultados en otro archivo.
    Uso: ./InfijoAPostfijoApp exp_infijas.txt
    Salida: exp_postfijas.txt
*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "Stack.h"


// Prototipos de procedimientos
void procesar_expresiones(FILE *fin, FILE *fout);

// Prototipos de funciones
int is_operator(char);
int precedence(char);
int is_right_assoc(char);
int infix_to_postfix(const char *, char *, size_t);
int eval_postfix(const char *, long *);

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Uso: %s exp_infijas.txt\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin){
        perror("No se pudo abrir el archivo de entrada");
        return 1;
    }

    FILE *fout = fopen("exp_postfijas.txt", "w");
    if (!fout){
        perror("No se pudo crear exp_postfijas.txt");
        fclose(fin);
        return 1;
    }

    // Procesar expresiones
    procesar_expresiones(fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}

// Lee el archivo de entrada, procesa cada expresión y escribe el resultado en el archivo de salida
void procesar_expresiones(FILE *fin, FILE *fout) {
    char buf[MAX_LINE];
    size_t n = 0;
    int c;

    while ((c = fgetc(fin)) != EOF){
        if (c == ';'){
            buf[n] = '\0'; // termina la expresión (sin ';')

            char postfix[4*MAX_LINE];
            long res = 0;

            int ok1 = infix_to_postfix(buf, postfix, sizeof(postfix));
            int ok2 = ok1 ? eval_postfix(postfix, &res) : 0;

            if (ok1){
                fprintf(fout, "Expresión: %s; Resultado: %ld\n", postfix, ok2 ? res : 0L);
            } else {
                fprintf(fout, "Expresión: ERROR; Resultado: 0\n");
            }

            n = 0;
        } else {
            if (n+1 < sizeof(buf)){
                if (c != '\n' && c != '\r'){
                    buf[n++] = (char)c;
                }
            } else {
                fprintf(stderr, "Advertencia: expresión demasiado larga, se truncará.\n");
                while ((c = fgetc(fin)) != EOF && c != ';');
                n = 0;
            }
        }
    }
}

// Funciones auxiliares para conversión y evaluación
int is_operator(char c){
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

// Precedencia de operadores
int precedence(char op){
    switch(op){
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int is_right_assoc(char op){
    return op=='^'; // solo '^' es asociativo a la derecha
}

// Convierte una expresión infija (con números enteros y operadores +, -, *, /, ^, paréntesis) a postfija
int infix_to_postfix(const char *infix, char *postfix, size_t out_cap){
    charStack ops; cs_init(&ops);
    size_t k = 0;

    for(size_t i=0; infix[i]; ){
        char c = infix[i];

        // Saltar espacios
        if (isspace((unsigned char)c)){ i++; continue; }

        // Si es dígito (soporta multi-dígito)
        if (isdigit((unsigned char)c)){
            while (isdigit((unsigned char)infix[i])){
                if (k+1 >= out_cap) return 0;
                postfix[k++] = infix[i++];
            }
            if (k+1 >= out_cap) return 0;
            postfix[k++] = ' ';
            continue;
        }

        // Paréntesis
        if (c == '('){
            if (!cs_push(&ops, c)) return 0;
            i++;
            continue;
        }
        if (c == ')'){
            while (!cs_empty(&ops) && cs_peek(&ops) != '('){
                if (k+2 >= out_cap) return 0;
                postfix[k++] = cs_pop(&ops);
                postfix[k++] = ' ';
            }
            if (cs_empty(&ops)) return 0; // desbalanceado
            cs_pop(&ops); // quitar '('
            i++;
            continue; // saltar ')'
        }

        // Operador
        if (is_operator(c)){
            while (!cs_empty(&ops) && is_operator(cs_peek(&ops))){
                char top = cs_peek(&ops);
                int pt = precedence(top), pc = precedence(c);
                int popit = 0;
                if (!is_right_assoc(c)){
                    popit = (pt >= pc);
                } else {
                    popit = (pt > pc);
                }
                if (!popit) break;
                if (k+2 >= out_cap) return 0;
                postfix[k++] = cs_pop(&ops);
                postfix[k++] = ' ';
            }
            if (!cs_push(&ops, c)) return 0;
            i++;
            continue;
        }

        // Token desconocido: saltar hasta espacio o fin
        return 0;
    }

    while (!cs_empty(&ops)){
        char op = cs_pop(&ops);
        if (op=='(' || op==')') return 0; // desbalanceado
        if (k+2 >= out_cap) return 0;
        postfix[k++] = op;
        postfix[k++] = ' ';
    }

    if (k < out_cap) postfix[k] = '\0';
    else return 0;
    return 1;
}

// Evalúa una expresión postfija con tokens separados por espacios
int eval_postfix(const char *postfix, long *out){
    longStack st; ls_init(&st);
    const char *p = postfix;

    while (*p){
        // saltar espacios
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;

        // Si empieza con dígito (soporta multi-dígito)
        if (isdigit((unsigned char)*p)){
            char *end = NULL;
            errno = 0;
            long val = strtol(p, &end, 10);
            if (errno != 0 || end == p) return 0;
            if (!ls_push(&st, val)) return 0;
            p = end;
            continue;
        }

        // Operador
        if (is_operator(*p)){
            if (st.top < 1) return 0; // faltan operandos
            long b = ls_pop(&st);
            long a = ls_pop(&st);
            long r = 0;
            switch (*p){
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0) return 0; // división entre cero
                    r = a / b;            // división entera
                    break;
                case '^': {
                    // pow con enteros (truncado)
                    r = (long) llround(pow((double)a, (double)b));
                    break;
                }
            }
            if (!ls_push(&st, r)) return 0;
            p++;
            continue;
        }

        // Token desconocido: saltar hasta espacio o fin
        while (*p && !isspace((unsigned char)*p)) p++;
    }

    if (st.top != 0) return 0;
    *out = ls_pop(&st);
    return 1;
}
