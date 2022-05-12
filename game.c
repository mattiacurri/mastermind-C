#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./game.h"
#include "./rules.h"


int main() {
    menu();
    system("pause");
    return 0;
}

// FUNZIONI DI ACCESSO DI CODE
char getValue(Code code, int index) {
    int value;
    value = code.value[index];
    return value;
}

Code setValue(Code code, int index, char value) {
    code.value[index] = value;
    return code;
}

// FUNZIONI DI ACCESSO A RESULT
int getElemResult(Result result, int index) {
    int value;
    value = result.attemptsResult[index];
    return value;
}

Result setElemResult(Result result, int index, int value) {
    result.attemptsResult[index] = value;
    return result;
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



Parameters setNumSymbol(Parameters param, int numSymbol) {
    param.numSymbol = numSymbol;
    return param;
}

Parameters setCodeLength(Parameters param, int codeLength) {
    param.codeLength = codeLength;
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

Code getCodeToGuess(Match match) {
	Code codeToGuess;
	codeToGuess = match.codeToGuess;
	return codeToGuess;
}

Parameters getParam(Match match) {
    Parameters param;
    param = match.param;
    return param;
}

int getAttemptsSoFar(Match match) {
    int attemptsSoFar;
    attemptsSoFar = match.attemptsSoFar;
    return attemptsSoFar;
}

Code getAttempts(Match match, int index) {
    Code attempt;
    attempt = match.attempts[index];
    return attempt;
}

Result getAttemptsResult(Match match, int index) {
    Result attemptResult;
    attemptResult = match.attemptsResult[index];
    return attemptResult;
}

Match setCodeToGuess(Match match, Code codeToGuess) {
	match.codeToGuess = codeToGuess;
	return match;
}

Match setParameters(Match match, Parameters param) {
    match.param = param;
    return match;
}

Match setAttemptsSoFar(Match match, int attemptsSoFar) {
    match.attemptsSoFar = attemptsSoFar;
    return match;
}

Match setAttempt(Match match, int index, Code attempt) {
    match.attempts[index] = attempt;
    return match;
}

Match setAttemptResult(Match match, int index, Result attemptResult) {
    match.attemptsResult[index] = attemptResult;
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

    choice = userChoice(1, 4);
    if (choice == '1') {
        ended = startMatch();
    } else if (choice == '2') {
        // viewTop10();
    } else if (choice == '3') {
        tutorial();
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

char userChoice(int min, int max) {
    char choice;
    choice = ' ';

    do {
        printf("INSERIRE UN VALORE TRA %d e %d: ", min, max);
        scanf("%c", &choice);
        fflush(stdin);
        if (choice < min + START_NUMBERS_ASCII || choice > max + START_NUMBERS_ASCII) {
            printf("ERRORE: inserire un numero compreso tra %d e %d\n", min, max);
        }
    } while(choice < min + START_NUMBERS_ASCII || choice > max + START_NUMBERS_ASCII);
    return choice;
}

int startMatch() {
    int ended; 
    char stage;
    char choice;
    int level;
    stage = 'n';
    ended = 0;
    choice = ' ';
    level = 0;
    showChoice(stage);
    choice = userChoice(1, 2);
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
    int level;
    Match match;
    Parameters param;
    level = 0;
    stage = 'l';
    Code codeToGuess;
    showChoice(stage);
    choice = userChoice(1, 3);
    ended = 0;
    i = 0;
    if (choice == '1') {
        param = setNumSymbol(param, NUM_SYMBOL_BASIC);
        param = setCodeLength(param, CODE_LENGTH_BASIC);
        param = setRepeated(param, FALSE);
        param = setNumAttempts(param, NUM_ATTEMPTS_BASIC);
        match = setParameters(match, param);
        match = setAttemptsSoFar(match, 0);
        match = generateCode(match);
        ended = newAttempt(match);
    } else if (choice == '2') {
        param = setNumSymbol(param, 8);
        param = setCodeLength(param, 4);
        param = setRepeated(param, FALSE);
        param = setNumAttempts(param, 15);
        match = setParameters(match, param);
        match = setAttemptsSoFar(match, 0);
        match = generateCode(match);
        ended = newAttempt(match);
    } else if (choice == '3') {
        param = setNumSymbol(param, 10);
        param = setCodeLength(param, 4);
        param = setRepeated(param, TRUE);
        param = setNumAttempts(param, 9);
        match = setParameters(match, param);
        match = setAttemptsSoFar(match, 0);
        match = generateCode(match);
        ended = newAttempt(match);
    }    
    return ended;
}

Match generateCode(Match match) {
    int randomSymbol;
    int numSymbol;
    int codeLength;
    int i;
    int j;
    int elementAmount;
    int isValid;
    Code codeToGuess;

    srand(time(0));
    numSymbol = getNumSymbol(getParam(match));
    codeLength = getCodeLength(getParam(match));

    
    i = 0;
    j = 0;
    elementAmount = 0;
    isValid = 1;
    
    if (getRepeated(getParam(match)) == 0) {
        while (i < codeLength)
        {
            j = 0;
            isValid = 1;
            randomSymbol = (rand() % 10) % numSymbol;
           
            while (j < elementAmount)
            {
                if (getValue(codeToGuess, j) == randomSymbol + START_NUMBERS_ASCII)
                {
                    j = elementAmount;
                    isValid = 0;
                }
                j++;
            }
           
            if (isValid == 1)
            {
                codeToGuess = setValue(codeToGuess, i, (randomSymbol + START_NUMBERS_ASCII));
                elementAmount++;
                i++;
            }
        }
   } else {
        while (i < codeLength) {
            randomSymbol = (rand() % 10) % numSymbol;
            codeToGuess = setValue(codeToGuess, i, (randomSymbol + START_NUMBERS_ASCII));
            i++; 
        }
    }
    match = setCodeToGuess(match, codeToGuess);
    i = 0;
    while (i < getCodeLength(getParam(match))) {
        printf("%c", getValue(codeToGuess, i));
        i++;
    }
    printf("\n");
    return match;
}

void printAttempts(Match match) {
    int i;
    int j;
    int codeLength;
    codeLength = getCodeLength(getParam(match));
    int numAttempts;
    j = 0;
    i = 0;
    Code attempts;
    Result attemptResult;
    while (i < getAttemptsSoFar(match) + 1) {
        printf("Tentativo numero %d: ", i + 1);
        attempts = getAttempts(match, i);
        attemptResult = getAttemptsResult(match, i);
        j = 0;
        while (j < codeLength) {
            printf(" %c ", getValue(attempts, j));
            j++;
        }
        printf("\t \t Esito: %d-%d", getElemResult(attemptResult, 0), getElemResult(attemptResult, 1));
        printf("\n");
        i++;
    }
    return;
}

int newAttempt(Match match) {
    int codeLength;
    int i;
    int ended;
    int attemptsSoFar;
    attemptsSoFar = 0;
    ended = 0;
    codeLength = getCodeLength(getParam(match));
    Code attemptCode;
    Result attemptResult;
    Code codeToGuess;
    codeToGuess = getCodeToGuess(match);
    while (ended == 0) {
        match = validateInput(match, attemptsSoFar, attemptCode);
        system("cls");
        match = checkCode(match, getAttempts(match, attemptsSoFar), codeToGuess);
        printAttempts(match);
        ended = winner(match);
        attemptsSoFar++;
        match = setAttemptsSoFar(match, attemptsSoFar);
    }
    return ended;
}

Match validateInput(Match match, int attemptsSoFar, Code attempt) {
    int codeLength;
    int i;
    int j;
    int numSymbol;
    codeLength = getCodeLength(getParam(match));
    numSymbol = getNumSymbol(getParam(match));
    char input;
    int validInput;
    validInput = 0;
    input = ' ';
    i = 0;
    while (i < codeLength) {
        do {    
            printf("Inserire il carattere numero %d: ", i + 1);
            input = getchar();
            fflush(stdin);
            if (input < START_NUMBERS_ASCII || input > numSymbol + START_NUMBERS_ASCII) {
                printf("Errore: inserire un numero compreso tra 0 e %d\n",numSymbol - 1);
            } else if (getRepeated(getParam(match)) == FALSE) {
                j = 0;
                while (j < validInput) {
                    if (getValue(attempt, j) == input) {
                        printf("Errore: hai inserito un numero che avevi gia' inserito, in questa difficolta' ricorda che non ci possono essere cifre ripetute!\n");
                        input = START_NUMBERS_ASCII - 1;
                    }
                    j++;
                }
            } 
        } while(input < START_NUMBERS_ASCII || input > numSymbol + START_NUMBERS_ASCII);
        attempt = setValue(attempt, i, input);
        validInput++;
        i++;
    }
    match = setAttempt(match, attemptsSoFar, attempt);
    return match;
}

Match checkCode(Match match, Code input, Code codeToGuess) {
    Result attempt;
    int i;
    int used[CODE_LENGTH_INTERMEDIATE];
    int userUsed[CODE_LENGTH_INTERMEDIATE];
    int found;
    int j;
    attempt = setElemResult(attempt, 0, 0);
    attempt = setElemResult(attempt, 1, 0);   
    if (getRepeated(getParam(match)) == 0)
    {
        i = 0;
        while (i < getCodeLength(getParam(match)))
        {
            if (getValue(input, i) == getValue(codeToGuess, i))
            {
                attempt = setElemResult(attempt, 0, getElemResult(attempt, 0) + 1);
            }
            i++;
        }
        i = 0;
        while (i < getCodeLength(getParam(match)))
        {
            if (wrongPosition(i, getValue(input, i), codeToGuess, getCodeLength(getParam(match))) == 1)
            {
                attempt = setElemResult(attempt, 1, getElemResult(attempt, 1) + 1);
            }
            i++;
        }
    }
    else
    {
        i = 0;
        while (i < getCodeLength(getParam(match)))
        {
            used[i] = 0;
            userUsed[i] = 0;
            i++;
        }
        i = 0;
        while (i < getCodeLength(getParam(match)))
        {
            if (getValue(input, i) == getValue(codeToGuess, i))
            {
                attempt = setElemResult(attempt, 0, getElemResult(attempt, 0) + 1);
                used[i] = 1;
                userUsed[i] = 1;
            }
            i++;
        }
        i = 0;
        while (i < getCodeLength(getParam(match)))
        {
            found = 0;
            j = 0;
            while (j < getCodeLength(getParam(match)) && found == 0) {
                if (getValue(input, i) == getValue(codeToGuess, j) && (i != j) && (used[j] == 0) && (userUsed[i] == 0))
                {
                    found = 1;
                    used[j] = 1;
                    userUsed[j] = 1;
                    attempt = setElemResult(attempt, 1, getElemResult(attempt, 1) + 1);
                }
                j++;
            }
            i++;
        }
    }
    match = setAttemptResult(match, getAttemptsSoFar(match), attempt);
    return match;
}

int wrongPosition(int i, char c, Code codeToGuess, int codeLength) {
    int found;
    int j;
    found = 0;
    j = 0;
    while (j < codeLength && found == 0)
    {
        if (c == getValue(codeToGuess, j) && i != j)
        {
            found = 1;
        }
        j++;
    }
    return found;
}

int winner(Match match) {
    Result attemptResult;
    int codeLength;
    int i;
    int ended;
    i = 0;
    attemptResult = getAttemptsResult(match, getAttemptsSoFar(match));
    codeLength = getCodeLength(getParam(match));
    Code codeToGuess;
    codeToGuess = getCodeToGuess(match);
    if (getElemResult(attemptResult, 0) == codeLength) {
        printf("PARTITA FINITA: HA VINTO IL DECODIFICATORE!\n");
        ended = 1;
    } else if (getAttemptsSoFar(match) == getNumAttempts(getParam(match)) - 1) {
        printf("PARTITA FINITA: HA VINTO IL CODIFICATORE!\n");
        printf("Il codice era: ---");
        while (i < codeLength) {
            printf("  %c  ", getValue(codeToGuess, i));
            i++;
        }
        printf("---\n");
        ended = 1;
    } else {
        ended = 0;
    }
    return ended;
}

