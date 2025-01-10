#include "music_player.h"

void check_mpg123() {

}

void play_file(char * file_name) {
  pid_t p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    system("mpg123 -R < to_player > from_player"); // will probably switch to execvp and redirection
    printf("finished playing.");
  } else {
    printf("currently playing...\n");
    int to_player = open("to_player", O_WRONLY, 0);
    int from_player = open("from_player", O_RDONLY, 0);
    char buff[1000];
    sprintf(buff, "L %s\n", file_name);
    write(to_player, buff, 1000);
    while (1) {
        read(from_player, buff, 100);
        //printf("%s\n", buff);
        if (buff[1] == 'P' && buff[3] == '0') break;
    }
    close(to_player);
    close(from_player);
    printf("test\n");
  }
}

int main() {
  mkfifo("to_player", 0777);
  mkfifo("from_player", 0777);
  play_file("./beep-test.mp3");
  remove("to_player");
  remove("from_player");
  return 0;
}
