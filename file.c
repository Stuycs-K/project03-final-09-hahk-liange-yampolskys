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
      write(musicFile,"|" , 1);
      write(musicFile, curr->title, strlen(curr->title));
      write(musicFile,"|", 1);
      write(musicFile, curr->filename, strlen(curr->filename));
      write(musicFile,"\n" , 1);
      curr = curr->next;
    }
  }

  close(musicFile);
  //printf("Library saved to %s\n", filename);
}

void load_library(struct song_node ** library, char *filename){
  char line[256], buffer[1];
  int index = 0;
  int bytes = 0;
  int list;
  int musicFile = open(filename, O_RDONLY);
  if(musicFile == -1){
    perror("No library detected. New library created\n");
    return;;
  }

  while((bytes = read(musicFile, buffer, 1)) > 0){
    if(buffer[0] == '\n' || index >= sizeof(line) - 1){
      line[index] = '\0';

      char *line_pointer = line;
      char *artist = strsep(&line_pointer, "|");
      char *title = strsep(&line_pointer, "|");
      char *filename = strsep(&line_pointer, "|");
      if(artist && title && filename){
        while(*artist == ' '){
          artist++;
        }
        while(*title == ' '){
          title++;
        }
        while(*filename == ' '){
          filename++;
        }
        if(artist[0] >= 'A' && artist[0] <= 'Z'){
          list = artist[0] - 'A';
        }
        else{
          list = 26;
        }
        library[list] = insert_alph(library[list], artist, title, filename);
      }
      index = 0;
    }
    else{
      line[index++] = buffer[0];
    }
  }

  close(musicFile);
  //printf("Library loaded from %s", filename);
}

void add_library(struct song_node **library, char *artist, char *title){
    int list;
    if(artist[0] >= 'A' && artist[0] <= 'Z'){
      list = artist[0] - 'A';
    }
    else{
      list = 26;
    }

    library[list] = insert_alph(library[list], artist, title, NULL);
    printf("Song added: %s , %s\n", artist, title);
}

//Saving files, adding files, reading files.
