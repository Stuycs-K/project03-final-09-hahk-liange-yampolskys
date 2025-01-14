#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "library.h"
#include "file.h"

int main(){
    struct song_node **library = init();
    int option = 0;
    char input[100];
    while(option != 5){
        printf("\nMenu:\n");
        printf("1. Add a song\n");
        printf("2. Look up a song\n");
        printf("3. Look up an artist\n");
        printf("4. View library\n");
        printf("5. Save and exit\n");
        printf("Choose an option: ");

        if(fgets(input, sizeof(input), stdin)){
            option = 0;
            for(int i = 0; input[i] >= '0' && input[i] <= '9'; i++){
                option = option*10 + (input[i] - '0');
            }
        }
        if(option == 1){
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
        }
        else if(option == 2){

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
