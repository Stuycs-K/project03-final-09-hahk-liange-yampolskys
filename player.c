#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "music_player.h"
//reused music library code, modified nodes to hold files, ask for artist + title so most functions still work
//maybe a default?

//write basic placeholders for now, modify node + library code to actually work
struct song_node skip(struct song_node song ){
	return song -> next;
}

struct song_node shuffle_next(struct song_node ** library){
	struct song_node start = chooseRandom(library[0]);
	return start;
}

void shuffle(struct song_node ** library){
	while(1){
		file = struct song_node
		play_file()
	}
}

static void sighandler(int signo) {
    if ( signo ==  ){
    
          }
  }
