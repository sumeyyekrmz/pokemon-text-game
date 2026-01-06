#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "player.h"
#include "type.h"

// BAK bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
void roundFunction(Player *Player1, Player *Player2)
{
    int choice1, choice2; // Player1 ve Player2 nin seçimlerini tutan geçici değişkenler
    int moveIdx1 = -1, moveIdx2 = -1; // seçilen move ların indexleri (henüz seçilmediği için -1)

    // Player 1 in seçimi
    // Player 1'in ismi ve o an sahada olan (currentIndex - 1) Pokemon'un ismi
    printf("%s, please select your move (Active Pokemon = %s , HP = %d):\n",
           Player1->name,
           Player1->Pokemons[Player1->currentIndex - 1].name,
           Player1->Pokemons[Player1->currentIndex - 1].currentHP);

    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");

    while (scanf("%d", &choice1) != 1 || (choice1 != 1 && choice1 != 2))
    {
        printf("Invalid input! Please enter 1 or 2: ");
        while (getchar() != '\n')
            continue;// Tamponu (buffer) temizle
    }
    printf("\n");

    // Player 2 nin seçimi
    // Player 1'in ismi ve o an sahada olan (currentIndex - 1) Pokemon'un ismi
    printf("%s, please select your move (Active Pokemon = %s , HP = %d):\n",
           Player2->name,
           Player2->Pokemons[Player2->currentIndex - 1].name,
           Player2->Pokemons[Player2->currentIndex - 1].currentHP);
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");

    while (scanf("%d", &choice2) != 1 || (choice2 != 1 && choice2 != 2))
    {
        printf("Invalid input! Please enter 1 or 2: ");
        while (getchar() != '\n')
            continue; // Tamponu (buffer) temizle
    }
    printf("\n");

    // Player 1 Attack
    if (choice1 == 1)
    {

        // BAK bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        //  Aktif Pokemon'un adresi alınır
        //  currentIndex 1'den başladığı için -1 yapılır
        Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];

        // pokemonun 4 move unu listeler
        for (int i = 0; i < 4; i++)
        {
            printf("%d - %-15s ", i + 1, p1->moves[i].name);

            // Her 2 move'da bir alt satıra geç BAK bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Kullanıcıdan move seçimi alınır    bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        printf("%s, please select a move: ", Player1->name);

        while (scanf("%d", &moveIdx1) != 1 || (moveIdx1 != 1 && moveIdx1 != 2 && moveIdx1 != 3 && moveIdx1 != 4))
        {
            printf("Invalid move! Please select between 1 and 4: ");
            while (getchar() != '\n')
                continue;
        }
        printf("\n");

        // 1–4 arası girilen değer 0–3 aralığına çevrilir bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        moveIdx1--;
    }
    else
    { // Player 1 Change Pokemon

        printf("Available Pokemons for %s:\n", Player1->name);

        for (int i = 0; i < 6; i++)
        {
            // oyuncunun ölü olmayan pokemonları listelenir
            if (Player1->Pokemons[i].currentHP > 0)
            {
                printf("%d - %s (HP = %d)\n", i + 1, Player1->Pokemons[i].name, Player1->Pokemons[i].currentHP);
            }
        }

        // aktif pokemon değiştirilir
        int tempChoice;
        while (1)
        {
            printf("Please select a Pokemon to switch: ");
            if (scanf("%d", &tempChoice) == 1 && tempChoice >= 1 && tempChoice <= 6)
            {
                if (Player1->Pokemons[tempChoice - 1].currentHP > 0)
                {
                    Player1->currentIndex = tempChoice; // Seçim geçerli
                    break;
                }
                else
                {
                    printf("This Pokemon is fainted! Choose another: ");
                }
            }
            else
            {
                printf("Invalid selection! Please enter 1-6: ");
                while (getchar() != '\n')
                    continue; // Tamponu temizle
            }
        }
        printf("\n");
    }

    // Player 2 Attack
    if (choice2 == 1)
    {
        // BAK bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        //  Aktif Pokemon'un adresi alınır
        //  currentIndex 1'den başladığı için -1 yapılır
        Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

        // pokemonun 4 move unu listeler
        for (int i = 0; i < 4; i++)
        {
            printf("%d - %-15s ", i + 1, p2->moves[i].name);

            // Her 2 move'da bir alt satıra geç BAK bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Kullanıcıdan move seçimi alınır    bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        printf("%s, please select a move: ", Player2->name);

        while (scanf("%d", &moveIdx2) != 1 || (moveIdx2 != 1 && moveIdx2 != 2 && moveIdx2 != 3 && moveIdx2 != 4))
        {
            printf("Invalid move! Please select between 1 and 4: ");
            while (getchar() != '\n')
                continue;
        }
        printf("\n");
        // 1–4 arası girilen değer 0–3 aralığına çevrilir bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
        moveIdx2--;
    }
    else
    { // Player 2 Change Pokemon

        printf("Available Pokemons for %s:\n", Player2->name);

        for (int i = 0; i < 6; i++)
        {
            // oyuncunun ölü olmayan pokemonları listelenir
            if (Player2->Pokemons[i].currentHP > 0)
            {
                printf("%d - %s (HP = %d)\n", i + 1, Player2->Pokemons[i].name, Player2->Pokemons[i].currentHP);
            }
        }

        // aktif pokemon değiştirilir
        printf("Please select a Pokemon to switch: ");
        int tempChoice;
        while (1)
        {
            if (scanf("%d", &tempChoice) == 1 && tempChoice >= 1 && tempChoice <= 6)
            {
                if (Player2->Pokemons[tempChoice - 1].currentHP > 0)
                {
                    Player2->currentIndex = tempChoice; // Seçim geçerli
                    break;
                }
                else
                {
                    printf("This Pokemon is fainted! Choose another: ");
                }
            }
            else
            {
                printf("Invalid selection! Please enter 1-6: ");
                while (getchar() != '\n')
                    continue; // Tamponu temizle
            }
            printf("\n");
        }
        printf("\n");
    }
    // bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
    //  -------- HASAR HESAPLAMA --------
    applyDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2);

    // Tüm seçimler alındıktan sonra burada damage hesaplanacak
    // calculateDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2, Types);
}

void applyDamage(Player *Player1, Player *Player2, int choice1, int choice2, int moveIdx1, int moveIdx2)
{
    Player *first, *second;
    int firstChoice, secondChoice, firstMove, secondMove;

    Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];
    Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

    // Hız kontrolü: Daha hızlı olan Pokémon önce saldırır.
    if (p1->speed >= p2->speed)
    {
        first = Player1;
        second = Player2;
        firstChoice = choice1;
        secondChoice = choice2;
        firstMove = moveIdx1;
        secondMove = moveIdx2;
    } else {
        first = Player2;
        second = Player1;
        firstChoice = choice2;
        secondChoice = choice1;
        firstMove = moveIdx2;
        secondMove = moveIdx1;
    }

    // İki saldırı aşaması (Önce hızlı olan, sonra yavaş olan)
    for (int i = 0; i < 2; i++)
    {
        Player *attacker = (i == 0) ? first : second;
        Player *defender = (i == 0) ? second : first;
        int currentChoice = (i == 0) ? firstChoice : secondChoice;
        int currentMoveIdx = (i == 0) ? firstMove : secondMove;

        Pokemon *atk = &attacker->Pokemons[attacker->currentIndex - 1];
        Pokemon *def = &defender->Pokemons[defender->currentIndex - 1];

        // Eğer oyuncu 'Change Pokemon' seçtiyse o tur saldıramaz.
        // Ayrıca defender zaten bayıldıysa veya attacker baygınsa saldırı gerçekleşmez.
        if (currentChoice == 2 || def->currentHP <= 0 || atk->currentHP <= 0)
            continue;

        Move *m = &atk->moves[currentMoveIdx];

        // Saldırı ve Savunma statlarının seçimi (Physical/Special ayrımı) [cite: 224, 225]
        double attackStat = (m->category == Physical_attack) ? atk->attack : atk->spAtk;
        double defenseStat = (m->category == Physical_attack) ? def->defense : def->spDef;

        // Tip Etkinliği (TypeEffect) hesaplama [cite: 226]
        double te1 = 1.0, te2 = 1.0;
        for (int j = 0; j < 19; j++)
        {
            // Hamle tipinin defender'ın birinci tipine etkisi
            if (strcmp(def->types[0].effects[j].atkName, m->type.name) == 0)
            {
                te1 = m->type.effects[j].multiplier;
            }
            // Hamle tipinin defender'ın ikinci tipine etkisi (Eğer "None" değilse)
            if (strcmp(def->types[1].name, "None") != 0)
            {
                if (strcmp(m->type.name, def->types[1].effects[j].atkName) == 0)
                {
                    te2 = m->type.effects[j].multiplier;
                }
            }
        }

        // STAB Kontrolü (Aynı Tip Saldırı Bonusu) [cite: 227]
        double stab = (strcmp(m->type.name, atk->types[0].name) == 0 ||
                       strcmp(m->type.name, atk->types[1].name) == 0) ? 1.5 : 1.0;

        // PDF'teki Final Hasar Formülü
        double damage = m->power * (attackStat / defenseStat) * te1 * te2 * stab;

        def->currentHP -= (int)damage;
        if (def->currentHP < 0)
            def->currentHP = 0;

        printf("%s used %s! It dealt %d damage to %s.\n", atk->name, m->name, (int)damage, def->name);

        // Bayılma Kontrolü: Eğer Pokémon bayılırsa bir sonraki uygun olan seçilir[cite: 219, 229].
        if (def->currentHP <= 0)
        {
            printf("%s fainted!\n", def->name);
            for (int k = 0; k < 6; k++)
            {
                if (defender->Pokemons[k].currentHP > 0)
                {
                    defender->currentIndex = k + 1; // 1-tabanlı index [cite: 212]
                    printf("%s sent out %s!\n", defender->name, defender->Pokemons[k].name);
                    break;
                }
            }
            // Defender bayıldığı için bu tur saldırı sırası ondaysa saldıramaz.
            printf("\n");
            break;
        }
        printf("\n");
    }
}

void game(Player *Player1, Player *Player2)
{
    while (1)
    {
        int p1_has_pokemon = 0, p2_has_pokemon = 0;

        // Oyunun bitip bitmediğini kontrol et
        for (int i = 0; i < 6; i++)
        {
            if (Player1->Pokemons[i].currentHP > 0)
                p1_has_pokemon = 1;
            if (Player2->Pokemons[i].currentHP > 0)
                p2_has_pokemon = 1;
        }

        if (!p1_has_pokemon)
        {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n", Player1->name, Player2->name);
            break;
        }
        if (!p2_has_pokemon)
        {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n", Player2->name, Player1->name);
            break;
        }
        roundFunction(Player1, Player2);
    }
}
