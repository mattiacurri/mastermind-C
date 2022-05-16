#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./game.h"

void saveGame(Match match) {
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:/Users/acurr/Desktop/Universita/I Anno - II Semestre/Laboratorio di Informatica/MasterMind/mastermind-C/save";
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

int loadGame() {
    system("cls");
    Match match;
    int ended;
    char extention[] = ".dat";
    char nameFile[] = "/match";
    FILE *file;
    char path[] = "C:/Users/acurr/Desktop/Universita/I Anno - II Semestre/Laboratorio di Informatica/MasterMind/mastermind-C/save";
    strcat(path, nameFile);
    strcat(path, extention);
    file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Errore nel salvataggio!\n");
    }
    else
    {
        printf("Partita caricata correttamente\n");
        fread(&match, sizeof(match), 1, file);
        printAttempts(match);
        ended = gameChoice(match);
    }
    fclose(file);
    return ended;
}
