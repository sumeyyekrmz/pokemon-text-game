#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"


void initializePokemons(Pokemon Pokemons[], Type Types[], Move Moves[]) {
    
    //dosyayı okumak için açma
    FILE *file = fopen("pokemon.txt", "r");
    if (file == NULL) {
        printf("Pokemon dosyasi bulunamadi!\n");
        return;
    }

    //typeName leri tutmak için geçici parametreler
    char typeName1[50], typeName2[50];

    for (int i = 0; i < 1015; i++) {
        fscanf(file, "%s %s %s %d %d %d %d %d %d", 
               Pokemons[i].name, typeName1, typeName2, 
               &Pokemons[i].maxHP, &Pokemons[i].attack, &Pokemons[i].defense, 
               &Pokemons[i].spAtk, &Pokemons[i].spDef, &Pokemons[i].speed);

        //başlangıçta can tam dolu
        Pokemons[i].currentHP = Pokemons[i].maxHP;

        for (int j = 0; j < 18; j++) {
            //typeName1 i arrayde bul ve pokemonun types arrayinin 1. elemanına ata
            if (strcmp(typeName1, Types[j].name) == 0) {
                Pokemons[i].types[0] = Types[j];
            }

            
            if (strcmp(typeName2, "-") == 0) {
                //Eğer 2. type ı yoksa Types arrayinin 19. elemanı none ata
                Pokemons[i].types[1] = Types[18];
            } else {
                //typeName2 i arrayde bul ve pokemonun types arrayinin 2. elemanına ata
                for (int j = 0; j < 18; j++) {
                    if (strcmp(typeName2, Types[j].name) == 0) {
                    Pokemons[i].types[1] = Types[j];
                    break;
                    }
                }
            }
        }

        // 4 tane random unıqe move seçme
        int count = 0;
        while (count < 4) {
            int randomIdx = rand() % 486;
            int isDuplicate = 0;

            //hareket daha önce eklenmiş mi kontrol
            for (int k = 0; k < count; k++) { 
                if (strcmp(Pokemons[i].moves[k].name, Moves[randomIdx].name) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }

            //hareket yeni ise kaydetme
            if (!isDuplicate) {
                Pokemons[i].moves[count] = Moves[randomIdx];
                count++;
            }
        }
    }
    fclose(file);
}