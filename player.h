#ifndef PLAYER_H

#define PLAYER_H

static void sighandler(int signo);
struct song_node *skip(struct song_node *current);
struct song_node *shuffle_next(struct song_node **library);
void shuffle_play(struct song_node ** library);
void loop(struct song_node **library, struct song_node *song);
void queueSongs(struct song_node **library, struct song_node *queueHead);
void addToQueue(struct song_node **queueHead, struct song_node *newSong);
#endif
