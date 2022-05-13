#include <conio.h>
#include "./rules.h"
#define BUFFER_SIZE 256

void tutorial()
{  
    FILE* rulesFile;
    char buffer[BUFFER_SIZE];
    char c;
    rulesFile = fopen("mastermind-C/rules.txt", "r");
    if (rulesFile == NULL) {
        printf("FILE NON APERTO");
    }
    printf("\n  --- REGOLE DI GIOCO ---\n\n");

    while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
    {
        printf("  %s", buffer);
    }

    printf("\n  -----------------------\n\n");
    
    printf("Premere un tasto qualsiasi per tornare al menu...");
    getch();
    printf("\n");
    system("cls");
    menu();
    return;
}
