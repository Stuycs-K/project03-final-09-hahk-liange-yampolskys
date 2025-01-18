.PHONY: compile run clean
<<<<<<< HEAD
compile main: main.o node.o library.o file.o music_player.o player.o
	@gcc -o main main.o node.o library.o file.o music_player.o player.o
=======
compile main: main.o node.o library.o file.o player.o music_player.o
	@gcc -o main main.o node.o library.o file.o player.o music_player.o
>>>>>>> c3cf160d7ce0f4bbbf835e60136bf8551b892373

main.o: main.c node.h library.h file.h music_player.h player.h
	@gcc -c main.c

node.o: node.c node.h
	@gcc -c node.c

library.o: library.c library.h
	@gcc -c library.c

file.o: file.c file.h
	@gcc -c file.c

<<<<<<< HEAD
music_play.o: music_player.c music_player.h
	@gcc -c music_player.c

player.o: player.c player.h
	@gcc -c player.c

=======
player.o: player.c player.h
	@gcc -c player.c

music_player.o: music_player.c music_player.h
	@gcc -c music_player.c

>>>>>>> c3cf160d7ce0f4bbbf835e60136bf8551b892373
run: main
	@./main

clean:
	@rm -rf *.o main
