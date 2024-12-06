# Definir el compilador y las banderas de compilación
CC = g++
CFLAGS = -std=c++11 -Wall  # -Wall muestra todos los warnings

# Archivos fuente y objetos
SRC = numeric_laser.cpp simulation_parameters.cpp
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable final
EXEC = simulation

# La regla principal: cómo construir el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regla para compilar archivos .cpp a archivos .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Limpiar los archivos generados
clean:
	rm -f $(OBJ) $(EXEC)