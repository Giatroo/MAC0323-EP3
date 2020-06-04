CC = g++
FLAGS = -Wall -g -O0
OBJ = ./obj

all : main
	@echo "Compilado corretamente"

main : main.o myGraph.o
	${CC} $^ ${FLAGS} -o $@

main.o : main.cpp
	${CC} -c $< ${FLAGS} -o $@

myGraph.o : myGraph.cpp myGraph.hpp
	${CC} -c $< ${FLAGS} -o $@
