#include "music_player.h"

void connect_player() {
  to_player = open("to_player", O_WRONLY, 0);
  from_player = open("from_player", O_RDONLY, 0);
}

int player_setup() {
  mkfifo("to_player", 0777);
  mkfifo("from_player", 0777);
  pid_t p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    char * args[] = {"mpg123", "-R", NULL};

    int inp = open("to_player", O_RDONLY);
    if (inp == -1 || dup2(inp, STDIN_FILENO) == -1) return 0;
    close(inp);

    int tar = open("from_player", O_WRONLY, 0);
    if (tar == -1 || dup2(tar, STDOUT_FILENO) == -1) return 0;
    close(tar);

    execvp(args[0], args);
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
  b[read(from_player, b, 1000)] = '\0';
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

struct frame_info * check_frame_info(char * b) {
  if (b[1] != 'F') return NULL;
  struct frame_info * ret = malloc(sizeof(struct frame_info));
  sscanf(b + 3, "%d %d %f %f", (int *)ret, (int *)ret + 1, (float *)ret + 2, (float *)ret + 3);
  return ret;
}

int interactive_player(char * file_name, char * artist, char * title) {
  printf("[ ] pause/resume, [a/d] jump left/right, [0-9] jump to position, [w/s] increase/decrease volume, [e] skip, [q] quit\nNow playing: %s - %s\n\n", artist, title);
  play_file(file_name);

  fd_set read_fds;

  // modify terminal options so that does not wait for enter key and does not output - only works on unix
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int paused = 0;
  char progress[50];
  do {
    FD_ZERO(&read_fds);
    FD_SET(from_player, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    select(from_player+1, &read_fds, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      switch (getchar()) {
        case ' ':
          paused = !paused;
          pause_playback();
          break;
      }
    }
    if (FD_ISSET(from_player, &read_fds)) {
      read_player(buff);
      struct frame_info * i = check_frame_info(buff);
      if (i != NULL) {
        float s = i->seconds;
        float sl = i->seconds_left;
        int is = (int)s;
        int isl = (int)sl;
        int f = (int)(s/(s+sl)*sizeof(progress)+.5);
        for (int j = 0; j < sizeof(progress); j++) progress[j] = j < f ? '#' : '-';
        printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2KNow playing %s - %s %s\n%d:%02d [%s] %d:%02d \n", artist, title, paused ? "[PAUSED]" : "", is/60, is%60, progress, isl/60, isl%60);
      }
    }
  } while (!check_finished_playing(buff));

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main() { // sample code to play audio and read info about it
  int is_main = player_setup();
  if (is_main) {
    /*play_file("./beep-test.mp3");
    while (1) {
        read_player(buff);
        if (check_finished_playing(buff)) break;
        struct frame_info * i = check_frame_info(buff);
        if (i != NULL) {
            struct frame_info r = *i;
            printf("%d frames, %d frames left, %f seconds, %f seconds left\n", r.frames, r.frames_left, r.seconds, r.seconds_left);
        }
    }*/
    interactive_player("./beep-test.mp3", "Artist", "Title");
    disconnect_player();
  }
  return 0;
}
