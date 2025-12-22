#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "pokemon.h"
#include "player.h"
#include "move.h"
#include "type.h" 

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
        } while (usedPokemon[index]);// 0/1 e göre dublicate kontrolü

        usedPokemon[index] = 1;//kullanılan pokemonları 1 olarak işaretleme
        Player1->Pokemons[i] = Pokemons[index];
    }

    //Player2 ye rastgele pokemon atama
    for (int i = 0; i < 6; i++) {
        int index;

        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1;
        Player2->Pokemons[i] = Pokemons[index];
    }
}


void initializeTypes(Type types[])
{
    //dosyayı okumak için açma
    FILE* file = fopen("types.txt", "r");
    if (file == NULL) {
        printf("Error: types.txt could not be opened.\n");
        return;
    }

    for (int i = 0; i < 18; i++) {

        //attack yapan pokemonun type ı 
        fscanf(file, "%s", types[i].name);

        for (int j = 0; j < 18; j++) {

            //defans yapan pokemonun type ı ve hasar çarpanı
            fscanf(file, "%s %lf",
                   types[i].effects[j].defName,
                   &types[i].effects[j].multiplier);

            //atkName = attack yapan pokemonun ismi
            strcpy(types[i].effects[j].atkName, types[i].name);
        }
    }

    //dosyayı kapatma
    fclose(file);

    //None type ını oluşturma ve 19. eleman olarak atama
    strcpy(types[18].name, "None");
    
    for (int j = 0; j < 19; j++) {
        strcpy(types[18].effects[j].atkName, "None");
        strcpy(types[18].effects[j].defName, types[j].name);
        types[18].effects[j].multiplier = 1.0;
    }
}


void initializeMoves(Move Moves[], Type Types[]) {

    //dosyayı okumak için açma
    FILE *file = fopen("moves.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open moves.txt!\n");
        return;
    }

    //isimleri tutmak için geçici parametreler
    char typeName[50];
    char categoryName[50];

    for (int i = 0; i < 486; i++) {
        fscanf(file, "%s %s %s %d", Moves[i].name, typeName, categoryName, &Moves[i].power);

        //typeName i Types arrayinde bulup move a atama
        for (int j = 0; j < 18; j++) {
            if (strcmp(typeName, Types[j].name) == 0) {
                Moves[i].type = Types[j];
                break;
            }
        }

        //catagoryName in special/physical olduğuna karar verip atama
        if (strcmp(categoryName, "Special") == 0) {
            Moves[i].category = Special_attack;
        } else {
            Moves[i].category = Physical_attack;
        }
    }

    //dosyayı kapatma
    fclose(file);
}


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


//BAK
void round(Player *Player1, Player *Player2, Type Types[]) {

    // Oyuncuların ana seçimleri (1: Attack, 2: Change Pokemon)
    int choice1, choice2;

    // Seçilen move indexleri (henüz seçilmediği için -1)
    int moveIdx1 = -1, moveIdx2 = -1;

    // -------- PLAYER 1 ANA SEÇİM --------
    printf("Player 1, select your move:\n");
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");
    scanf("%d", &choice1);

    // -------- PLAYER 2 ANA SEÇİM --------
    printf("Player 2, select your move:\n");
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");
    scanf("%d", &choice2);

    // -------- PLAYER 1 DETAYLI SEÇİM --------
    if (choice1 == 1) {  
        // Player 1 saldırı seçtiyse

        // Aktif Pokemon'un adresi alınır
        // currentIndex 1'den başladığı için -1 yapılır
        Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];

        // Pokemon'un 4 move'u listelenir
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p1->moves[i].name);

            // Her 2 move'da bir alt satıra geç
            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Kullanıcıdan move seçimi alınır
        printf("Please select a move: ");
        scanf("%d", &moveIdx1);

        // 1–4 arası girilen değer 0–3 aralığına çevrilir
        moveIdx1--;

    } else {
        // Player 1 Pokemon değiştirmek isterse

        printf("Available Pokemons:\n");

        // Oyuncunun 6 Pokemon'u dolaşılır
        for (int i = 0; i < 6; i++) {

            // HP'si 0'dan büyük olanlar (ölü olmayanlar) listelenir
            if (Player1->Pokemons[i].currentHP > 0) {
                printf("%d - %s ", i + 1, Player1->Pokemons[i].name);
            }
        }

        // Yeni aktif Pokemon seçilir
        printf("\nPlease select a Pokemon to switch: ");
        scanf("%d", &Player1->currentIndex);
    }

    // -------- PLAYER 2 DETAYLI SEÇİM --------
    if (choice2 == 1) {
        // Player 2 saldırı seçtiyse

        // Player 2'nin aktif Pokemon'u
        Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

        // 4 move listelenir
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p2->moves[i].name);

            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Move seçimi alınır
        printf("Please select a move: ");
        scanf("%d", &moveIdx2);

        // 0-tabanlı indexe çevirilir
        moveIdx2--;

    } else {
        // Player 2 Pokemon değiştirmek isterse

        printf("Available Pokemons:\n");

        for (int i = 0; i < 6; i++) {
            if (Player2->Pokemons[i].currentHP > 0) {
                printf("%d - %s ", i + 1, Player2->Pokemons[i].name);
            }
        }

        // Yeni aktif Pokemon seçilir
        printf("\nPlease select a Pokemon to switch: ");
        scanf("%d", &Player2->currentIndex);
    }

    // -------- HASAR HESAPLAMA --------
    // Tüm seçimler alındıktan sonra burada damage hesaplanacak
    // calculateDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2, Types);
}

