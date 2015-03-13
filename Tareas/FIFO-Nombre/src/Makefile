#    Makefile - Desarrollo de Aplicaciones en Red Servidor
#    all	- Compilar todo
#    clean	- Limpiar archivos compilados
#    lectura	- Compilar lectura

BIN = ../bin
EXECUTABLES = lectura getUUID
# Agregar cabeceras .h
INCLUDES = 
#Usar gcc
GCC = gcc 
#Bibliotecas
LIBS = -lm -lpthread -lpam
#FLAGS =  -std=c99
CFLAGS = -I.

#'make all' creará todos los ejecutables
all: 	$(EXECUTABLES)

#'make clean' eleminar archivos objetos
clean:
	rm -f $(BIN)/lectura *.o

# Compilar los archivos .c
%.o:%.c $(INCLUDES) 
	$(GCC) $(FLAGS) $(CFLAGS) -c $<

# Generar ejecutables individuales
lectura: lectura.o
	$(GCC) $(FLAGS) $(CFLAGS) -o $(BIN)/lectura lectura.o $(LIBS)
getUUID: getUUID.o
	$(GCC) $(FLAGS) $(CFLAGS) -o $(BIN)/getUUID getUUID.o $(LIBS)

