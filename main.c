#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "file.h"
#include "music_player.h"
#include "player.h"
#define default_list "playlist.txt"

int main(){
  signal(SIGINT, sighandler);
  struct song_node **library = init();
  char list_name[100] = default_list;
  load_library(library, list_name);
  int player = player_setup();
  int option = 0;
  char input[100];
  struct song_node *curr_song = NULL;

  while(option != 12){
    printf("\n__________________________\n");
    printf("\nMenu:\n");
    printf("1. Load & view playlist\n");
    printf("2. Look up a song\n");
    printf("3. Look up an artist\n");
    printf("4. Play a song\n");
    printf("5. Add song\n");
    printf("6. Remove song\n");
    printf("7. Play\n");
    printf("8. Shuffle playlist\n"); 
    printf("9. Loop playlist\n"); 
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
      char new_list[100];
      printf("\nCurrent playlist: %s\n", list_name);
      print_library(library);
      printf("\nEnter name of the playlist to load: ");
      if(fgets(new_list, sizeof(new_list), stdin)){
        int length = strlen(new_list);
        if(length > 0 && new_list[length - 1] == '\n'){
          new_list[length - 1] = '\0';
        }
      }
      if(strlen(new_list) == 0){
        printf("No name provided.\n");
      }
      else if(strlen(new_list) > 0){
        struct stat stat_buffer;
        if(stat(new_list, &stat_buffer) == 0){ 
          strncpy(list_name, new_list, sizeof(list_name));
          reset(library); 
          load_library(library, list_name); 
          printf("\nLoaded playlist: %s\n", list_name);
          print_library(library);
        } 
        else{ 
          printf("\nPlaylist does not exist.\n");
        }
      }
    }

    else if(option == 2){ //look up song
      char artist[100];
      char title[100];
      char filename[100];
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
      printf("Enter filename: ");
      if(fgets(filename, sizeof(filename), stdin)){
          int length = strlen(filename);
          if(length > 0 && filename[length-1] == '\n'){
              filename[length-1] = '\0';
          }
      }
      struct song_node *song = search_song(library, artist, title, filename);
      if(song){
        printf("\nFound %s by %s.\n", song->title, song->artist);
      }
      else{
        printf("\nSong not found.\n");
      }
    }

    else if(option == 3){ //look up artist
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

   else if(option == 4){ //play specific song
      char artist[100];
      char title[100];
      char filename[100];
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
      printf("Enter filename: ");
      if(fgets(filename, sizeof(filename), stdin)){
          int length = strlen(filename);
          if(length > 0 && filename[length-1] == '\n'){
              filename[length-1] = '\0';
          }
      }
      struct song_node *song = search_song(library, artist, title, filename);
      if(song != NULL){
        interactive_player(song->filename, song->artist, song->title);
      }
      else{
        printf("\nSong not found.\n");
      }
    }

    else if(option == 5){ //add song
      char artist[100];
      char title[100];
      char filename[100];
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
      printf("Enter filename: ");
      if(fgets(filename, sizeof(filename), stdin)){
          int length = strlen(filename);
          if(length > 0 && filename[length-1] == '\n'){
              filename[length-1] = '\0';
          }
      }
      add(library, artist, title, filename);
      save_library(library, list_name);
      printf("\nSong added.\n");
    }

    else if(option == 6){ //remove song
      char artist[100];
      char title[100];
      char filename[100];
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
      printf("Enter filename: ");
      if(fgets(filename, sizeof(filename), stdin)){
          int length = strlen(filename);
          if(length > 0 && filename[length-1] == '\n'){
              filename[length-1] = '\0';
          }
      }
      delete_song(library, artist, title, filename);
      save_library(library, list_name);
      reset(library);
      load_library(library, list_name);
      printf("\nSong removed.\n");
    }

    else if(option == 7){ //play
      curr_song = library[0];
      if(curr_song){
        interactive_player(curr_song->filename, curr_song->artist, curr_song->title);
      }
      else{
        printf("\nNo songs left to play\n");
      }
    } 

    else if(option == 8){//shuffle playlist
      shufflePlay(library); 
    }

    else if(option == 9){ //loop playlist
      if(curr_song){
        loop(library, curr_song);
      }
      else{
        printf("\nNo song to loop\n");
      }
    } 

    else if(option == 10){ //create new playlist
      char new_list[100];
      printf("Enter new playlist name: ");
      if(fgets(new_list, sizeof(new_list), stdin)){
        int length = strlen(new_list);
        if(length > 0 && new_list[length - 1] == '\n'){
          new_list[length -1] = '\0';
        }
      }
      if(strlen(new_list) > 0){
        strncpy(list_name, new_list, sizeof(list_name));
        reset(library);
        save_library(library, list_name);
        printf("\n%s created.\n", list_name);
      } 
      else{
        printf("\nPlaylist name cannot be empty.\n");
      }    
    }

    else if(option == 11){ //delete playlist of choice
      printf("Enter playlist name to delete: ");
      if(fgets(list_name, sizeof(list_name), stdin)){
        int length = strlen(list_name);
        if(length > 0 && list_name[length - 1] == '\n'){
          list_name[length - 1] = '\0';
        }
      }
      remove(list_name);
      printf("\n%s deleted.\n", list_name);
    }

    else if(option == 12){ //save and exit
      save_library(library, list_name);
      printf("\nPlaylist saved.\n");
      reset(library);
      free(library);
      if(player){
        disconnect_player();
      }
      kill(0, SIGKILL);
      printf("\nClosing...\n");
    }

    else{
        printf("\nInvalid option. Please try again.\n");
      }
    }


    return 0;
  }
