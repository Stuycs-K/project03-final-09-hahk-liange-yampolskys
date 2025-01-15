#include <stdio.h>
#include <stdlib.h>
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
    perror("open file failed (save)");
    exit(1);
  }

  for(int i = 0; i < 27; i++){
    struct song_node *curr = library[i];
    while(curr){
      write(musicFile, curr->artist, strlen(curr->artist));
      write(musicFile,"-" , 1);
      write(musicFile, curr->title, strlen(curr->title));
      write(musicFile,"\n" , 2);
      curr = curr->next;
    }
  }

  close(musicFile);
}

void load_library(struct song_node ** library, char *filename){
  char artist[100], title[100];
  struct song_node temp;
  int bytes, index;
  int musicFile = open(filename, O_RDONLY);
  if(musicFile == -1){
    perror("open file fail (load)");
    exit(1);
  }

  while((bytes = read(musicFile, artist, sizeof(artist)-1)) > 0){
    artist[bytes] = '\0';

    bytes = read(musicFile, title, sizeof(title)-1);
    if(bytes <= 0){
      break;
    }
    title[bytes] = '\0';

    if(artist[0] >= 'A' && artist[0] <= 'Z'){
      index = artist[0] - 'A';
    }
    else{
      index = 26;
    }

    library[index] = insert_alph(library[index], artist, title);
  }

  close (musicFile);
}

void add_library(struct song_node **library, char *filename){
    int musicFile = open(filename, O_RDONLY, 0644);
    int bytes;
    int char artist[100], title[100];
    if(musicFile == -1){
      perror("open musicfile fail");
      exit(1);
    }


}

//Saving files, adding files, reading files.
