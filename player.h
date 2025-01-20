#ifndef PLAYER_H
#define PLAYER_H

void sighandler(int signo);
void fisherYatesShuffle(struct song_node **array, int size);
void shufflePlay(struct song_node ** library);
void loop(struct song_node **library, struct song_node *song);
void loop_list(struct song_node **library);
void loop_shuffled_list(struct song_node **library);
void queueSongs(struct song_node **library, struct song_node *queueHead);
void addToQueue(struct song_node **queueHead, struct song_node *newSong);

#endif
