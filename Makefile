all : main.cpp automata.o
	g++ -g -o  main automata.o main.cpp

automata.o : automata.cpp automata.h
	g++ -g -c automata.cpp

clean: rm *.o main

.PHONY: all clean