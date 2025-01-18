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
        kill(0, SIGKILL);
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

// Fisher-Yates shuffle helper function
void fisherYatesShuffle(struct song_node **array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct song_node *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//play songs in shuffled order
//forks
void shufflePlay(struct song_node **library) {
    struct song_node *songArray[1000];
    int count = 0;

    for (int i = 0; i < 27; i++) {
        struct song_node *current = library[i];
        while (current) {
            songArray[count++] = current;
            current = current->next;
        }
    }

    if (count == 0) {
        printf("No songs available.\n");
        return;
    }

    fisherYatesShuffle(songArray, count);

    signal(SIGINT, sighandler);

    for (int i = 0; i < count; i++) {
        printf("Now playing: %s - %s\n", songArray[i]->artist, songArray[i]->title);
        play_file(songArray[i]->filename);

        do {
            read_player(buff);
        } while (!check_finished_playing(buff));
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
