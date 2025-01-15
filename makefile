.PHONY: compile run clean
compile main: main.o node.o library.o file.o
	@gcc -o main main.o node.o library.o file.o

main.o: main.c node.h library.h file.h
	@gcc -c main.c

node.o: node.c node.h
	@gcc -c node.c

library.o: library.c library.h
	@gcc -c library.c

file.o: file.c file.h
	@gcc -c file.c

run: main
	@./main

clean:
	@rm -rf *.o main
