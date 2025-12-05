# Compilador
CXX = g++
CXXFLAGS = -Wall -std=c++17

BIN_DIR = bin

# Fuentes
PARTE1_SRCS = Problema01/main.cpp Problema01/TablaHashEstudiantes.cpp
PARTE2_SRCS = Problema02/main.cpp Problema02/TablaSimbolos.cpp

# Objetos
PARTE1_OBJS = $(PARTE1_SRCS:.cpp=.o)
PARTE2_OBJS = $(PARTE2_SRCS:.cpp=.o)

# Ejecutables
PARTE1_OUTPUT = $(BIN_DIR)/Tabla_estudiantes.exe
PARTE2_OUTPUT = $(BIN_DIR)/Tabla_simbolos.exe


# -----------------------
# Objetivos ficticios (PHONY)
# -----------------------
# 'all' y 'clean' no son archivos reales, 
# así que los marcamos como PHONY para que make
# siempre ejecute sus recetas aunque existan archivos con esos nombres.
.PHONY: all clean

# -----------------------
# Objetivo por defecto
# -----------------------
# 'all' depende de:
#   1. la carpeta de binarios $(BIN_DIR)
#   2. los ejecutables de la Parte 1 y Parte 2
# Esto significa que al ejecutar 'make' se creará la carpeta
# y luego se compilarán ambos programas.
all: $(BIN_DIR) $(PARTE1_OUTPUT) $(PARTE2_OUTPUT)

# -----------------------
# Crear carpeta bin
# -----------------------
# Esta regla crea la carpeta donde se guardarán los ejecutables.
# El '-p' evita error si la carpeta ya existe.
$(BIN_DIR):
	mkdir -p $(BIN_DIR)


# Parte1
$(PARTE1_OUTPUT): $(PARTE1_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Parte2
$(PARTE2_OUTPUT): $(PARTE2_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regla genérica para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PARTE1_OBJS) $(PARTE2_OBJS) $(PARTE1_OUTPUT) $(PARTE2_OUTPUT)
