#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

int to_player, from_player;
char buff[1000];
void check_mpg123();
void connect_player();
int player_setup();
void disconnect_player();
void read_player(char * b);
void write_player(char * b);
void play_file(char * file_name);
int check_finished_playing(char * b);

#endif
