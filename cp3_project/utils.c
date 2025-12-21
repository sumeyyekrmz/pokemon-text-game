#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[], Player* Player1, Player* Player2)
{
    initializeTypes(Types);
    initializeMoves(Moves, Types);
    initializePokemons(Pokemons, Types, Moves);

    //rastgele pokemon atama
    srand(time(NULL));

    //player isimlerini atama
    strcpy(Player1->name, "Esila");
    strcpy(Player2->name, "Sümeyye");

    Player1->currentIndex = 1;
    Player2->currentIndex = 1;

    //kullanılan pokemonların indexinin saklanacağı array
    int usedPokemon[1015] = {0};

    //Player1 e rastgele pokemon atama
    for (int i = 0; i < 6; i++) {
        int index;

        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1;
        Player1->Pokemons[i] = Pokemons[index];
    }

    //Player2 e rastgele pokemon atama
    for (int i = 0; i < 6; i++) {
        int index;

        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1;
        Player2->Pokemons[i] = Pokemons[index];
    }
}
