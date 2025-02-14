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
#define default_list "None"

int main(){
  signal(SIGINT, sighandler);
  struct song_node **library = init();
  char list_name[100] = "";
  load_library(library, list_name);
  player_setup();
  int option = 0;
  char input[100];
  struct song_node *curr_song = NULL;

  while(option != 14){
    printf("\n__________________________\n");
    printf("\nMenu:\n");
    printf("1. Load & view playlist\n");
    printf("2. Look up a song\n");
    printf("3. Look up an artist\n");
    printf("4. Play a song\n");
    printf("5. Loop song\n"); 
    printf("6. Add song\n");
    printf("7. Remove song\n");
    printf("8. Play\n");
    printf("9. Shuffle playlist\n"); 
    printf("10. Loop playlist\n"); 
    printf("11. Loop shuffled playlist\n");
    printf("12. Create new playlist\n");
    printf("13. Delete playlist\n");
    printf("14. Save and exit\n");
    printf("Choose an option: ");

    if(fgets(input, sizeof(input), stdin)){
        option = 0;
        for(int i = 0; input[i] >= '0' && input[i] <= '9'; i++){
            option = option*10 + (input[i] - '0');
        }
    }

    if(option == 1){ //load & view
      char new_list[100];
      if(strlen(list_name) == 0){
        printf("\nERROR: No playlist to view. Please load or create a playlist first.\n");
        printf("\nEnter name of the playlist to load: ");
        if(fgets(new_list, sizeof(new_list), stdin)){
          int length = strlen(new_list);
          if(length > 0 && new_list[length - 1] == '\n'){
            new_list[length - 1] = '\0';
          }
        }
        if(strlen(new_list) == 0){
          printf("\nERROR: Field(s) cannot be blank.\n");
        }
        else{
          struct stat stat_buffer;
          if(stat(new_list, &stat_buffer) == 0){
              strncpy(list_name, new_list, sizeof(list_name));
              reset(library);
              load_library(library, list_name);
              printf("\nLoaded playlist: %s\n", list_name);
              print_library(library);
            } 
          else{
              printf("\nERROR: Playlist does not exist.\n");
          }
        }
        continue;
      }
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
        printf("\nERROR: Field(s) cannot be blank.\n");
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
          printf("\nERROR: Playlist does not exist.\n");
        }
      }
    }

    else if(option == 2){ //look up song
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
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
      if(strlen(artist) == 0 || strlen(title) == 0 || strlen(filename) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
      }
      else{
        struct song_node *song = search_song(library, artist, title, filename);
        if(song){
          printf("\nFound %s by %s.\n", song->title, song->artist);
        }
        else{
          printf("\nERROR: Song not found.\n");
        }
      }
    }

    else if(option == 3){ //look up artist
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      char artist[100];
      printf("Enter artist: ");
      if(fgets(artist, sizeof(artist), stdin)){
        int length = strlen(artist);
        if(length > 0 && artist[length - 1] == '\n'){
          artist[length -1] = '\0';
        }
      }
      if(strlen(artist) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
      } 
      else{
    printf("\nSongs by %s:\n", artist);
    print_artist(library, artist);
}
    }

   else if(option == 4){ //play specific song
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
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
      if(strlen(artist) == 0 || strlen(title) == 0 || strlen(filename) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
      } 
      else{
        int index;
        if(artist[0] >= 'A' && artist[0] <= 'Z'){
          index = artist[0] - 'A';
        }
        else{
          index = 26;
        }

        struct song_node *song = find_song(library[index], artist, title, filename);
        if(song == NULL){
          printf("\nERROR: Song not found.\n");
        } 
        else{
          interactive_player(song->filename, song->artist, song->title);
        }
      }
    }

    else if(option == 5){ //loop song
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      char artist[100];
      char title[100];
      char filename[100];
      printf("Enter artist: ");
      if(fgets(artist, sizeof(artist), stdin)){
        int length = strlen(artist);
        if(length > 0 && artist[length - 1] == '\n'){
          artist[length - 1] = '\0';
        }
      }
      printf("Enter title: ");
      if(fgets(title, sizeof(title), stdin)){
        int length = strlen(title);
        if(length > 0 && title[length - 1] == '\n'){
          title[length - 1] = '\0';
        }
      }
      printf("Enter filename: ");
      if(fgets(filename, sizeof(filename), stdin)){
          int length = strlen(filename);
          if(length > 0 && filename[length-1] == '\n'){
              filename[length-1] = '\0';
          }
      }
      if(strlen(artist) == 0 || strlen(title) == 0 || strlen(filename) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
        continue;
      }
      struct song_node *song = search_song(library, artist, title, filename);
      if(!song){
        printf("\nERROR: Song not found.\n");
      } 
      else{
        loop(library, song);
      }
    } 

    else if(option == 6){ //add song
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
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
      if(strlen(artist) == 0 || strlen(title) == 0 || strlen(filename) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
      } 
      if(!file_exists(filename)){
        printf("\nERROR: The file '%s' does not exist.\n", filename);
        continue;
      }
      add(library, artist, title, filename);
      save_library(library, list_name);
      printf("\nSong added.\n");
      
    }


    else if(option == 7){ //remove song
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
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
      if(strlen(artist) == 0 || strlen(title) == 0 || strlen(filename) == 0){
        printf("\nERROR: Field(s) cannot be blank.\n");
      } 
      if(!search_song(library, artist, title, filename)){
        printf("\nERROR: Song does not exist.\n");
        continue;
      }
    
      delete_song(library, artist, title, filename);
      save_library(library, list_name);
      reset(library);
      load_library(library, list_name);
      printf("\nSong removed.\n");
      
    }

    else if(option == 8){ //play
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      struct song_node *queue = NULL;
      for(int i = 0; i < 27; i++){
        struct song_node *curr = library[i];
        while(curr){
          addToQueue(&queue, curr);
          curr = curr->next;
        }
      }
      if(queue){
        printf("\nPlaying playlist '%s'...\n", list_name);
        queueSongs(library, queue);
        free_list(queue); //frees after playback
      }
      else{
        printf("\nERROR: No songs left to play.\n");
      }
    } 

    else if(option == 9){//shuffle playlist
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      printf("\nPlaying %s in shuffled order...\n", list_name);
      shufflePlay(library); 
    }

    else if(option == 10){ //loop playlist
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      printf("\nLooping %s...\n", list_name);
      loop_list(library);
    } 

    else if(option == 11){ //loop shuffled playlist
      if(strlen(list_name) == 0){
        printf("\nERROR: Please load or create a playlist first.\n");
        continue;
      }
      printf("\nLooping %s in shuffled order...\n", list_name);
      loop_shuffled_list(library);
    } 

    else if(option == 12){ //create new playlist
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
        printf("\nERROR: Playlist name cannot be blank.\n");
      }    
    }

    else if(option == 13){ //delete playlist of choice
      char deleted_list[100];
      printf("Enter playlist name to delete: ");
      if(fgets(deleted_list, sizeof(deleted_list), stdin)){
        int length = strlen(deleted_list);
        if(length > 0 && deleted_list[length - 1] == '\n'){
          deleted_list[length - 1] = '\0';
        }
      }
      struct stat stat_buffer;    
      if(strlen(deleted_list) == 0){
        printf("\nERROR: Playlist name cannot be blank.\n");
      } 
      else if(stat(deleted_list, &stat_buffer) != 0){
        printf("\nERROR: Playlist does not exist.\n");
      } 
      else{
        if(remove(deleted_list) == 0){
          printf("\n%s deleted.\n", deleted_list);
          strcpy(list_name, "");
        } 
        else{
          perror("\nERROR: Failed to delete playlist.");
        }
      }
    }

    else if(option == 14){ //save and exit
      if(strlen(list_name) == 0){
        printf("\nERROR: No playlist to save to. Please load or create a playlist first.\n");
      }
      save_library(library, list_name);
      printf("\nPlaylist saved.\n");
      reset(library);
      free(library);
      disconnect_player();
      kill(0, SIGKILL);
      printf("\nClosing...\n");
    }
    else{
        printf("\nInvalid option. Please try again.\n");
      }
    }
    return 0;
  }
