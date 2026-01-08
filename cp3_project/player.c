#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[], Player* Player1, Player* Player2) {
    initializeTypes(Types);
    initializeMoves(Moves, Types);
    initializePokemons(Pokemons, Types, Moves);

    // random pokemon assignment
    srand(time(NULL));

    // set player names
    strcpy(Player1->name, "Esila");
    strcpy(Player2->name, "Sumeyye");

    // starting index
    Player1->currentIndex = 1;
    Player2->currentIndex = 1;

    // used pokemon flags
    int usedPokemon[1015] = {0};

    // assign random pokemons (for Player1)
    for (int i = 0; i < 6; i++) {
        int index;

        // avoid duplicates
        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1; // mark used
        Player1->Pokemons[i] = Pokemons[index]; // add pokemon
    }

    // assign random pokemons (for Player2)
    for (int i = 0; i < 6; i++) {
        int index;

        // avoid duplicates
        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1; // mark used
        Player2->Pokemons[i] = Pokemons[index]; // add pokemon
    }
}