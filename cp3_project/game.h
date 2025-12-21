#ifndef GAME_H
#define GAME_H
#include "type.h" 
#include "move.h"
#include "pokemon.h"
#include "player.h"

void initialize(Type Types[18],
                Move Moves[486],
                Pokemon Pokemons[1015],
                Player *Player1,
                Player *Player2);

void initializeTypes(Type Types[18]);
void initializeMoves(Move Moves[486], Type Types[18]);
void initializePokemons(Pokemon Pokemons[1015], Type Types[18], Move Moves[486]);
void initializePlayers(Player *Player1, Player *Player2, Pokemon Pokemons[1015]);

void round(Type Types[18], Player *Player1, Player *Player2);

void game(Type Types[18],
          Move Moves[486],
          Pokemon Pokemons[1015],
          Player *Player1,
          Player *Player2);

#endif