#include "./rules.h"
#define BUFFER_SIZE 256

void showRules()
{  
    FILE* rulesFile;
    char buffer[BUFFER_SIZE];
    char choice;

    rulesFile = fopen("C:/Users/acurr/Desktop/Universita/I Anno - II Semestre/Laboratorio di Informatica/MasterMind/mastermind-C/rules.txt", "r");
    choice = ' ';

    if (rulesFile == NULL) {
        printf("ERRORE: PROBLEMA COL FILE DELLE REGOLE\n");
        menu();
    }
    else {
        printf("\n  --- REGOLE DI GIOCO ---\n\n");

        while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
        {
            printf("  %s", buffer);
        }
        printf("\n");
        printf("SCEGLIERE UN'OPERAZIONE\n");
        printf("1. TORNARE AL MENU'\n");
        printf("2. GIOCARE IL TUTORIAL\n");
        choice = userChoice(1, 2);
        if (choice == '1') {
            system("cls");
            menu();
        } else if (choice == '2') {
            system("cls");
            // tutorial()
    }
    
    }
    return;
}
