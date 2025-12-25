#include "type.h"
#include <stdio.h>
#include <string.h>


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
