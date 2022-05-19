#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../game.h"

void saveGame(Match match) {
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:\\eclipse\\workspace\\mastermind18-05\\src\\save\\savedMatch";
    strcat(nameFile, extention);
    strcat(path, nameFile);
    file = fopen(path, "wb");
    if (file == NULL)
    {
        printf("Errore nel salvataggio!\n ");
    }
    else
    {
        printf("Salvataggio effettuato!\n");
        fwrite(&match, sizeof(match), 1, file);
    }
    fclose(file);
    return;
}

void loadGame() {
    system("cls");
    Match match;
    int isLoaded;
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:\\eclipse\\workspace\\mastermind18-05\\src\\save\\savedMatch";
    strcat(path, nameFile);
    strcat(path, extention);
    file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file!\n");
    }
    else
    {
        printf("Partita caricata correttamente\n");
        fread(&match, sizeof(match), 1, file);
        if (getAttemptsSoFar(match) == getNumAttempts(getParam(match)) || getElemResult(getAttemptsResult(match, getAttemptsSoFar(match) - 1), 0) == getCodeLength(getParam(match))) {
        	printf("Partita terminata.\n");
        	printf("Si prega di iniziare una nuova partita dal menu.\n");
        	backToMenu();
        } else {
        	printAttempts(match);
        	isLoaded = TRUE;
        	gameChoice(match, isLoaded);
        }
    }
    fclose(file);
    return;
}


