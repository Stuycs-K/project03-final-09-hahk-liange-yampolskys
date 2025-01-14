#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "music_player.h"


static void sighandler(int signo) {
	 if (signo == SIGINT) {
        printf("\nTerminating playback...\n");
        exit(0);
    }
}

char* skip(struct song_node *current) {
    if (current) {
        return current->next->filename;
    }
    return NULL;
}
char *shuffle_next(struct song_node **library) {
    int bucket = rand() % 27;
    return chooseRandom(library[bucket])->filename;
}

void shuffle_play(struct song_node **library) {
//wait is this compatible with group code? discuss.
    struct song_node *current;
    pid_t player_pid;

    signal(SIGINT, sighandler);

    while (1) {
        current = shuffle_next(library);
        if (current) {
            printf("Now playing: %s - %s\n", current->artist, current->title);
            player_pid = fork();
            if (player_pid == 0) {
                play_file(current);
                exit(0);
            }
             else {
                perror("Fork failed");
                return;
            }
        } else {
            printf("No songs available.\n");
            break;
        }
    }
void loop(struct song_node ** library, struct song_node song){
	pid_t player_pid;
	signal(SIGINT, sighandler);
	printf("looping %s - %s\n", song->artist, song->title);
	while(1){
		 player_pid = fork();
            if (player_pid == 0) {
                play_file(song->filename);
                exit(0);
            }
             else {
                perror("Fork failed");
                return;
            }
	}
		
}

//queueing songs:
/*
can add songs to queue while playing
when songs are added, first queue method is called, then when queue is finished, calls shuffle
*/
void queue_songs(struct song_node **library, struct song_node song){
	
}
