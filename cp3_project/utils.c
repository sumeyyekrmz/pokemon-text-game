#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "player.h"
#include "type.h"

void roundFunction(Player *Player1, Player *Player2) {

    int choice1, choice2; // temp variable to store Player1, Player2's choices
    int moveIdx1 = -1, moveIdx2 = -1; // Index of selected moves (-1 means no move selected yet))

    // *** Player 1 Choice Screen ***
    printf("%s, please select your move (Active Pokemon = %s , HP = %d):\n",
           Player1->name,
           Player1->Pokemons[Player1->currentIndex - 1].name,
           Player1->Pokemons[Player1->currentIndex - 1].currentHP);

    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");

    // only accept 1 or 2
    while (scanf("%d", &choice1) != 1 || (choice1 != 1 && choice1 != 2)) {
        printf("Invalid input! Please enter 1 or 2: ");
        while (getchar() != '\n')
            continue; // Clear input buffer
    }
    printf("\n");

    // *** Player 1 Choice Screen ***
    printf("%s, please select your move (Active Pokemon = %s , HP = %d):\n",
           Player2->name,
           Player2->Pokemons[Player2->currentIndex - 1].name,
           Player2->Pokemons[Player2->currentIndex - 1].currentHP);
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");

    // only accept 1 or 2
    while (scanf("%d", &choice2) != 1 || (choice2 != 1 && choice2 != 2)) {
        printf("Invalid input! Please enter 1 or 2: ");
        while (getchar() != '\n') {
            continue; // Clear input buffer
        }
    }
    printf("\n");

    // *** Player 1 Chooses to Attack ***
    if (choice1 == 1) {

        // Get address of active Pokemon
        Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];

        // List 4 moves of the Pokemon
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p1->moves[i].name);

            // Print 2 moves per line for cleaner output
            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        printf("%s, please select a move: ", Player1->name);

        // only 1–4 allowed
        while (scanf("%d", &moveIdx1) != 1 || (moveIdx1 != 1 && moveIdx1 != 2 && moveIdx1 != 3 && moveIdx1 != 4)) {
            printf("Invalid move! Please select between 1 and 4: ");
            while (getchar() != '\n') {
                continue; //Clear input buffer
            }
        }
        printf("\n");

        // Convert 1–4 range to 0–3 index for array
        moveIdx1--;
    }
    else { 
        // *** Player 1 Chooses to Change Pokemon ***
        printf("Available Pokemons for %s:\n", Player1->name);

        for (int i = 0; i < 6; i++) {
            // List only alive Pokemons
            if (Player1->Pokemons[i].currentHP > 0) {
                printf("%d - %s (HP = %d)\n", i + 1, Player1->Pokemons[i].name, Player1->Pokemons[i].currentHP);
            }
        }

        printf("Please select a Pokemon to switch: ");
        int tempChoice;
        while (1) {    
            if (scanf("%d", &tempChoice) == 1 && tempChoice >= 1 && tempChoice <= 6) {
                if (Player1->Pokemons[tempChoice - 1].currentHP > 0) {
                    Player1->currentIndex = tempChoice;
                    break;
                }
                else {
                    printf("This Pokemon is fainted! Choose another: ");
                }
            }
            else {
                printf("Invalid selection! Please enter 1-6: ");
                while (getchar() != '\n') {
                    continue; // Clear input buffer
                }
            }
        }
        printf("\n");
    }

    // *** Player 2 Chooses to Attack ***
    if (choice2 == 1) {
        // Get address of active Pokemon
        Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

        // List 4 moves of the Pokemon
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p2->moves[i].name);

            // Print 2 moves per line for cleaner output
            if ((i + 1) % 2 == 0) {
                printf("\n");
            }
        }

        printf("%s, please select a move: ", Player2->name);

        // only 1–4 allowed
        while (scanf("%d", &moveIdx2) != 1 || (moveIdx2 != 1 && moveIdx2 != 2 && moveIdx2 != 3 && moveIdx2 != 4)) {
            printf("Invalid move! Please select between 1 and 4: ");
            while (getchar() != '\n') {
                continue; // Clear input buffer
            }
        }
        printf("\n");

        // Convert 1–4 range to 0–3 index for array
        moveIdx2--;
    } 
    else { 
        // *** Player 2 Chooses to Change Pokemon ***
        printf("Available Pokemons for %s:\n", Player2->name);

        for (int i = 0; i < 6; i++) {
            // List only alive Pokemons
            if (Player2->Pokemons[i].currentHP > 0) {
                printf("%d - %s (HP = %d)\n", i + 1, Player2->Pokemons[i].name, Player2->Pokemons[i].currentHP);
            }
        }

        printf("Please select a Pokemon to switch: ");
        int tempChoice;
        while (1) {
            if (scanf("%d", &tempChoice) == 1 && tempChoice >= 1 && tempChoice <= 6) {
                if (Player2->Pokemons[tempChoice - 1].currentHP > 0) {
                    Player2->currentIndex = tempChoice;
                    break;
                }
                else {
                    printf("This Pokemon is fainted! Choose another: ");
                }
            }
            else {
                printf("Invalid selection! Please enter 1-6: ");
                while (getchar() != '\n') {
                    continue; // Clear input buffer
                }
            }
            printf("\n");
        }
        printf("\n");
    }    
    applyDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2);
}

void applyDamage(Player *Player1, Player *Player2, int choice1, int choice2, int moveIdx1, int moveIdx2) {
    Player *first, *second;
    int firstChoice, secondChoice, firstMove, secondMove;

    // Get active Pokemons of both players
    Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];
    Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

    // Speed comparison (faster Pokemon attacks first)
    if (p1->speed >= p2->speed) {
        first = Player1;
        second = Player2;
        firstChoice = choice1;
        secondChoice = choice2;
        firstMove = moveIdx1;
        secondMove = moveIdx2;
    } 
    else {
        first = Player2;
        second = Player1;
        firstChoice = choice2;
        secondChoice = choice1;
        firstMove = moveIdx2;
        secondMove = moveIdx1;
    }

    // Two attack stages (first attacker then second attacker)
    for (int i = 0; i < 2; i++) {

        // Determine attacker and defender for this stage
        Player *attacker = (i == 0) ? first : second;
        Player *defender = (i == 0) ? second : first;

        int currentChoice = (i == 0) ? firstChoice : secondChoice;
        int currentMoveIdx = (i == 0) ? firstMove : secondMove;

        // Get active Pokemon of attacker and defender
        Pokemon *atk = &attacker->Pokemons[attacker->currentIndex - 1];
        Pokemon *def = &defender->Pokemons[defender->currentIndex - 1];

        // If player chose "Change Pokemon" or Pokemon is fainted (skip attack)
        if (currentChoice == 2 || def->currentHP <= 0 || atk->currentHP <= 0) {
            continue;
        }

        // Selected move of attacker
        Move *m = &atk->moves[currentMoveIdx];

        // Determine attack and defense (Physical-Special)
        double attackStat = (m->category == Physical_attack) ? atk->attack : atk->spAtk;
        double defenseStat = (m->category == Physical_attack) ? def->defense : def->spDef;

        // Type effect multipliers (temp)
        double te1 = 1.0, te2 = 1.0;
        for (int j = 0; j < 19; j++) {
            // Effect of move type on defender's first type
            if (strcmp(def->types[0].effects[j].atkName, m->type.name) == 0) {
                te1 = m->type.effects[j].multiplier;
            }
            // Effect on defender's second type (if not None)
            if (strcmp(def->types[1].name, "None") != 0) {
                if (strcmp(m->type.name, def->types[1].effects[j].atkName) == 0) {
                    te2 = m->type.effects[j].multiplier;
                }
            }
        }

        // STAB (Same Type Attack Bonus)
        double stab = (strcmp(m->type.name, atk->types[0].name) == 0 ||
                       strcmp(m->type.name, atk->types[1].name) == 0) ? 1.5 : 1.0;

        // Final damage calculation
        double damage = m->power * (attackStat / defenseStat) * te1 * te2 * stab;

        // Apply damage and set HP to zero
        def->currentHP -= (int)damage;
        if (def->currentHP < 0) {
            def->currentHP = 0;
        }

        printf("%s used %s! It dealt %d damage to %s.\n", atk->name, m->name, (int)damage, def->name);

        // If defender faints, auto-send next available Pokemon (Faint check)
        if (def->currentHP <= 0) {
            printf("%s fainted!\n", def->name);
            for (int k = 0; k < 6; k++) {
                if (defender->Pokemons[k].currentHP > 0) {
                    defender->currentIndex = k + 1; 
                    printf("%s sent out %s!\n", defender->name, defender->Pokemons[k].name);
                    break;
                }
            }
            // Defender cannot attack after fainting
            break;
        }
    }
    printf("\n");
}

void game(Player *Player1, Player *Player2) {
    while (1) {
        int p1_has_pokemon = 0, p2_has_pokemon = 0;

        // Check at least one alive Pokemon
        for (int i = 0; i < 6; i++) {
            if (Player1->Pokemons[i].currentHP > 0)
                p1_has_pokemon = 1;
            if (Player2->Pokemons[i].currentHP > 0)
                p2_has_pokemon = 1;
        }

        // End game if Player1 has no Pokemons left
        if (!p1_has_pokemon) {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n", Player1->name, Player2->name);
            break;
        }
        // End game if Player2 has no Pokemons left
        if (!p2_has_pokemon) {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n\n", Player2->name, Player1->name);
            break;
        }
        // Play one round
        roundFunction(Player1, Player2);
    }
}