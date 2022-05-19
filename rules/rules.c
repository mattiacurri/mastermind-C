#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "./rules.h"

void showRules()
{  
    FILE* rulesFile;
    char buffer[BUFFER_SIZE];
    char choice;

    rulesFile = fopen(RULES_PATH, "r");
    choice = ' ';


    if (rulesFile == NULL) {
        printf("ERRORE: PROBLEMA COL FILE DELLE REGOLE\n");
        backToMenu();
    }
    else {
        printf("\n  --- REGOLE DI GIOCO ---\n\n");

        while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(rulesFile);
        printf("\n");
        printf("1. VEDERE IL TUTORIAL\n");
        printf("2. TORNARE AL MENU\n");
        choice = userChoice(1, 2);
        if (choice == '1') {
        	rulesFile = fopen(HOWTOPLAY_PATH, "r");
        	printf("\n  --- TUTORIAL ---\n\n");
        	while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
        	{
        		printf("%s", buffer);
        	}
        	backToMenu();
        } else {
        	system("cls");
        	menu();
        }
    }
    return;
}
