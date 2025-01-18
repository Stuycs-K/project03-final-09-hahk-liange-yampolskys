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
#include <string.h>

struct frame_info {
  int frames;
  int frames_left;
  float seconds;
  float seconds_left;
};

<<<<<<< HEAD
extern int to_player;
extern int from_player; //searched up; extern basically defines variables in single c file
extern char buff[1000];
void check_mpg123();
=======
int to_player, from_player;
char buff[1000];
>>>>>>> c3cf160d7ce0f4bbbf835e60136bf8551b892373
void connect_player();
int player_setup();
void disconnect_player();
void read_player(char * b);
void write_player(char * b);
void play_file(char * file_name);
void pause_playback();
void stop_playback();
void jump_absolute(float seconds);
void jump_relative(float seconds);
void set_volume(float percent);
int check_finished_playing(char * b);
<<<<<<< HEAD
int get_to_player();
int get_from_player();
char* get_buff();
=======
struct frame_info * check_frame_info(char * b);
>>>>>>> c3cf160d7ce0f4bbbf835e60136bf8551b892373

#endif
