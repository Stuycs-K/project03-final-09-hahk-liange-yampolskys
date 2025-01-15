#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "file.h"

//#define list_name "playlist.txt"

int main(){
  struct song_node **library = init();
  int option = 0;
  char input[100];
  while(option != 9){
    printf("\n__________________________\n");
    printf("\nMenu:\n");
    printf("1. View playlist\n");
    printf("2. Play\n");
    printf("3. Play a song\n");
    printf("4. Add a song\n");
    printf("5. Look up a song\n");
    printf("6. Look up an artist\n");
    printf("7. Create new playlist\n");
    printf("8. Delete playlist\n");
    printf("9. Save and exit\n");
    printf("Choose an option: ");

    if(fgets(input, sizeof(input), stdin)){
        option = 0;
        for(int i = 0; input[i] >= '0' && input[i] <= '9'; i++){
            option = option*10 + (input[i] - '0');
        }
    }

    if(option == 1){ //view
      printf("\nViewing playlist:\n");
      print_library(library);
    }

    else if(option == 2){ //play

    }

    else if(option == 3){ //play specific song

      }

    else if(option == 4){ //add song
      char artist[100];
      char title[100];
      printf("Enter artist: ");
      if(fgets(artist, sizeof(artist), stdin)){
          int length = strlen(artist);
          if(length > 0 && artist[length - 1] == '\n'){
              artist[length-1] = '\0';
          }
      }
      printf("Enter title: ");
      if(fgets(title, sizeof(title), stdin)){
          int length = strlen(title);
          if(length > 0 && title[length-1] == '\n'){
              title[length-1] = '\0';
          }
      }
      add(library, artist, title);
      printf("\nSong added.\n");
    }

    else if(option == 5){ //look up song
      char artist[100];
      char title[100];
      printf("Enter artist: ");
      if(fgets(artist, sizeof(artist), stdin)){
        int length = strlen(artist);
        if(length > 0 && artist[length-1] == '\n'){
          artist[length - 1] = '\0';
        }
      }
      printf("Enter title: ");
      if(fgets(title, sizeof(title), stdin)){
          int length = strlen(title);
          if(length > 0 && title[length-1] == '\n'){
              title[length-1] = '\0';
          }
      }
      struct song_node *song = search_song(library, artist, title);
      if(song){
        printf("\nFound %s by %s.\n", song->title, song->artist);
      }
      else{
        printf("\nSong not found.\n");
      }
    }

    else if(option == 6){ //look up artist
      char artist[100];
      printf("Enter artist: ");
      if(fgets(artist, sizeof(artist), stdin)){
        int length = strlen(artist);
          if(length > 0 && artist[length - 1] == '\n'){
            artist[length -1] = '\0';
          }
      }
      printf("\nSongs by %s:\n", artist);
      print_artist(library, artist);
    }

    else if(option == 7){ //create new playlist
      char list_name[100];
      fgets(list_name, sizeof(list_name), stdin);
      printf("Enter playlist name: ");

      save_library(library, list_name);
      printf("\n%s saved to playlists.\n", list_name);
      }

    else if(option == 8){ //delete playlist of choice

      }

    else if(option == 9){ //save and exit
      save_library(library, list_name);
      printf("\nPlaylist saved.\n");
      reset(library);
      free(library);
    }

    else{
      printf("\nInvalid option. Please try again.\n");
    }
  }





    /*
    add(library, "The Beatles", "Hey Jude");
    add(library, "RHCP", "Can't Stop");
    add(library, "The Beatles", "Let It Be");
    add(library, "Pink Floyd", "Comfortably Numb");
    add(library, "The Rolling Stones", "Paint It Black");
    add(library, "Pink Floyd", "Wish You Were Here");

    printf("Music Library:\n");
    print_library(library);

    char *filename = "library.txt";
    printf("\nSaving library to '%s'...\n", filename);
    save_library(library, filename);

    reset(library);

    printf("\nLoading library from '%s'...\n", filename);
    load_library(library, filename);

    printf("\nLoaded Music Library:\n");
    print_library(library);

    reset(library);
*/
    return 0;
}
