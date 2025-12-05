SISTEMA DE GESTIÓN DE ALUMNOS CON ÁRBOL BINARIO DE BÚSQUEDA

===== Archivos =====
    - main.c : código fuente principal
    - README.txt : documentación del proyecto

===== Descripción =====
Este proyecto implementa un sistema de gestión de alumnos en C utilizando un Árbol Binario de Búsqueda (ABB) para almacenar información de estudiantes, incluyendo:

- Matrícula
- Nombre y Apellido
- Calificaciones dinámicas

El programa permite:
- Insertar, eliminar y actualizar estudiantes
- Registrar y actualizar calificaciones
- Generar reportes por matrícula (inorden), por promedio (ascendente) y por umbrales de promedio
- Contar alumnos con promedio menor al de un estudiante dado
- Mostrar nodos por nivel y el árbol en representación ASCII

===== Reflexión =====
Una de las primeras motivaciones durante el desarrollo de la actividad era manejar gráficos para desplegar la información del árbol, reemplazando el uso del ASCII en la terminal. Sin embargo, aún no estaba listo ni familiarizado con las herramientas, siendo que se usa C++ por compatibilidad con las bibliotecas gráficas populares al usar clases, aprovechando el paradigma del lenguaje, es decir, la POO.

===== Requisitos =====
$ Compilador de C compatible con funciones matemáticas estándar (como gcc, clang, o MinGW).

===== Compilación =====
gcc main.c -o gestion_alumnos

===== Ejecución =====
./gestion_alumnos

===== Notas =====
Manejo de memoria:
    - Se utiliza memoria dinámica para las calificaciones y nodos del árbol
    - Todas las estructuras se liberan al finalizar (tree_free, grades_free)

Validación de entradas:
    - Ingresar correctamente enteros (matrícula) y flotantes
    - No exceder la longitud máxima de nombre y apellido (63 caracteres)

===== Contacto: Equipo 09 =====
    § C. Rodríguez Sánchez Gerardo Israel (Estudiante de la LIC)
        a19200922@alumnos.uady.mx
