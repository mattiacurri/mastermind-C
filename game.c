#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TODO: PROTOTIPI DI OGNI FUNZIONE D'ACCESSO

/* ELENCO FUNZIONI:
 MENU
    NUOVA PARTITA
        SCELTA DIFFICOLTA'
        CODICE DA DECODIFICARE
        INSERIMENTO TENTATIVO
            VALIDAZIONE INPUT
            CONTROLLO CODICE INSERITO
                ESITO PARTITA
        STAMPA INTERFACCIA
        STAMPA TURNI ED ESITI
    CARICA PARTITA
        STAMPA TURNI ED ESITI DOPO CARICAMENTO FILE
    
    SALVA PARTITA
    
    TORNA AL MENU'
    ESCI DAL GIOCO
*/

// TENTATIVI EFFETTUATI: PRINTATTEMPTS
// INSERIRE NUOVO TENTATIVO: NUMERI A UNO A UNO FINO A CODELENGTH


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
Match setCodeToGuess(Match match, Parameters param, char codeToGuess[CODE_LENGTH_INTERMEDIATE]);
Parameters setNumSymbol(Parameters param, int numSymbol);
int getCodeLength(Parameters param);
Parameters setCodeLength(Parameters param, int codeLength);

void generateCode(Match match, Parameters param);

int main() {
    menu();
    system("pause");
    return 0;
}

// int getLength(char array[]);

/* STRUCT:
    PARTITA:
        LIVELLO DIFFICOLTA'
        CODICE DA INDOVINARE
        TENTATIVI
        ESITO TENTATIVI
        END
    PARAMETRI:
        LIVELLO DIFFICOLTA'
        NUMERO SIMBOLI
        SIMBOLI
        LUNGHEZZA CODICE
        NUMERO TENTATIVI
*/


// FUNZIONI D'ACCESSO DI PARAMETERS
int getNumSymbol(Parameters param) {
    int numSymbol;
    numSymbol = param.numSymbol;
    printf("NUMSYMBOL: %d\n", numSymbol);
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
    printf("PARAM.NUMSYMBOL: %d\n", param.numSymbol);
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
        printf("param.symbol[%d]: %c\n", i, param.symbol[i]);
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

// getLevel
// getCodeToGuess
// getAttempts
// getAttemptsRsult
// getEnd
// setLevel
// setCodeToGuess
// setAttempts
// setAttemptsRsult
// setEnd

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
        printf("MATCH.CODETOGUESS[%d]: %d\n", i, match.codeToGuess[i]);
        i++;
    }
    return match;
}

Match setAttempts(Match match, Parameters param, int numAttempt, char attempt[CODE_LENGTH_INTERMEDIATE]) {
    int i;
    int length;
    i = 0;
    length = getCodeLength(param);
    while (i < length) {
        match.attempts[numAttempt][i] = attempt[numAttempt];
        i++;
    }
    return match;
}

Match setAttemptsResult(Match match, Parameters param, int numAttempt, char attemptResult[1]) {
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
    Match match;
    Parameters param;
    stage = 'l';
    char codeToGuess[CODE_LENGTH_INTERMEDIATE];
    showChoice(stage);
    choice = userChoice(stage);
    
    ended = 0;
    if (choice == '1') {
        match = setLevel(match, 1);
        param = setNumSymbol(param, 6);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 3);
        param = setRepeated(param, 0);
        param = setNumAttempts(param, 20);
        generateCode(match, param);
        ended = 1;
    } else if (choice == '2') {
        match = setLevel(match, 2);
        param = setNumSymbol(param, 8);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 0);
        param = setNumAttempts(param, 15);
        generateCode(match, param);
        ended = 1;
    } else if (choice == '3') {
        match = setLevel(match, 3);
        param = setNumSymbol(param, 10);
        param = setSymbol(param, getNumSymbol(param));
        param = setCodeLength(param, 4);
        param = setRepeated(param, 1);
        param = setNumAttempts(param, 9);
        generateCode(match, param);
        ended = 1;
    }    
    return ended;
}

void generateCode(Match match, Parameters param) {
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
        codeToGuess[i] = random;
        printf("CODETOGUESS[%d]: %d\n", i, codeToGuess[i]);
        i++;  
    } 
    match = setCodeToGuess(match, param, codeToGuess);
    
    return;
}

// int getLength(char array[]) {
//     int length;
//     while (array[length] != '\0') {
//         length++;
//     }
//     return length;
// }


/* CARICARE SIMBOLI
    char symbol[11];
    int i = 0;
    while (i < 10) {
        symbol[i] = START_LOWERCASE_ASCII + i;
        i++;
    }
*/
