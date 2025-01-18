#include "music_player.h"

int to_player;
int from_player;
char buff[1000];

void check_mpg123() {

}

void connect_player() {
  to_player = open("to_player", O_WRONLY, 0);
  from_player = open("from_player", O_RDONLY, 0);
}

int player_setup() {
  pid_t p = fork();
  mkfifo("to_player", 0777);
  mkfifo("from_player", 0777);
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    system("mpg123 -R < to_player > from_player"); // will probably switch to execvp and redirection
    return 0;
  } else {
    connect_player();
    return 1;
  }
}

void disconnect_player() {
  close(to_player);
  close(from_player);
  remove("to_player");
  remove("from_player");
}

void read_player(char * b) {
    read(from_player, b, sizeof(b));
}

void write_player(char * b) {
  write(to_player, b, 1000);
}

void play_file(char * file_name) {
  sprintf(buff, "L %s\n", file_name);
  write_player(buff);
}

int check_finished_playing(char * b) {
  return b[1] == 'P' && b[3] == '0';
}

int get_to_player(){
  return to_player;
}

int get_from_player(){
  return from_player;
}

char* get_buff(){
  return buff;
}

/*
int main() {
  int is_main = player_setup();
  if (is_main) {
    play_file("./beep-test.mp3");
    while (1) {
        read_player(buff);
        if (check_finished_playing(buff)) break;
    }
    disconnect_player();
  }
  return 0;
}
*/