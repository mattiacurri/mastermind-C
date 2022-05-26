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

    showLogo();
    if (rulesFile == NULL) {
        printf("ERRORE: PROBLEMA COL FILE DELLE REGOLE\n");
        backToMenu();
    }
    else {
    	printf("- - - - - - - - - - - - - - -     --- REGOLE DI GIOCO ---     - - - - - - - - - - - - - - - - - - - - - - - \n");

        while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
        {
            printf(" %s ", buffer);
        }

        fclose(rulesFile);
        printf("\n");
        printf("SCEGLIERE UN'OPZIONE\n");
        printf("1. VEDERE IL TUTORIAL\n");
        printf("\n");
        printf("0. Tornare al menu\n");
        printf("\n");
        choice = userChoice(0, 1);
        system("cls");
        if (choice == '1') {
        	system("cls");
        	showLogo();
        	showTutorial();
        } else {
        	menu();
        }
    }
    return;
}

void showTutorial() {
	FILE *tutorialFile;

	char buffer[BUFFER_SIZE];

	tutorialFile = fopen(HOWTOPLAY_PATH, "r");
	printf("- - - - - - - - - - - - - - -     --- TUTORIAL ---     - - - - - - - - - - - - - - - - - - - - - - - \n");
	while (fgets(buffer, BUFFER_SIZE, tutorialFile) != NULL)
	{
		printf("%s", buffer);
	}
	backToMenu();
	return;
}
