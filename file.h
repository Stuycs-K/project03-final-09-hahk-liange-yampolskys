#ifndef FILE_H
#define FILE_H
#include "node.h"

struct song_node **init();
void save_library(struct song_node ** library, char *filename);
void load_library(struct song_node **library, char *filename);
//void load_library(struct song_node ** library, char *filename);
void add_library(struct song_node ** library, char *artist, char *filename);
int file_exists(char *file);
#endif
