#include "music_player.h"

void check_mpg123() {

}

void play_file(char * file_name) {
  pid_t p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    char * args[] = {"mpg123", "-q", file_name, NULL};
    execvp(args[0], args);
  } else {
    printf("currently playing...\n");
  }
}

int main() {
  play_file("./beep-test.mp3");
  return 0;
}
