.PHONY: compile run clean
compile main: main.o node.o library.o file.o player.o music_player.o
	@gcc -o main main.o node.o library.o file.o player.o music_player.o

main.o: main.c node.h library.h file.h
	@gcc -c main.c

node.o: node.c node.h
	@gcc -c node.c

library.o: library.c library.h
	@gcc -c library.c

file.o: file.c file.h
	@gcc -c file.c

player.o: player.c player.h
	@gcc -c player.c

music_player.o: music_player.c music_player.h
	@gcc -c music_player.c

run: main
	@./main

clean:
	@rm -rf *.o main
