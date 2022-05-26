#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../game.h"

void saveGame(Match match) {
    FILE *file;

    file = fopen(PATH, "wb");
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
    FILE *file;
    system("cls");

    Match match;
    int isLoaded;
    int attemptsSoFar;
    int isCodeGuessed;
    int numAttempts;
    int codeLength;

    file = fopen(PATH, "rb");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file!\n");
        backToMenu();
    }
    else
    {
        printf("Partita caricata correttamente\n");
        fread(&match, sizeof(match), 1, file);

        attemptsSoFar = getAttemptsSoFar(match);
        numAttempts = getNumAttempts(getParam(match));
        codeLength = getCodeLength(getParam(match));
        isCodeGuessed = getElemResult(getAttemptsResult(match, attemptsSoFar - 1), 0);

        if (attemptsSoFar == numAttempts || isCodeGuessed == codeLength) {
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


