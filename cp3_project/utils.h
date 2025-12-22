#ifndef UTILS_H
#define UTILS_H
#include "type.h" 
#include "move.h"
#include "pokemon.h"
#include "player.h"

void initialize(Type Types[],
                Move Moves[],
                Pokemon Pokemons[],
                Player *Player1,
                Player *Player2);

void initializeTypes(Type Types[]);
void initializeMoves(Move Moves[], Type Types[]);
void initializePokemons(Pokemon Pokemons[], Type Types[], Move Moves[]);


//BAK
void round(Type Types[], Player *Player1, Player *Player2);

//BAK
void game(Type Types[],
          Move Moves[],
          Pokemon Pokemons[],
          Player *Player1,
          Player *Player2);

#endif