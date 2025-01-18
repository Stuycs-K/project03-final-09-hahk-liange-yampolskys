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
static void sighandler(int signo) {
    if (signo == SIGINT) {
        printf("\nTerminating playback...\n");
        exit(0);
    }
}

//return the filename of the next song
//call play_file(skip(current))
char* skip(struct song_node *current) {
    if (current && current->next) {
        return current->next->filename;
    }
    return NULL;
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
    pid_t playerPid;

    signal(SIGINT, sighandler);

    while (1) {
        current = shuffleNext(library);
        if (current) {
            printf("Now playing: %s - %s\n", current->artist, current->title);
            playerPid = fork();
            if (playerPid == 0) {
                play_file(current->filename);
                exit(0);
            } 
            else if (playerPid > 0) {
                int status;
                waitpid(playerPid, &status, 0);
            } 
            else {
                perror("Fork failed");
                return;
            }
        } 
        else {
            printf("No songs available.\n");
            break;
        }
    }
}

//play the same song on repeat
void loop(struct song_node **library, struct song_node *song) {
    pid_t playerPid;

    signal(SIGINT, sighandler);

    while (1) {
        playerPid = fork();
        if (playerPid == 0) {
            play_file(song->filename);
            exit(0);
        } 
        else if (playerPid > 0) {
            int status;
            waitpid(playerPid, &status, 0);
        } 
        else {
            perror("Fork failed");
            return;
        }
    }
}

//play a list with queued songs
void queueSongs(struct song_node **library, struct song_node *queueHead) {
    struct song_node *current = queueHead;
    pid_t playerPid;

    signal(SIGINT, sighandler);

    while (current) {
        playerPid = fork();
        if (playerPid == 0) {
            play_file(current->filename);
            exit(0);
        } 
        else if (playerPid > 0) {
            int status;
            waitpid(playerPid, &status, 0);
            current = current->next;
        } 
        else {
            perror("Fork failed");
            return;
        }
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