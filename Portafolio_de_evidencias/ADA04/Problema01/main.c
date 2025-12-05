#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64
#define SURNAME_LEN 64

typedef struct {
    float *data;
    int size;
    int capacity;
} GradeArray;

typedef struct {
    int matricula;
    char nombre[NAME_LEN];
    char apellido[SURNAME_LEN];
    GradeArray grades;
} Student;

typedef struct Node {
    Student student;
    struct Node *left;
    struct Node *right;
} Node;


//- Prototipos de funciones y procedimientos

//- Funciones del árbol
Node* tree_insert(Node *root, Student s);
Node* tree_delete(Node *root, int matricula);
void tree_free(Node *root);

//- Funciones de reporte
void report_inorder(Node *root);
void report_by_average(Node *root);
void report_by_threshold(Node *root, float limite, int menor);
int count_less_than_student(Node *root, int matricula, int *count);
void print_level(Node *root, int nivel);
void print_ascii(Node *root, int espacio, char simbolo);

//- Funciones de utilidades
Student input_student(void);
int update_grade(Node *root, int matricula, int indice, float nuevo_valor);

//- Interfaz de usuario
void print_menu(void);

//- Función principal
int main() {
    Node *root = NULL;
    int opc;

    do {
        print_menu();
        printf("\nSeleccione una opción: ");
        if (scanf("%d", &opc) != 1) break;
        getchar(); // limpia el buffer

        switch (opc) {
            case 1:
                printf("\n-- Reporte por matrícula (inorden) --\n");
                report_inorder(root);
                break;
            case 2:
                printf("\n-- Reporte por promedio (ascendente) --\n");
                report_by_average(root);
                break;
            case 3:
                printf("\n-- Promedio < 70 --\n");
                report_by_threshold(root, 70.0f, 1);
                break;
            case 4:
                printf("\n-- Promedio >= 70 --\n");
                report_by_threshold(root, 70.0f, 0);
                break;
            case 5: {
                printf("\n-- Insertar estudiante --\n");
                Student s = input_student();
                root = tree_insert(root, s);
                break;
            }
            case 6: {
                int m;
                printf("\nMatrícula a eliminar: ");
                scanf("%d", &m);
                root = tree_delete(root, m);
                break;
            }
            case 7: {
                int m, idx;
                float nv;
                printf("\nMatrícula: "); scanf("%d", &m);
                printf("Índice de calificación a actualizar (0-based): "); scanf("%d", &idx);
                printf("Nuevo valor: "); scanf("%f", &nv);
                int r = update_grade(root, m, idx, nv);
                if (r == 1) printf("Calificación actualizada.\n");
                else if (r == -1) printf("Índice fuera de rango.\n");
                else printf("Matrícula no encontrada.\n");
                break;
            }
            case 8: {
                int m, count;
                printf("\nMatrícula: "); scanf("%d", &m);
                if (count_less_than_student(root, m, &count)) {
                    printf("Alumnos con promedio menor al del alumno %d: %d\n", m, count);
                } else {
                    printf("Matrícula no encontrada.\n");
                }
                break;
            }
            case 9: {
                int lvl;
                printf("\nNivel (0 para raíz): "); scanf("%d", &lvl);
                printf("-- Nodos en nivel %d --\n", lvl);
                print_level(root, lvl);
                break;
            }
            case 10:
                printf("\n-- Árbol en ASCII --\n");
                print_ascii(root, 0, '*');
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpción inválida.\n");
        }

    } while (opc != 0);

    tree_free(root);
    return 0;
}

//- Definición del menú
void print_menu(void) {
    printf("\n============================================\n");
    printf("          SISTEMA DE GESTIÓN DE ALUMNOS      \n");
    printf("============================================\n");
    printf(" 1. Reporte por matrícula (inorden)\n");
    printf(" 2. Reporte por promedio (ascendente)\n");
    printf(" 3. Reporte de alumnos con promedio < 70\n");
    printf(" 4. Reporte de alumnos con promedio >= 70\n");
    printf(" 5. Insertar estudiante\n");
    printf(" 6. Eliminar estudiante\n");
    printf(" 7. Actualizar calificación\n");
    printf(" 8. Contar alumnos con promedio menor\n");
    printf(" 9. Mostrar nodos de un nivel\n");
    printf("10. Mostrar árbol en ASCII\n");
    printf(" 0. Salir\n");
    printf("============================================\n");
}

/* --------- Utilidades de GradeArray --------- */
void grades_init(GradeArray *ga) {
    ga->size = 0;
    ga->capacity = 4;
    ga->data = (float*)malloc(sizeof(float) * ga->capacity);
}

void grades_free(GradeArray *ga) {
    free(ga->data);
    ga->data = NULL;
    ga->size = ga->capacity = 0;
}

void grades_push(GradeArray *ga, float value) {
    if (ga->size == ga->capacity) {
        ga->capacity *= 2;
        ga->data = (float*)realloc(ga->data, sizeof(float) * ga->capacity);
    }
    ga->data[ga->size++] = value;
}

float grades_average(const GradeArray *ga) {
    if (ga->size == 0) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < ga->size; i++) sum += ga->data[i];
    return sum / ga->size;
}

/* --------- Gestión de Student --------- */
Student student_create(int matricula, const char *nombre, const char *apellido) {
    Student s;
    s.matricula = matricula;
    strncpy(s.nombre, nombre, NAME_LEN - 1);
    s.nombre[NAME_LEN - 1] = '\0';
    strncpy(s.apellido, apellido, SURNAME_LEN - 1);
    s.apellido[SURNAME_LEN - 1] = '\0';
    grades_init(&s.grades);
    return s;
}

void student_free(Student *s) {
    grades_free(&s->grades);
}

/* --------- ABB: creación y utilidades --------- */
Node* node_create(Student s) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->student = s;
    n->left = n->right = NULL;
    return n;
}

void tree_free(Node *root) {
    if (!root) return;
    tree_free(root->left);
    tree_free(root->right);
    student_free(&root->student);
    free(root);
}

Node* tree_insert(Node *root, Student s) {
    if (!root) return node_create(s);
    if (s.matricula < root->student.matricula) {
        root->left = tree_insert(root->left, s);
    } else if (s.matricula > root->student.matricula) {
        root->right = tree_insert(root->right, s);
    } else {
        // Matrícula duplicada: actualizar nombre/apellido, pero mantener calificaciones existentes
        strncpy(root->student.nombre, s.nombre, NAME_LEN - 1);
        strncpy(root->student.apellido, s.apellido, SURNAME_LEN - 1);
        root->student.nombre[NAME_LEN - 1] = '\0';
        root->student.apellido[SURNAME_LEN - 1] = '\0';
        // Liberar calificaciones de s (las que venían nuevas) para evitar fugas
        grades_free(&s.grades);
    }
    return root;
}

Node* tree_search(Node *root, int matricula) {
    if (!root) return NULL;
    if (matricula < root->student.matricula) return tree_search(root->left, matricula);
    if (matricula > root->student.matricula) return tree_search(root->right, matricula);
    return root;
}

/* --------- ABB: eliminación --------- */
Node* find_min(Node *root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* tree_delete(Node *root, int matricula) {
    if (!root) return NULL;
    if (matricula < root->student.matricula) {
        root->left = tree_delete(root->left, matricula);
    } else if (matricula > root->student.matricula) {
        root->right = tree_delete(root->right, matricula);
    } else {
        // Encontrado
        if (!root->left && !root->right) {
            student_free(&root->student);
            free(root);
            return NULL;
        } else if (!root->left) {
            Node *temp = root->right;
            student_free(&root->student);
            free(root);
            return temp;
        } else if (!root->right) {
            Node *temp = root->left;
            student_free(&root->student);
            free(root);
            return temp;
        } else {
            // Dos hijos: reemplazar con mínimo de subárbol derecho
            Node *minRight = find_min(root->right);
            // Copiar datos del sucesor
            // Primero liberar calificaciones del actual
            grades_free(&root->student.grades);
            root->student.matricula = minRight->student.matricula;
            strncpy(root->student.nombre, minRight->student.nombre, NAME_LEN);
            strncpy(root->student.apellido, minRight->student.apellido, SURNAME_LEN);
            // Clonar grades
            grades_init(&root->student.grades);
            for (int i = 0; i < minRight->student.grades.size; i++) {
                grades_push(&root->student.grades, minRight->student.grades.data[i]);
            }
            // Eliminar el sucesor en subárbol derecho
            root->right = tree_delete(root->right, minRight->student.matricula);
        }
    }
    return root;
}

/* --------- Reportes y recorridos --------- */
void print_student(const Student *s) {
    printf("Matricula: %d | %s %s | Calificaciones: [", s->matricula, s->nombre, s->apellido);
    for (int i = 0; i < s->grades.size; i++) {
        printf("%.2f", s->grades.data[i]);
        if (i + 1 < s->grades.size) printf(", ");
    }
    printf("] | Promedio: %.2f\n", grades_average(&s->grades));
}

void report_inorder(Node *root) {
    if (!root) return;
    report_inorder(root->left);
    print_student(&root->student);
    report_inorder(root->right);
}

/* Recolectar nodos en arreglo para ordenar por promedio */
typedef struct {
    Node **nodes;
    int size;
    int capacity;
} NodeArray;

void na_init(NodeArray *na) {
    na->size = 0;
    na->capacity = 16;
    na->nodes = (Node**)malloc(sizeof(Node*) * na->capacity);
}

void na_push(NodeArray *na, Node *n) {
    if (na->size == na->capacity) {
        na->capacity *= 2;
        na->nodes = (Node**)realloc(na->nodes, sizeof(Node*) * na->capacity);
    }
    na->nodes[na->size++] = n;
}

void na_free(NodeArray *na) {
    free(na->nodes);
    na->nodes = NULL;
    na->size = na->capacity = 0;
}

void collect_nodes(Node *root, NodeArray *na) {
    if (!root) return;
    collect_nodes(root->left, na);
    na_push(na, root);
    collect_nodes(root->right, na);
}

int cmp_by_avg_asc(const void *a, const void *b) {
    const Node *na = *(const Node* const*)a;
    const Node *nb = *(const Node* const*)b;
    float pa = grades_average(&na->student.grades);
    float pb = grades_average(&nb->student.grades);
    if (pa < pb) return -1;
    if (pa > pb) return 1;
    // desempate por matrícula
    return (na->student.matricula - nb->student.matricula);
}

void report_by_average(Node *root) {
    NodeArray arr; na_init(&arr);
    collect_nodes(root, &arr);
    qsort(arr.nodes, arr.size, sizeof(Node*), cmp_by_avg_asc);
    for (int i = 0; i < arr.size; i++) {
        print_student(&arr.nodes[i]->student);
    }
    na_free(&arr);
}

void report_by_threshold(Node *root, float threshold, int less_than) {
    if (!root) return;
    report_by_threshold(root->left, threshold, less_than);
    float avg = grades_average(&root->student.grades);
    if ((less_than && avg < threshold) || (!less_than && avg >= threshold)) {
        print_student(&root->student);
    }
    report_by_threshold(root->right, threshold, less_than);
}

/* --------- Actualización de una calificación --------- */
int update_grade(Node *root, int matricula, int index, float new_value) {
    Node *n = tree_search(root, matricula);
    if (!n) return 0;
    if (index < 0 || index >= n->student.grades.size) return -1;
    n->student.grades.data[index] = new_value;
    return 1;
}

/* --------- Contar alumnos con promedio menor al de un alumno dado --------- */
int count_students_with_lower_avg(Node *root, float target_avg) {
    if (!root) return 0;
    int left = count_students_with_lower_avg(root->left, target_avg);
    int right = count_students_with_lower_avg(root->right, target_avg);
    return left + right + (grades_average(&root->student.grades) < target_avg ? 1 : 0);
}

int count_less_than_student(Node *root, int matricula, int *out_count) {
    Node *n = tree_search(root, matricula);
    if (!n) return 0;
    float target_avg = grades_average(&n->student.grades);
    *out_count = count_students_with_lower_avg(root, target_avg);
    // excluir al propio alumno si corresponde (su avg no es menor a sí mismo)
    return 1;
}

/* --------- Mostrar nodos por nivel --------- */
void print_level(Node *root, int level) {
    if (!root) return;
    if (level == 0) {
        print_student(&root->student);
        return;
    }
    print_level(root->left, level - 1);
    print_level(root->right, level - 1);
}

/* --------- Mostrar árbol en ASCII --------- */
void print_ascii(Node *root, int depth, char branch) {
    if (!root) return;
    print_ascii(root->right, depth + 1, '/');
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%c-[%d]\n", branch, root->student.matricula);
    print_ascii(root->left, depth + 1, '\\');
}

/* --------- Entrada de datos --------- */
Student input_student() {
    int m; char nombre[NAME_LEN], apellido[SURNAME_LEN];
    printf("Matricula: "); scanf("%d", &m);
    getchar();

    printf("Nombre: "); scanf("%63[^\n]", nombre);
    getchar();

    printf("Apellido: "); scanf("%63[^\n]", apellido);
    getchar();

    Student s = student_create(m, nombre, apellido);
    int ncal;
    printf("Numero de calificaciones: "); scanf("%d", &ncal);
    for (int i = 0; i < ncal; i++) {
        float c;
        printf("Calificacion %d: ", i);
        scanf("%f", &c);
        grades_push(&s.grades, c);
    }
    return s;
}
