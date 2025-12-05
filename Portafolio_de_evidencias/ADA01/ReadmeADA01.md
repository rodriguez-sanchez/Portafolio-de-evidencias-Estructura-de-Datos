===== Parser de expresiones aritméticas =====

Este programa en C permite convertir expresiones aritméticas infijas (como 3 + 4 * 2) a su forma postfija (también llamada notación polaca inversa, por ejemplo 3 4 2 * +) y luego evalúa el resultado numérico.

Lee las expresiones desde un archivo de texto (una por línea, terminada en ;) y escribe tanto la forma postfija como el resultado en un archivo de salida.

Soporta los operadores:
    + (suma),
    - (resta),
    * (multiplicación),
    / (división entera),
    ^ (potencia), y
    paréntesis ( y )

Los resultados se guardan en un archivo llamado exp_postfijas.txt.

===== Reflexión =====
En esta actividad tuve un poco más de noción de cómo un compilador gestionaba el manejo de las operaciones, lo cual involucra los operandos, operadores y la prioridad, así como la sintaxis al definir las expresiones a resolver. Esto representó un desafío bastante interesante, pues desarrollamos la comprensión en notación prefija y posfija, y la implementación con la ED pila fue sencilla.

===== Archivos =====
    § InfijoAPostfijoApp.c: Archivo fuente del programa. Contiene la lógica para leer las expresiones en notación infija, convertirlas a postfija, evaluar el resultado y escribir la salida en un archivo.
    § Stack.c: Archivo fuente que implementa las funciones para manejar las pilas (stack) de caracteres y de números enteros largas (charStack y longStack), usadas para la conversión y evaluación de expresiones.
    $ Stack.h: Archivo de cabecera que declara las estructuras de datos y prototipos de las funciones para manipular las pilas, permitiendo su uso en otros archivos fuente.
    § exp_infijas.txt: Archivo de entrada con el texto a analizar (debes crearlo).
    § exp_postfijas.txt: Archivo generado con los resultados (por defecto).

===== Requisitos =====
    $ Compilador de C compatible con funciones matemáticas estándar (como gcc, clang, o MinGW).

===== Compilación =====
    § Linux / macOS
        gcc InfijoAPostfijoApp.c Stack.c -o InfijoAPostfijoApp -lm
    § Windows
        gcc InfijoAPostfijoApp.c Stack.c -o InfijoAPostfijoApp
Nota: El flag -lm le indica al compilador que debe enlazar (link) la biblioteca matemática de C (libm).

===== Ejecución =====
    § Linux / macOS
        ./InfijoAPostfijoApp exp_infijas.txt
    § Windows
        ./InfijoAPostfijoApp exp_infijas.txt

===== Notas =====
    § Asegúrate de tener un archivo exp_infijas.txt en el mismo directorio que el ejecutable.
    § El programa es sensible a los caracteres introducidos: solo reconoce los siguientes operadores: +, -, *, /, ^, y paréntesis ( y ).
        No se aceptan símbolos similares, como el guion largo (–) en lugar del guion estándar (-).
        El uso de caracteres inválidos o mal escritos generará un error al evaluar la expresión.
    $ Archivo de entrada con expresiones válidas terminadas en punto y coma (;)
    § El archivo salida.txt se sobreescribe en cada ejecución.

===== Contacto =====
    § C. Rodríguez Sánchez Gerardo Israel (Estudiante de la LIC)
        a19200922@alumnos.uady.mx
