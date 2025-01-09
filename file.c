#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "node.h"
#include "library.h"
#include "file.h"

// save_library(library, "text.txt")
void save_library(struct song_node ** library, char *filename){
  int musicFile = open(filename, O_WRONLY | O_CREAT| O_TRUNC, 0644);
  if(musicFile == -1){
    perror("open file failed");
    exit(1);
  }

  for(int i = 0; i < 27; i++){
    struct song_node *curr = library[i];
    while(curr){
      write_file(musicFile, curr);
      curr = curr->next;
    }
  }

  close(musicFile);
}

void load_library(struct song_node ** library, int num){
  int fd =
}

void add_library(struct song_node ** library, int num){

}


//Saving files, adding files, reading files.
