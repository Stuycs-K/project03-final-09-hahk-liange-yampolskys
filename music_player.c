#include "music_player.h"
#include "file.h"
int to_player;
int from_player;
char buff[1000];
float volume = 100;

void player_setup() {
  int to_fds[2], from_fds[2];
  pipe(to_fds);
  pipe(from_fds);
  pid_t p = fork();
  if (p < 0) {
    perror("fork fail");
    exit(1);
  } else if (p == 0) {
    char * args[] = {"mpg123", "-R", NULL};

    close(to_fds[WRITE]);
    if (dup2(to_fds[READ], STDIN_FILENO) == -1) {
      perror("redirection fail");
      exit(1);
    }
    close(to_fds[READ]);

    close(from_fds[READ]);
    if (dup2(from_fds[WRITE], STDOUT_FILENO) == -1) {
      perror("redirection fail");
      exit(1);
    }
    close(from_fds[WRITE]);

    execvp(args[0], args);
  } else {
    close(to_fds[READ]);
    to_player = to_fds[WRITE];
    close(from_fds[WRITE]);
    from_player = from_fds[READ];
  }
}

void disconnect_player() {
  close(to_player);
  close(from_player);
}

void read_player(char * b) {
  b[read(from_player, b, 1000)] = '\0';
}

void write_player(char * b) {
  write(to_player, b, strlen(b));
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
  sprintf(buff, seconds > 0 ? "J +%fs\n" : "J %fs\n", seconds);
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

char * check_error(char * b) {
  return b[1] == 'E' ? b + 3 : NULL;
}

int interactive_player(char * file_name, char * artist, char * title) {
  if(!file_exists(file_name)){
    printf("\nERROR: File '%s' does not exist.\n", file_name);
    return -1; 
  }

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
  char progress[51];
  progress[sizeof(progress) - 1] = '\0';
  float length = -1;
  int ret = END;
  do {
    FD_ZERO(&read_fds);
    FD_SET(from_player, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    buff[0] = '\0';
    select(from_player+1, &read_fds, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      char c = getchar();
      switch (c) {
        case ' ':
          paused = !paused;
          pause_playback();
          break;
        case 'a':
          jump_relative(-5);
          break;
        case 'd':
          jump_relative(5);
          break;
        case 'w':
          volume = volume >= 95 ? 100 : volume + 5;
          set_volume(volume);
          break;
        case 's':
          volume = volume <= 5 ? 0 : volume - 5;
          set_volume(volume);
          break;
        case 'e':
          ret = SKIP;
          stop_playback();
          break;
        case 'q':
          ret = QUIT;
          stop_playback();
          break;
        default:
          if (length != -1 && '0' <= c && c <= '9') jump_absolute((c - '0') / 10.f * length);
      }
    }
    if (FD_ISSET(from_player, &read_fds)) {
      read_player(buff);
      char * error = check_error(buff);
      if (error != NULL) {
        fprintf(stderr, "Error: %s\n", error);
        ret = QUIT;
        break;
      }
      struct frame_info * i = check_frame_info(buff);
      if (i != NULL) {
        float s = i->seconds;
        float sl = i->seconds_left;
        if (length == -1) length = s + sl;
        int is = (int)s;
        int isl = (int)sl;
        int f = (int)(s / length * (sizeof(progress) - 1) + .5);
        for (int j = 0; j < sizeof(progress) - 1; j++) progress[j] = j < f ? '#' : '-';
        printf("\x1b[1F\x1b[2K\x1b[1F\x1b[2KNow playing: %s - %s [VOLUME: %d%%] %s\n%d:%02d [%s] %d:%02d \n", artist, title, (int)volume, paused ? "[PAUSED]" : "", is/60, is%60, progress, isl/60, isl%60);
      }
    }
  } while (!check_finished_playing(buff));

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ret;
}

/*
int main() {
  player_setup();
  while (1) interactive_player("beep-test.mp3", "Artist", "Title");
  disconnect_player();
  return 0;
}
*/
