#include "library.h"
#include "file.h"
#include "music_player.h"
#include "player.h"

int main(){
    struct song_node **library = init();
    add(library, "The Beatles", "Hey Jude");
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

    return 0;
}
