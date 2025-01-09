#include "music_player.h"

void check_mpg123() {

}

void play_file(char * file_name) {
  pid_t p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    //char * args[] = {"mpg123", "-q", file_name, NULL};
    //int ret = execvp(args[0], args);
    char buff[1000];
    sprintf(buff, "mpg123 -q %s > /dev/null 2>&1", file_name);
    system(buff);
    printf("finished playing.");
  } else {
    printf("currently playing...\n");
  }
}

int main() {
  play_file("./beep-test.mp3");
  return 0;
}
