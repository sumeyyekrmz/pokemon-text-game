#ifndef UTILS_H
#define UTILS_H
#include "type.h" 
#include "move.h"
#include "pokemon.h"
#include "player.h"

void roundFunction(Player *Player1,
           Player *Player2);

void applyDamage(Player *Player1,
                 Player *Player2,
                 int choice1,
                 int choice2,
                 int moveIdx1,
                 int moveIdx2);

void game(Player *Player1,
          Player *Player2);

#endif