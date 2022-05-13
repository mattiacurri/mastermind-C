#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./game.h"

void saveGame(Match match) {
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:/salvatg";
    strcat(nameFile, extention);
    strcat(path, nameFile);
    file = fopen(path, "w");
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

int loadGame() {
    system("cls");
    Match match;
    int ended;
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:/salvatg";
    strcat(path, nameFile);
    strcat(path, extention);
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Errore nel salvataggio!\n");
    }
    else
    {
        printf("Caricamento partita\n");
        fread(&match, sizeof(match), 1, file);
        ended = gameChoice(match);
    }
    fclose(file);
    return ended;
}
