#include "move.h"
#include <stdio.h>
#include <string.h>

void initializeMoves(Move Moves[], Type Types[]) {

    // Open moves data file
    FILE *file = fopen("moves.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open moves.txt!\n");
        return;
    }

    // temp string buffers
    char typeName[50];
    char categoryName[50];

    for (int i = 0; i < 486; i++) {
        // read move data
        fscanf(file, "%s %s %s %f", Moves[i].name, typeName, categoryName, &Moves[i].power);

        // match move type
        for (int j = 0; j < 18; j++) {
            if (strcmp(typeName, Types[j].name) == 0) {
                Moves[i].type = Types[j];
                break;
            }
        }

        // set attack category (physical/special)
        if (strcmp(categoryName, "Special") == 0) {
            Moves[i].category = Special_attack;
        } else {
            Moves[i].category = Physical_attack;
        }
    }
    fclose(file);
}