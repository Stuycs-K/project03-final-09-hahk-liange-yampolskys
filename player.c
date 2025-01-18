#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "music_player.h"

//handle signals
void sighandler(int signo) {
    if (signo == SIGINT) {
        printf("\nTerminating playback...\n");
        disconnect_player();
        kill(0, SIGKILL); // b/c when ctrl+c, child processes arent killed 
        exit(0);
    }
}

//helper
struct song_node* shuffleNext(struct song_node **library) {
    int bucket = rand() % 27;
    return chooseRandom(library[bucket]);
}

//play songs in shuffled order
//forks
void shufflePlay(struct song_node **library) {
    struct song_node *current;
    signal(SIGINT, sighandler);

    while (1) {
        current = shuffleNext(library);
        if (current) {
           interactive_player(current->filename, current->artist, current->title);
        } else {
            printf("No songs available.\n");
            break;
        }
    }
}

//play the same song on repeat
void loop(struct song_node **library, struct song_node *song) {
    signal(SIGINT, sighandler);

    while (1) {
        interactive_player(song->filename, song->artist, song->title);
    }
}

//play a list with queued songs
void queueSongs(struct song_node **library, struct song_node *queueHead) {
    struct song_node *current = queueHead;
    signal(SIGINT, sighandler);

    while (current) {
        interactive_player(current->filename, current->artist, current->title);
        current = current->next;
    }
}

//add songs to queue
void addToQueue(struct song_node **queueHead, struct song_node *newSong) {
    struct song_node *current = *queueHead;

    if (!newSong) {
        printf("Invalid song. Cannot add to queue.\n");
        return;
    }

    struct song_node *songToAdd = malloc(sizeof(struct song_node));
    if (!songToAdd) {
        perror("Failed to allocate memory for the new song in the queue");
        return;
    }

    strcpy(songToAdd->title, newSong->title);
    strcpy(songToAdd->artist, newSong->artist);
    strcpy(songToAdd->filename, newSong->filename);
    songToAdd->next = NULL;

    if (!*queueHead) {
        *queueHead = songToAdd;
    } 
    else {
        while (current->next) {
            current = current->next;
        }
        current->next = songToAdd;
    }
}
