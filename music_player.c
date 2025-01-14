#include "music_player.h"

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

void pause_playback() {
  write_player("P\n");
}

void stop_playback() {
  write_player("S\n");
}

void jump_absolute(float seconds) {
  sprintf(buff, "J %fs\n", seconds);
  write_player(buff);
}

void jump_relative(float seconds) {
  sprintf(buff, seconds > 0 ? "J +%fs\n" : "J -%fs\n", seconds);
  write_player(buff);
}

void set_volume(float percent) {
  sprintf(buff, "V %f\n", percent);
  write_player(buff);
}

int check_finished_playing(char * b) {
  return b[1] == 'P' && b[3] == '0';
}

struct frame_info check_frame_info(char * b) {
  struct frame_info ret;
  if (b[1] != 'F') return ret;
  sscanf(b, "@F %d %d %f %f", (int *)&ret, (int *)&ret + 1, (float *)&ret + 2, (float *)&ret + 3);
  return ret;
}

int main() {
  int is_main = player_setup();
  if (is_main) {
    play_file("./beep-test.mp3");
    while (1) {
        read_player(buff);
        if (check_finished_playing(buff)) break;
        struct frame_info r = check_frame_info(buff);
        printf("f %d %d %f %f\n", r.frames, r.frames_left, r.seconds, r.seconds_left);
    }
    disconnect_player();
  }
  return 0;
}
