#include <stdio.h>
#include "type.h"
#include "move.h"
#include "pokemon.h"
#include "player.h"
#include "utils.h"

Type Types[19];
    Move Moves[486];
    Pokemon Pokemons[1015];

int main(void)
{
    printf("GAME STARTED\n\n");

    
    Player Player1;
    Player Player2;

    initialize(Types, Moves, Pokemons, &Player1, &Player2);

    //BAK
    game(&Player1, &Player2);

    return 0;
}
