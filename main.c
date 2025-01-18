#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "file.h"

#define list_name "playlist.txt"

int main(){
  struct song_node **library = init();
  int option = 0;
  char input[100];
  while(option != 12){
    printf("\n__________________________\n");
    printf("\nMenu:\n");
    printf("1. Load & view playlist\n");
    printf("2. Play\n");
    printf("3. Play a song\n");
    printf("4. Skip song\n"); //here too
    printf("5. Add song\n");
    printf("6. Remove song\n");
    printf("7. Look up a song\n");
    printf("8. Look up an artist\n");
    printf("9. Loop playlist\n"); //i think this is another person's funciton
    printf("10. Create new playlist\n");
    printf("11. Delete playlist\n");
    printf("12. Save and exit\n");
    printf("Choose an option: ");

    if(fgets(input, sizeof(input), stdin)){
        option = 0;
        for(int i = 0; input[i] >= '0' && input[i] <= '9'; i++){
            option = option*10 + (input[i] - '0');
        }
    }

    if(option == 1){ //load & view
      printf("\nViewing playlist:\n");
      print_library(library);
    }

    else if(option == 2) //play
      if(library != NULL && numFilled(library) > 0){
        struct song_node *first_song = library[0];
        if(first_song != NULL){
          printf("Playing: %s by %s\n", first_song->title, first_song->artist);
          playfile(first_song->title);
        }
      }
      else{
        printf("\nNo songs left to play\n");
      }

    }

    else if(option == 3){ //play specific song

      }

    else if(option == 4){ //skip song

    }


    else if(option == 5){ //add song
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

    else if(option == 6){ //remove song
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
      delete_song(library, artist, title);
      printf("\nSong removed.\n");
    }

    else if(option == 7){ //look up song
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

    else if(option == 8){ //look up artist
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

    else if(option == 9){ //loop playlist

    }

    else if(option == 10){ //create new playlist
    //  char list_name[100];
      printf("Enter playlist name: ");
      fgets(list_name, sizeof(list_name), stdin);
      save_library(library, list_name);
      printf("\n%s saved to playlists.\n", list_name);
      }

    else if(option == 11){ //delete playlist of choice
      char name[100];
      printf("Enter playlist name: ");
      if(fgets(name, sizeof(name), stdin)){
        int length = strlen(name);
        if(length > 0 && name[length - 1] == '\n'){

        }
      }

      printf("\n%s deleted.\n", name)
  }

    else if(option == 12){ //save and exit
      save_library(library, list_name);
      printf("\nPlaylist saved.\n");
      reset(library);
      free(library);
    }

    else{
      printf("\nInvalid option. Please try again.\n");
    }
  }

    return 0;
}
