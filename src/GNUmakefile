# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura: ALGORITMOS Y ESTRUCTURAS DE DATOS AVANZADAS
# Curso: 2º
# Práctica 4: Tabla hash
# Autor: Stephan Brommer Gutiérrez
# Correo: alu0101493497@ull.es
# Fecha: 31/03/2023
# Archivo GNUMakefile
#
# Historial de revisiones
# 15/03/2023 - Creación (primera versión) del código

CXX = g++
CXXFLAGS = -std=c++17 -g
LDFLAGS =

all: main

main: main.o usuario.o baseDatos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -rf *.o main usuario baseDatos ../doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;