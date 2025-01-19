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
#include <termios.h>

#define END 0 // end of song is reached
#define SKIP 1 // song is skipped
#define QUIT 2 // user quits

struct frame_info {
  int frames;
  int frames_left;
  float seconds;
  float seconds_left;
};

extern int to_player;
extern int from_player; //searched up; extern basically defines variables in single c file
extern char buff[1000];
extern float volume;
void check_mpg123();
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
char * check_error(char * b);
struct frame_info * check_frame_info(char * b);
int interactive_player(char * file_name, char * artist, char * title);
int get_to_player();
int get_from_player();
char* get_buff();

#endif
