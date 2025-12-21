#include "type.h"
#include "move.h"
#include "pokemon.h"
#include "player.h"
#include "game.h"

int main(void)
{
    Type Types[18];
    Move Moves[486];
    Pokemon Pokemons[1015];
    Player Player1;
    Player Player2;

    initialize(Types, Moves, Pokemons, &Player1, &Player2);

    game(Types, Moves, Pokemons, &Player1, &Player2);

    return 0;
}
