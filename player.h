#ifndef PLAYER_H
#define PLAYER_H

void sighandler(int signo);
char* skip(struct song_node *current);
void fisherYatesShuffle(struct song_node **array, int size);
void shufflePlay(struct song_node ** library);
void loop(struct song_node **library, struct song_node *song);
void queueSongs(struct song_node **library, struct song_node *queueHead);
void addToQueue(struct song_node **queueHead, struct song_node *newSong);

#endif
