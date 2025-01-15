#ifndef PLAYER_H

#define PLAYER_H

static void sighandler(int signo);
struct song_node *skip(struct song_node *current);
struct song_node *shuffle_next(struct song_node **library);
void shuffle_play(struct song_node ** library);

#endif
