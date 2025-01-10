#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "music_player.h"

static int pause_flag = 0;

static void sighandler(int signo) {
    if (signo == SIGUSR1) {
        pause_flag = !pause_flag;
    } else if (signo == SIGINT) {
        printf("\nTerminating playback...\n");
        exit(0);
    }
}

void play_file(char *filename) {
    char *args[] = {"mpg123", filename, NULL};
    execvp("mpg123", args);
    perror("Error: execvp failed");
    exit(1);
}

struct song_node *skip(struct song_node *current) {
    if (current) {
        return current->next;
    }
    return NULL;
}

struct song_node *shuffle_next(struct song_node **library) {
    int bucket = rand() % 27;
    return chooseRandom(library[bucket]);
}

void shuffle_play(struct song_node **library) {
    struct song_node *current;
    pid_t player_pid;

    signal(SIGUSR1, sighandler);
    signal(SIGINT, sighandler);

    while (1) {
        current = shuffle_next(library);
        if (current) {
            printf("Now playing: %s - %s\n", current->artist, current->title);
            player_pid = fork();
            if (player_pid == 0) {
                play_file(current->filename);
                exit(0);
            } else if (player_pid > 0) {
                while (1) {
                    if (pause_flag) {
                        kill(player_pid, SIGSTOP);
                        while (pause_flag) {
                            pause();
                        }
                        kill(player_pid, SIGCONT);
                    }
                    int status;
                    if (waitpid(player_pid, &status, WNOHANG) > 0) {
                        break;
                    }
                }
            } else {
                perror("Fork failed");
                return;
            }
        } else {
            printf("No songs available.\n");
            break;
        }
    }
}
