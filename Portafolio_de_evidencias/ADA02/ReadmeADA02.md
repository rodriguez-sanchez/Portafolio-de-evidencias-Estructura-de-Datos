===== Simulación de atención al cliente en bancos =====

Este programa en C simula un sistema de atención de clientes de un banco en tres colas paralelas. Cada cliente llega con un tiempo de llegada y un número de transacciones que tarda en procesar. Los clientes se asignan aleatoriamente a una de las colas, que luego son atendidas simultáneamente por hilos independientes.

===== Reflexión =====
El desarrollo de este proyecto fue sencillo. Sin embargo, al implementar las funciones necesarias y probarlo, se sentía bastante estático y lineal, ya que los procesos se hacían en una sola cola de caja hasta acabar y después se pasaba a la siguiente. Pero encontramos la biblioteca que nos proporcionaba thread. Esto le dio bastante dinamismo al permitir avanzar independientemente las colas.

===== Archivos =====
    § main.c: Archivo fuente principal que contiene toda la lógica.


===== Requisitos =====
    $ Compilador de C compatible con funciones matemáticas estándar (como gcc, clang, o MinGW).


===== Compilación =====
    § Linux / macOS
        gcc main.c -o banco

    § Windows
        gcc main.c -o banco
===== Ejecución =====
    § Linux / macOS
        ./banco

    § Windows
        ./banco

===== Notas =====
    § Los tiempos de llegada y duración de transacciones son generados aleatoriamente en cada ejecución.
    $ Puedes modificar la constante MAX_CLIENTES y UM_COLAS dentro del archivo main.c para ajustar la cantidad de clientes simulados.

===== Contacto: Equipo 09 =====
    § C. Rodríguez Sánchez Gerardo Israel (Estudiante de la LIC)
        a19200922@alumnos.uady.mx
