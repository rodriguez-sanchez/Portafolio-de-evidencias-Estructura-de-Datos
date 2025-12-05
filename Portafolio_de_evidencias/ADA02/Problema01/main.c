#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_COLAS 3
#define MAX_CLIENTES 28

typedef struct Cliente {
    int id;
    int transacciones;
    int tiempoLlegada;
    int tiempoSalida;
    struct Cliente *sig;
} Cliente;

typedef struct {
    Cliente *frente;
    Cliente *final;
    int tamano;
    pthread_mutex_t lock;  // Mutex para proteger la cola
} Cola;

typedef struct {
    Cola *cola;
    int idCola;
    int clientesAtendidos;
    int tiempoEspera;
} ParamThread;

void inicializarCola(Cola *c) {
    c->frente = c->final = NULL;
    c->tamano = 0;
    pthread_mutex_init(&c->lock, NULL);
}

int colaVacia(Cola *c) {
    return c->tamano == 0;
}

Cliente* crearCliente(int id, int tiempoLlegada, int transacciones) {
    Cliente *nuevo = (Cliente*)malloc(sizeof(Cliente));
    if (!nuevo) {
        perror("Error al asignar memoria a cliente");
        exit(EXIT_FAILURE);
    }
    nuevo->id = id;
    nuevo->tiempoLlegada = tiempoLlegada;
    nuevo->transacciones = transacciones;
    nuevo->tiempoSalida = 0;
    nuevo->sig = NULL;
    return nuevo;
}

void encolar(Cola *c, Cliente *nuevo) {
    pthread_mutex_lock(&c->lock);
    nuevo->sig = NULL;
    if (colaVacia(c)) {
        c->frente = c->final = nuevo;
    } else {
        c->final->sig = nuevo;
        c->final = nuevo;
    }
    c->tamano++;
    pthread_mutex_unlock(&c->lock);
}

Cliente* desencolar(Cola *c) {
    pthread_mutex_lock(&c->lock);
    if (colaVacia(c)) {
        pthread_mutex_unlock(&c->lock);
        return NULL;
    }
    Cliente *aux = c->frente;
    c->frente = c->frente->sig;
    c->tamano--;
    if (c->tamano == 0) c->final = NULL;
    pthread_mutex_unlock(&c->lock);
    return aux;
}

void* atenderCola(void *arg) {
    ParamThread *params = (ParamThread*)arg;
    Cola *cola = params->cola;
    int idCola = params->idCola;

    int reloj = 0;
    params->clientesAtendidos = 0;
    params->tiempoEspera = 0;

    while (1) {
        Cliente *c = desencolar(cola);
        if (!c) break;

        if (reloj < c->tiempoLlegada) reloj = c->tiempoLlegada;

        int espera = reloj - c->tiempoLlegada;
        params->tiempoEspera += espera;
        reloj += c->transacciones;
        c->tiempoSalida = reloj;

        printf("Cliente %d atendido en cola %d: espera %d, sale en %d\n",
               c->id, idCola + 1, espera, c->tiempoSalida);

        params->clientesAtendidos++;
        free(c);
    }
    return NULL;
}

void inicializarColas(Cola colas[]) {
    for (int i = 0; i < NUM_COLAS; i++) {
        inicializarCola(&colas[i]);
    }
}

void crearYEncolarClientes(Cola colas[]) {
    int tiempo = 0;
    for (int i = 0; i < MAX_CLIENTES; i++) {
        int transacciones = 1 + rand() % 5;
        Cliente *nuevo = crearCliente(i + 1, tiempo, transacciones);
        int colaAsignada = rand() % NUM_COLAS;
        encolar(&colas[colaAsignada], nuevo);
        printf("Cliente %d llega al tiempo %d y entra a la cola %d (tarda %d)\n",
               nuevo->id, nuevo->tiempoLlegada, colaAsignada + 1, nuevo->transacciones);
        tiempo += rand() % 3;
    }
}

void crearYEsperarThreads(Cola colas[], pthread_t threads[], ParamThread params[]) {
    for (int i = 0; i < NUM_COLAS; i++) {
        params[i].cola = &colas[i];
        params[i].idCola = i;
        pthread_create(&threads[i], NULL, atenderCola, &params[i]);
    }

    for (int i = 0; i < NUM_COLAS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void imprimirEstadisticas(ParamThread params[]) {
    printf("\n--- Estadísticas por Cola ---\n");
    int totalAtendidos = 0;
    int totalEspera = 0;

    for (int i = 0; i < NUM_COLAS; i++) {
        float promedio = params[i].clientesAtendidos ? (float)params[i].tiempoEspera / params[i].clientesAtendidos : 0.0;
        printf("Cola %d: %d clientes, espera promedio: %.2f\n", i + 1, params[i].clientesAtendidos, promedio);
        for (int j = 0; j < (int)promedio; j++) {
            printf("█");
        }
        printf("\n");

        totalAtendidos += params[i].clientesAtendidos;
        totalEspera += params[i].tiempoEspera;
    }

    printf("\n--- Estadísticas Globales ---\n");
    float promedioGlobal = totalAtendidos ? (float)totalEspera / totalAtendidos : 0.0;
    printf("Total clientes atendidos: %d\n", totalAtendidos);
    printf("Espera promedio global: %.2f\n", promedioGlobal);
}

void destruirMutexes(Cola colas[]) {
    for (int i = 0; i < NUM_COLAS; i++) {
        pthread_mutex_destroy(&colas[i].lock);
    }
}

int main() {
    srand(time(NULL));
    Cola colas[NUM_COLAS];
    pthread_t threads[NUM_COLAS];
    ParamThread params[NUM_COLAS];

    inicializarColas(colas);
    crearYEncolarClientes(colas);
    crearYEsperarThreads(colas, threads, params);
    imprimirEstadisticas(params);
    destruirMutexes(colas);

    return 0;
}
