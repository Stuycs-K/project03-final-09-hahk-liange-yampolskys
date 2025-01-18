.PHONY: compile run clean
compile main: main.o node.o library.o file.o music_player.o player.o
	@gcc -o main main.o node.o library.o file.o music_player.o player.o

main.o: main.c node.h library.h file.h music_player.h player.h
	@gcc -c main.c

node.o: node.c node.h
	@gcc -c node.c

library.o: library.c library.h
	@gcc -c library.c

file.o: file.c file.h
	@gcc -c file.c

music_play.o: music_player.c music_player.h
	@gcc -c music_player.c

player.o: player.c player.h
	@gcc -c player.c

run: main
	@./main

clean:
	@rm -rf *.o main
