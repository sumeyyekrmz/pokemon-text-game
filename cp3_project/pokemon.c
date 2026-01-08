#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

void initializePokemons(Pokemon Pokemons[], Type Types[], Move Moves[]) {
    
    // open pokemon file
    FILE *file = fopen("pokemon.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open pokemon.txt!\n");
        return;
    }

    // temp type names
    char typeName1[50], typeName2[50];

    // read pokemon data
    for (int i = 0; i < 1015; i++) {
        fscanf(file, "%s %s %s %d %d %d %d %d %d", 
               Pokemons[i].name, typeName1, typeName2, 
               &Pokemons[i].maxHP, &Pokemons[i].attack, &Pokemons[i].defense, 
               &Pokemons[i].spAtk, &Pokemons[i].spDef, &Pokemons[i].speed);

        // set initial HP
        Pokemons[i].currentHP = Pokemons[i].maxHP;

        for (int j = 0; j < 18; j++) {
            // set primary type1
            if (strcmp(typeName1, Types[j].name) == 0) {
                Pokemons[i].types[0] = Types[j];
            }

            // check type2
            if (strcmp(typeName2, "-") == 0) {
                // no type2
                Pokemons[i].types[1] = Types[18];
            } else {
                // set primary type2
                for (int j = 0; j < 18; j++) {
                    if (strcmp(typeName2, Types[j].name) == 0) {
                    Pokemons[i].types[1] = Types[j];
                    break;
                    }
                }
            }
        }

        // select 4 random moves
        int count = 0;
        while (count < 4) {
            int randomIdx = rand() % 486;
            int isDuplicate = 0;

            // check duplicates
            for (int k = 0; k < count; k++) { 
                if (strcmp(Pokemons[i].moves[k].name, Moves[randomIdx].name) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }

            // add unique move
            if (!isDuplicate) {
                Pokemons[i].moves[count] = Moves[randomIdx];
                count++;
            }
        }
    }
    fclose(file);
}