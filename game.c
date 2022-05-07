#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TODO: PROTOTIPI DI OGNI FUNZIONE D'ACCESSO



#define NUM_SYMBOL_BASIC 6
#define NUM_SYMBOL_INTERMEDIATE 8
#define NUM_SYMBOL_ADVANCED 10
#define CODE_LENGTH_BASIC 3
#define CODE_LENGTH_INTERMEDIATE 4 // stesso valore di CODE_LENGTH_ADVANCED
#define REPEATED_BASIC 0 // stesso valore di REPEATED_INTERMEDIATE
#define REPEATED_ADVANCED 1
#define NUM_ATTEMPS_BASIC 20
#define NUM_ATTEMPS_INTERMEDIATE 15
#define NUM_ATTEMPS_ADVANCED 9
#define START_LOWERCASE_ASCII 97

typedef struct Parameters {
    int numSymbol;
    char symbol[NUM_ATTEMPS_ADVANCED];
    int codeLength;
    int repeated; // 0: NO; 1: SI
    int numAttempts;
} Parameters;

typedef struct Match {
    int level;
    char codeToGuess[CODE_LENGTH_INTERMEDIATE];
    char attempts[NUM_ATTEMPS_ADVANCED][CODE_LENGTH_INTERMEDIATE];
    int attemptsResult[NUM_ATTEMPS_ADVANCED][1];
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
Parameters setNumSymbol(Parameters param, int numSymbol);
Parameters setCodeLength(Parameters param, int codeLength);
Match setCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]);
Match setAttempt(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]);
Match initializeAttempts(Match match, Parameters param);
Match setAttemptResult(Match match, Parameters param, int numAttempt, char attemptResult[1]);
Match generateCode(Match match, Parameters param);
void printAttempts(Match match, Parameters param, int numAttempts);
Match newAttempt(Match match, Parameters param, int attemptsSoFar);
Match validateInput(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]);
Match checkCode(Match match, Parameters param, int attemptsSoFar, char input[CODE_LENGTH_INTERMEDIATE]);
int isCharInVector(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i);
void printAttemptResult(Match match, Parameters param, int numAttempt);

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

void getSymbol(Parameters param, char symbol[NUM_ATTEMPS_ADVANCED]) 
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
        attempt[numAttempt] = match.attempts[numAttempt][i];
        i++;
    }
    return;
}

void getAttemptsResult(Match match, Parameters param, int numAttempt, char attemptResult[1]) {
    int i;
    i = 0;
    while (i < 2) {
        attemptResult[i] = match.attemptsResult[numAttempt][i];
        i++;
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

Match setAttemptResult(Match match, Parameters param, int numAttempt, char attemptResult[1]) {
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

Match initializeAttempts(Match match, Parameters param) {
    int i;
    int j;
    i = 0;
    int numAttempts;
    int codeLength;
    codeLength = getCodeLength(param);
    numAttempts = getNumAttempts(param);
    char attempts[codeLength];
    while (i < codeLength) {
        attempts[i] = '-';
        i++;
    }

    i = 0;
    while (i < numAttempts) {
        match = setAttempt(match, param, i, attempts);
        i++; 
    }
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
    
    system("cls");

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
        while (ended == 0) {
            i = 0;
            while (i < attemptsSoFar) {
                printAttempts(match, param, i);
                i++;
            }
            attemptsSoFar++;
            match = newAttempt(match, param, attemptsSoFar);
            ended = 1;
        }
        ended = 1;
    } else if (choice == '2') {
        match = setLevel(match, 2);
        param = setNumSymbol(param, 8);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 0);
        param = setNumAttempts(param, 15);
        match = generateCode(match, param);
        while (ended == 0) {
            i = 0;
            while (i < attemptsSoFar) {
                printAttempts(match, param, i);
                i++;
            }
            ended = 1;
        }
        ended = 1;
    } else if (choice == '3') {
        match = setLevel(match, 3);
        param = setNumSymbol(param, 10);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 1);
        param = setNumAttempts(param, 9);
        match = generateCode(match, param);
        while (ended == 0) {
            i = 0;
            while (i < attemptsSoFar) {
                printAttempts(match, param, i);
                i++;
            }
            ended = 1;
        }
        ended = 1;
    }    
    return ended;
}

Match generateCode(Match match, Parameters param) {
    int random;
    int numSymbol;
    int codeLength;
    int i;
    
    srand(time(0));
    numSymbol = getNumSymbol(param);
    codeLength = getCodeLength(param);
    i = 0;
    
    char codeToGuess[codeLength];
    while (i < codeLength) {    
        random = 1 + rand() % numSymbol;
        codeToGuess[i] = random + START_LOWERCASE_ASCII - 1;
        i++;  
    } 
    match = setCodeToGuess(match, param, codeToGuess);
    
    return match;
}

// TENTATIVI EFFETTUATI: PRINTATTEMPTS
// INSERIRE NUOVO TENTATIVO: NUMERI A UNO A UNO FINO A CODELENGTH

void printAttempts(Match match, Parameters param, int numAttempts) {
    int i;
    int j;

    int codeLength;
    i = 0;
    codeLength = getCodeLength(param);

    j = 0;
    while (j < codeLength) {
        printf(" %c ", match.attempts[numAttempts][j]);
        j++;
    }
    printf("\n");
    i++; 
    
    return;
}

Match newAttempt(Match match, Parameters param, int attemptsSoFar) {
    int codeLength;
    codeLength = getCodeLength(param);
    char input[codeLength];
    match = validateInput(match, param, attemptsSoFar, input);
    match = checkCode(match, param, attemptsSoFar, input);
    printAttempts(match, param, attemptsSoFar);
    printAttemptResult(match, param, attemptsSoFar);
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
    char attemptResult[1];
    attemptResult[0] = 0;
    attemptResult[1] = 0;
    getCodeToGuess(match, param, codeToGuess);
    i = 0;
    while (i < codeLength) {
        if (input[i] == codeToGuess[i]) {
            attemptResult[0]++;
        }
        i++;
    }
    i = 0;
    while (i < codeLength) {
        if (isCharInVector(match, param, input, i) == 1) {
            attemptResult[1]++;
        }
        i++;
    }

    match = setAttemptResult(match, param, attemptsSoFar, attemptResult);
    return match;
}

int isCharInVector(Match match, Parameters param, char input[CODE_LENGTH_INTERMEDIATE], int i) {
    int codeLength;
    int found;
    
    int j;
    codeLength = getCodeLength(param);
    char codeToGuess[codeLength];
    getCodeToGuess(match, param, codeToGuess);
    
    found = 0;
   
    j = 0;
    while (j < codeLength && found == 0) {
        if (input[i] == codeToGuess[j]) {
            found = 1;
        }
        j++;
    }
    
    return found;
}

void printAttemptResult(Match match, Parameters param, int numAttempt) {
    char attemptResult[1];
    getAttemptsResult(match, param, numAttempt, attemptResult);
    printf("%d-%d\n", attemptResult[0], attemptResult[1]);
    return;
}