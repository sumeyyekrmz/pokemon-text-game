#include "type.h"
#include <stdio.h>
#include <string.h>

void initializeTypes(Type types[]){
    
    // open types file
    FILE* file = fopen("types.txt", "r");
    if (file == NULL) {
        printf("Error: types.txt could not be opened.\n");
        return;
    }

    for (int i = 0; i < 18; i++) {
        // attacker type name
        fscanf(file, "%s", types[i].name);

        for (int j = 0; j < 18; j++) {

            // defender type + multiplier
            fscanf(file, "%s %lf",
                   types[i].effects[j].defName,
                   &types[i].effects[j].multiplier);

            // store attacker name
            strcpy(types[i].effects[j].atkName, types[i].name);
        }
    }
    fclose(file);

    // create None type
    strcpy(types[18].name, "None");
    
    for (int j = 0; j < 19; j++) {
        // default effects
        strcpy(types[18].effects[j].atkName, "None");
        strcpy(types[18].effects[j].defName, types[j].name);
        types[18].effects[j].multiplier = 1.0;
    }
}