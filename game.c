#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#define NUM_SYMBOL_BASIC 6
#define NUM_SYMBOL_INTERMEDIATE 8
#define NUM_SYMBOL_ADVANCED 10
#define CODE_LENGTH_BASIC 3
#define CODE_LENGTH_INTERMEDIATE 4 // stesso valore di CODE_LENGTH_ADVANCED
#define REPEATED_BASIC 0 // stesso valore di REPEATED_INTERMEDIATE
#define REPEATED_ADVANCED 1
#define NUM_ATTEMPTS_BASIC 20 // PER MOTIVI DI TEST; RIMETTERE A 20
#define NUM_ATTEMPTS_INTERMEDIATE 15
#define NUM_ATTEMPTS_ADVANCED 9
#define START_LOWERCASE_ASCII 97

typedef struct Parameters {
    int numSymbol;
    char symbol[NUM_SYMBOL_ADVANCED];
    int codeLength;
    int repeated; // 0: NO; 1: SI
    int numAttempts;
} Parameters;

typedef struct Match {
    int level;
    char codeToGuess[CODE_LENGTH_INTERMEDIATE];
    char attempts[NUM_ATTEMPTS_BASIC][CODE_LENGTH_INTERMEDIATE];
    int attemptsResult[NUM_ATTEMPTS_BASIC][2];
    int end; 
} Match;

void menu();
char userChoice(char stage);
void showChoice(char choice);
int startMatch();
int newGameLoop();

// FUNZIONI D'ACCESSO DI PARAMETERS
int getNumSymbol(Parameters param);
int getCodeLength(Parameters param);
int getNumAttempts(Parameters param);
int getRepeated(Parameters param);
void getSymbol(Parameters param, char symbol[NUM_ATTEMPTS_ADVANCED]);
int getLevel(Match match);
void getCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]);
void getAttempts(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]);
void getAttemptsResult(Match match, Parameters param, int numAttempt, int attemptResult[2]);
int getEnd(Match match);

Parameters setNumSymbol(Parameters param, int numSymbol);
Parameters setCodeLength(Parameters param, int codeLength);
Parameters setNumAttempts(Parameters param, int numAttempts);
Parameters setRepeated(Parameters param, int repeated);
Parameters setSymbol(Parameters param, int numSymbol);
Match setLevel(Match match, int level);
Match setCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]);
Match setAttempt(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]);
Match setAttemptResult(Match match, Parameters param, int numAttempt, int attemptResult[2]);
Match setEnd(Match match, int end);

Match generateCode(Match match, Parameters param);
Match newAttempt(Match match, Parameters param, int attemptsSoFar);
Match validateInput(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]);
void countLetter(Match match, Parameters param, int lettere[NUM_SYMBOL_ADVANCED]);
Match checkCode(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]);
// int isCharInCodeToGuess(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i);
// int isCharRepeated(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i, char alreadyScanned[CODE_LENGTH_INTERMEDIATE], int dim);

void printAttempts(Match match, Parameters param, int i);
void printAttemptResult(Match match, Parameters param, int i);
Match winner(Match match, Parameters param, int attemptsSoFar);


int main() {
    menu();
    system("pause");
    return 0;
}

// FUNZIONI D'ACCESSO DI PARAMETERS
int getNumSymbol(Parameters param) {
    int numSymbol;
    numSymbol = param.numSymbol;
    return numSymbol;
}

int getCodeLength(Parameters param) {
    int codeLength;
    codeLength = param.codeLength;
    return codeLength;
}

int getRepeated(Parameters param) {
    int repeated;
    repeated = param.repeated;
    return repeated;
}

int getNumAttempts(Parameters param) {
    int numAttempts;
    numAttempts = param.numAttempts;
    return numAttempts;
}

void getSymbol(Parameters param, char symbol[NUM_ATTEMPTS_ADVANCED]) 
{
	int i;
	int length;
    length = getNumSymbol(param);
	i = 0;
	while (i < length)
	{
		symbol[i] = param.symbol[i];
		i++;
	}

	return;
}

Parameters setNumSymbol(Parameters param, int numSymbol) {
    param.numSymbol = numSymbol;
    return param;
}

Parameters setCodeLength(Parameters param, int codeLength) {
    param.codeLength = codeLength;
    return param;
}

Parameters setSymbol(Parameters param, int numSymbol) {
    int i;
    i = 0;
    while (i < numSymbol) {
        param.symbol[i] = START_LOWERCASE_ASCII + i;
        i++;
    }
    return param;
}

Parameters setRepeated(Parameters param, int repeated) {
    param.repeated = repeated;
    return param;
}

Parameters setNumAttempts(Parameters param, int numAttempts) {
    param.numAttempts = numAttempts;
    return param;
}

int getLevel(Match match) {
    int level;
    level = match.level;
    return level;
}

void getCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]) {
    int i;
    int length;
    i = 0;
    length = getCodeLength(param);
    while (i < length) {
        codeToGuess[i] = match.codeToGuess[i];
        i++;
    }
    return;
}

void getAttempts(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]) {
    int i;
    int length;
    i = 0;
    length = getCodeLength(param);
    while (i < length) {
        attempt[i] = match.attempts[numAttempt][i];
        i++;
    }
    return;
}

void getAttemptsResult(Match match, Parameters param, int numAttempt, int attemptResult[2]) {
    int j;
    j = 0;
    while (j < 2) {
        attemptResult[j] = match.attemptsResult[numAttempt][j];
        j++;
    }
    return;
}

int getEnd(Match match) {
    int end;
    end = match.end;
    return end;
}

Match setLevel(Match match, int level) {
    match.level = level;
    return match;
}

Match setCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]) {
    int i;
    int length;
    i = 0;
    length = getCodeLength(param);
    while (i < length) {
        match.codeToGuess[i] = codeToGuess[i];
        printf("CODICE: %c\n", match.codeToGuess[i]);
        i++;
    }
    return match;
}

Match setAttempt(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]) {
    int i;
    int length;
    i = 0;
    length = getCodeLength(param);
    while (i < length) {
        match.attempts[numAttempt][i] = attempt[i];
        i++;
    }
    return match;
}

Match setAttemptResult(Match match, Parameters param, int numAttempt, int attemptResult[2]) {
    int i;
    i = 0;
    while (i < 2) {
        match.attemptsResult[numAttempt][i] = attemptResult[i];
        i++;
    }
    return match;
}

Match setEnd(Match match, int end) {
    match.end = end;
    return match;
}

void menu() {
    int ended;
    char choice;
    int error;
    char stage;
    
    choice = ' ';
    ended = 0;
    error = 0;
    stage = 'm';
    showChoice(stage);

    choice = userChoice(stage);
    while (ended == 0) {
        if (choice == '1') {
            ended = startMatch();
        } else if (choice == '2') {
            // TODO:
            // top 10
        } else if (choice == '3') {
            // TODO: 
            // regole + tutorial
        } else if (choice == '4') {
            ended = 1;
        }
    }
    return;
}

void showChoice(char choice) {
    if (choice == 'm') {
        printf("BENVENUTO AL GIOCO DEL MASTERMIND\n");
        printf("--- MENU PRINCIPALE ---\n");
        printf("1. NUOVA PARTITA \n");
        printf("2. TOP 10\n");
        printf("3. GUIDA AL GIOCO\n");
        printf("4. ESCI DAL GIOCO\n");
    } else if(choice == 'n') {
        printf("HAI SCELTO DI INIZIARE UNA PARTITA. \n");
        printf("SCEGLI TRA LE SEGUENTI OPZIONI:\n");
        printf("1. NUOVA PARTITA\n");
        printf("2. CARICA PARTITA\n");
    } else if (choice == 'l') {
        printf("SCEGLIERE IL LIVELLO DI DIFFICOLTA' TRA I SEGUENTI\n");
        printf("1. PRINCIPIANTE\n");
        printf("2. INTERMEDIO\n");
        printf("3. AVANZATO\n");
    }
    return;
}

char userChoice(char stage) {
    char choice;
    choice = ' ';

    do {
        printf("SCEGLIERE VOCE DAL MENU: ");
        scanf("%c", &choice);
        fflush(stdin);
        if (choice < '1' || choice > '4') {
            printf("ERRORE: inserire un numero compreso tra 1 e 4");
        }
    } while(choice < '1' || choice > '4');
    return choice;
}

int startMatch() {
    int ended; 
    char stage;
    char choice;
    stage = 'n';
    ended = 0;
    choice = ' ';
    
    showChoice(stage);
    choice = userChoice(stage);
    if (choice == '1') {
        ended = newGameLoop();
    } else if (choice == '2') {
        // loadGame();
    }

    return ended;
}

int newGameLoop() {
    int ended;
    char choice;
    char stage;
    int i;
    Match match;
    Parameters param;
    stage = 'l';
    char codeToGuess[CODE_LENGTH_INTERMEDIATE];
    showChoice(stage);
    choice = userChoice(stage);
    int attemptsSoFar;
    attemptsSoFar = 0;
    ended = 0;
    i = 0;
    if (choice == '1') {
        match = setLevel(match, 1);
        param = setNumSymbol(param, 6);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 3);
        param = setRepeated(param, 0);
        param = setNumAttempts(param, 20);
        match = generateCode(match, param);
        match = setEnd(match, 0);
        while (getEnd(match) == 0) {
            match = newAttempt(match, param, attemptsSoFar);
        }
        ended = getEnd(match);
    } else if (choice == '2') {
        match = setLevel(match, 2);
        param = setNumSymbol(param, 8);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 0);
        param = setNumAttempts(param, 15);
        match = generateCode(match, param);
        match = setEnd(match, 0);
        while (getEnd(match) == 0) {
            match = newAttempt(match, param, attemptsSoFar);
        }
        ended = getEnd(match);
    } else if (choice == '3') {
        match = setLevel(match, 3);
        param = setNumSymbol(param, 10);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 1);
        param = setNumAttempts(param, 9);
        match = generateCode(match, param);
        match = setEnd(match, 0);
        while (getEnd(match) == 0) {
            match = newAttempt(match, param, attemptsSoFar);
        }
        ended = getEnd(match);
    }    
    return ended;
}

Match generateCode(Match match, Parameters param) {
    int randomSymbol;
    int numSymbol;
    int codeLength;
    int i;
    int j;
    int elementAmount;
    int isValid;

    srand(time(0));
    numSymbol = getNumSymbol(param);
    codeLength = getCodeLength(param);
    char symbol[numSymbol];
    getSymbol(param, symbol);
    char codeToGuess[codeLength];
    
    i = 0;
    j = 0;
    elementAmount = 0;
    isValid = 1;
    
    // if (getRepeated(param) == 0) {
    //     while (i < codeLength)
    //     {
    //         j = 0;
    //         isValid = 1;
    //         randomSymbol = 1 + rand() % numSymbol;
            
    //         while (j < elementAmount)
    //         {
    //             if (codeToGuess[j] == randomSymbol + START_LOWERCASE_ASCII - 1)
    //             {
    //                 j = elementAmount;
    //                 isValid = 0;
    //             }

    //             j++;
    //         }

            
    //         if (isValid == 1)
    //         {
    //             codeToGuess[i] = randomSymbol + START_LOWERCASE_ASCII - 1;
    //             elementAmount++;
    //             i++;
    //         }
    //     }
    // } else {
    //     while (i < codeLength) {
    //         randomSymbol = 1 + rand() % numSymbol;
    //         codeToGuess[i] = randomSymbol + START_LOWERCASE_ASCII - 1;
    //         i++; 
    //     }
    // }
    codeToGuess[0] = 'a';
    codeToGuess[1] = 'd';
    codeToGuess[2] = 'c';
    codeToGuess[3] = 'd';
    match = setCodeToGuess(match, param, codeToGuess);
    return match;
}

void countLetter(Match match, Parameters param, int lettere[NUM_SYMBOL_ADVANCED]) {
    int i;
    int j;
    int dim;
    int codeLength;
    // int numSymbol;
    codeLength = getCodeLength(param);
    char codeToGuess[codeLength];
    getCodeToGuess(match, param, codeToGuess);
    // numSymbol = getNumSymbol(param);

    int charToNumber;
    i = 0;
    while (i < codeLength) {
        j = 0;
        while (j < codeLength) { 
            if (codeToGuess[i] == codeToGuess[j]) {
                charToNumber = codeToGuess[j] - START_LOWERCASE_ASCII;
                // printf("ciclo %d: CHARTONUMBER DI %c: %d\n", j, codeToGuess[j], charToNumber);
                lettere[charToNumber] = lettere[charToNumber] + 1;
                // printf("lett[%d]: %d\n", charToNumber, lettere[charToNumber]);
                codeToGuess[j] = '.';
            }
            j++;
        }
        i++;
    }

    // printf("\n");
    // i = 0;
    // while (i < numSymbol) {
    //     printf("%d: %d", i, lettere[i]);    
    //     printf("\n");
    //     i++;
    // }
    return;
}

void printAttempts(Match match, Parameters param, int i) {
    int j;
    int codeLength;
    codeLength = getCodeLength(param);
    int numAttempts;
    j = 0;
    char attempts[codeLength];
    printf("Tentativo numero %d: ", i + 1);
    getAttempts(match, param, i, attempts);
    j = 0;
    while (j < codeLength) {
        printf(" %c ", attempts[j]);
        j++;
    }
    
    printf("\n");
    i++;

    return;
}

Match newAttempt(Match match, Parameters param, int attemptsSoFar) {
    int codeLength;
    int i;
    char inputC;
    codeLength = getCodeLength(param);
    char input[codeLength];
    while (getEnd(match) == 0) {
        match = validateInput(match, param, attemptsSoFar, input);
        system("cls");
        match = checkCode(match, param, attemptsSoFar, input);
        i = 0;
        while (i <= attemptsSoFar) {
            printAttempts(match, param, i);
            printAttemptResult(match, param, i);
            i++;
        }
        match = winner(match, param, attemptsSoFar);
        attemptsSoFar++;
    }
    return match;
}

Match validateInput(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]) {
    int codeLength;
    int i;
    int numSymbol;
    codeLength = getCodeLength(param);
    numSymbol = getNumSymbol(param);
    
    i = 0;
    while (i < codeLength) {
        do {    
            printf("Inserire il carattere numero %d: ", i + 1);
            scanf("%c", &input[i]);
            fflush(stdin);
            if (input[i] < START_LOWERCASE_ASCII || input[i] > START_LOWERCASE_ASCII + numSymbol - 1) {
                printf("Errore: inserire un carattere compreso tra %c e %c\n", START_LOWERCASE_ASCII, START_LOWERCASE_ASCII + numSymbol - 1);
            }
        } while(input[i] < START_LOWERCASE_ASCII || input[i] > START_LOWERCASE_ASCII + numSymbol - 1);
        i++;
    }
    match = setAttempt(match, param, attemptsSoFar, input);
    return match;
}

Match checkCode(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]) {
    int codeLength;
    int i;
    codeLength = getCodeLength(param);
    char codeToGuess[codeLength];
    int attemptResult[2];
    // int dim;
    // char alreadyScanned[codeLength];
    
    attemptResult[0] = 0;
    attemptResult[1] = 0;
    getCodeToGuess(match, param, codeToGuess);
    
    // i = 0;
    // while (i < codeLength) {
    //     printf("input[%d]: %c\n", i, input[i]);
    //     i++;
    // }
    // i = 0;
    // while (i < codeLength) {
    //     if (input[i] == codeToGuess[i]) {
    //         attemptResult[0]++;
    //         input[i] = '-';
    //     }
    //     i++;
    // }
    
    // i = 0;
    // dim = 0;
    // while (i < codeLength) {
    //     if (isCharInCodeToGuess(match, param, input, i) == 1) {
    //         printf("input[%d]: %c -> %d\n", i, input[i], isCharRepeated(match, param, input, i, alreadyScanned, dim));
    //         if (isCharRepeated(match, param, input, i, alreadyScanned, dim) == 0) {     
    //             attemptResult[1]++;
    //             alreadyScanned[dim] = input[i]; 
    //             dim++;
    //         }
    //     }
    //     i++;
    // }
    int numSymbol;
    numSymbol = getNumSymbol(param);
    int lungh[numSymbol];
    i = 0;
    while (i < numSymbol) {
        lungh[i] = 0;
        i++;
    }
    countLetter(match, param, lungh);
    int charToNumber;
    i = 0;
    int PS;
    PS = 0;
    while (i < codeLength) {
        charToNumber = input[i] - START_LOWERCASE_ASCII;
        if (input[i] == codeToGuess[i]) {
            if (lungh[charToNumber] > 0) {
                attemptResult[0]++;
                lungh[charToNumber]--;
            } 
        } else {
            if (lungh[charToNumber] > 0) {
                // attemptResult[1]++;
                PS++;
            }
        }
        i++;
    }
    i = 0;
    while (i < codeLength) {
        charToNumber = input[i] - START_LOWERCASE_ASCII;
        if (lungh[charToNumber] != 0 && input[i] != codeToGuess[i]) {
            attemptResult[1]++;
        }
        i++;
    } 
    match = setAttemptResult(match, param, attemptsSoFar, attemptResult);
    return match;
}

// int isCharInCodeToGuess(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i) {
//     int codeLength;
//     int found;
//     int j;
    
//     codeLength = getCodeLength(param);
//     char codeToGuess[codeLength];
//     getCodeToGuess(match, param, codeToGuess);
    
//     found = 0;
//     j = 0;
   
//     while (j < codeLength && found == 0) {
//         if (input[i] == codeToGuess[j] && input[i] != codeToGuess[i]) {
//             found = 1;
//         }
//         j++;
//     }
    
//     return found;
// }


// int isCharRepeated(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i, char alreadyScanned[CODE_LENGTH_INTERMEDIATE], int dim) {
//     int found;
//     int j;
    
//     found = 0;
//     j = 0;
//     while (j < dim && found == 0) {
//         if (input[i] == alreadyScanned[j] && input[i] != alreadyScanned[i]) {
//             found = 1;
//             printf("SONO QUI CON input[%d]: %c e alreadyScanned[%d]: %c\n", i, input[i], j, alreadyScanned[j]);
//         }
//         j++;
//     }
    
//     return found;
// }

void printAttemptResult(Match match, Parameters param, int i) {
    int attemptResult[2];
    getAttemptsResult(match, param, i, attemptResult);
    printf("Lettere giuste in posizione corretta: %d\nLettere giuste in posizione sbagliata: %d\n", attemptResult[0], attemptResult[1]);
    return;
}

Match winner(Match match, Parameters param, int attemptsSoFar) {
    int attemptResult[2];
    int codeLength;
    int i;
    i = 0;
    getAttemptsResult(match, param, attemptsSoFar, attemptResult);
    codeLength = getCodeLength(param);
    char codeToGuess[codeLength];
    getCodeToGuess(match, param, codeToGuess);
    if (attemptResult[0] == codeLength) {
        printf("PARTITA FINITA: HA VINTO IL DECODIFICATORE!\n");
        match = setEnd(match, 1);
    } else if (attemptsSoFar == getNumAttempts(param) - 1) {
        printf("PARTITA FINITA: HA VINTO IL CODIFICATORE!\n");
        printf("Il codice era: ---");
        while (i < codeLength) {
            printf("  %c  ", codeToGuess[i]);
            i++;
        }
        printf("---\n");
        match = setEnd(match, 1);
    }
    return match;
}

