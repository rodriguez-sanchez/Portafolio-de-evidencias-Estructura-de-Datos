# ADA07_E09

## Descripción
Este repositorio contiene el código fuente y el Makefile necesarios para compilar y ejecutar la práctica **ADA07_E09**.  
El Makefile automatiza la compilación, ejecución y limpieza de los artefactos generados.

## Reflexión
Fue un proyecto que se dividió en dos partes, del cual me gustó trabajar en la tabla de símbolos, pues nuevamente me aclaró ideas sobre el funcionamiento interno del compilador. Asimismo, se hizo uso de Doxygen para una mejor documentación del proyecto.

## Contacto
- **C. Rodríguez Sánchez Gerardo Israel** (Estudiante de la LIC)  
  Correo: `a19200922@alumnos.uady.mx`

## Requisitos
- MSYS2 con shell **MINGW64**.
- Herramienta `make` disponible en el entorno **MINGW64**.

## Uso rápido en Microsoft Windows
1. Abrir el shell **MSYS2 MINGW64**.
2. Entrar al directorio del proyecto:
    ```bash
    cd ADA07_E09
    ```
3. Ejecutar el Makefile:
    ```bash
    make
    ```
   > Este comando compila ambos programas y genera los ejecutables en la carpeta `bin/`.

## Targets disponibles
- `make` — objetivo por defecto: compila y ejecuta el proyecto.
- `make clean` — elimina archivos generados (binarios, objetos, etc.).

## Notas
- Es importante usar el shell **MINGW64** para asegurar que las rutas y herramientas funcionen correctamente.
- Asegúrate de que `make` esté correctamente instalado y accesible desde el entorno MSYS2.
