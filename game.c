#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./game.h"

int main() {
    menu();

    system("pause");
    return 0;
}

int menu() {
    int ended;
    char choice;
    char stage;
    
    choice = ' ';
    ended = FALSE;
    stage = 'm';
    showChoice(stage);

    choice = userChoice(1, 4);
    system("cls");

    if (choice == '1') {
        ended = startMatch();
    } else if (choice == '2') {
        // viewTop10();
    } else if (choice == '3') {
        showRules();
    } else if (choice == '4') {
        ended = TRUE;
    }
    return ended;
}

void showChoice(char choice) {
    if (choice == 'm') {
        printf("BENVENUTO AL GIOCO DEL MASTERMIND\n");
        printf("--- MENU PRINCIPALE ---\n");
        printf("1. GIOCA PARTITA \n");
        printf("2. TOP 10\n");
        printf("3. GUIDA AL GIOCO\n");
        printf("4. ESCI DAL GIOCO\n");
    } else if(choice == 'n') {
        printf("HAI SCELTO DI GIOCARE UNA PARTITA. \n");
        printf("SCEGLI TRA LE SEGUENTI OPZIONI:\n");
        printf("1. NUOVA PARTITA\n");
        printf("2. CARICA PARTITA\n");
    } else if (choice == 'l') {
        printf("SCEGLIERE IL LIVELLO DI DIFFICOLTA' TRA I SEGUENTI\n");
        printf("1. PRINCIPIANTE\n");
        printf("2. INTERMEDIO\n");
        printf("3. AVANZATO\n");
    } else if (choice == 'a') {
        printf("SCEGLIERE UN'OPZIONE:\n");
        printf("1. INSERIRE TENTATIVO\n");
        printf("2. SALVARE LA PARTITA\n");
        printf("3. TORNARE AL MENU'\n");
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

    stage = 'n';
    ended = FALSE;
    choice = ' ';
    
    showChoice(stage);
    choice = userChoice(1, 2);
    system("cls");
    
    if (choice == '1') {
        ended = gameLoop(TRUE);
    } else if (choice == '2') {
        ended = loadGame();
    }

    return ended;
}

int gameLoop(int isNew) {
    Match match;
    Parameters param;
    int ended;
    char choice;
    char stage;
    
    ended = FALSE;
    choice = ' ';
    stage = 'l';

    if (isNew == TRUE) {
        showChoice(stage);
        choice = userChoice(1, 3);
    }
    system("cls");
    
    if (isNew == TRUE) {
        if (choice == '1') {
            param = setNumSymbol(param, NUM_SYMBOL_BASIC);
            param = setCodeLength(param, CODE_LENGTH_BASIC);
            param = setRepeated(param, FALSE);
            param = setNumAttempts(param, NUM_ATTEMPTS_BASIC);
            match = setParameters(match, param);
            match = generateCode(match);

            match = setAttemptsSoFar(match, NUM_ATTEMPTS_BASIC);
            match = initAttempts(match);
            printAttempts(match);

            match = setAttemptsSoFar(match, 0);
            ended = gameChoice(match);
        } else if (choice == '2') {
            param = setNumSymbol(param, NUM_SYMBOL_INTERMEDIATE);
            param = setCodeLength(param, CODE_LENGTH_INTERMEDIATE);
            param = setRepeated(param, FALSE);
            param = setNumAttempts(param, NUM_ATTEMPTS_INTERMEDIATE);
            match = setParameters(match, param);
            match = generateCode(match);

            match = setAttemptsSoFar(match, NUM_ATTEMPTS_INTERMEDIATE);
            match = initAttempts(match);
            printAttempts(match);

            match = setAttemptsSoFar(match, 0);
            ended = gameChoice(match);
        } else if (choice == '3') {
            param = setNumSymbol(param, NUM_ATTEMPTS_ADVANCED);
            param = setCodeLength(param, CODE_LENGTH_INTERMEDIATE);
            param = setRepeated(param, TRUE);
            param = setNumAttempts(param, NUM_ATTEMPTS_ADVANCED);
            match = setParameters(match, param);
            match = generateCode(match);

            match = setAttemptsSoFar(match, NUM_ATTEMPTS_ADVANCED);
            match = initAttempts(match);
            printAttempts(match);

            match = setAttemptsSoFar(match, 0);
            ended = gameChoice(match);
        }
    } else {
        ended = gameChoice(match);
    }
    return ended;
}

Match generateCode(Match match) {
    Code codeToGuess;
    int randomSymbol;
    int numSymbol;
    int codeLength;

    numSymbol = getNumSymbol(getParam(match));
    codeLength = getCodeLength(getParam(match));
    
    int i;
    int j;
    int isValid;

    i = 0;
    j = 0;
    isValid = 1;
    srand(time(0));
    
    if (getRepeated(getParam(match)) == 0) {
        while (i < codeLength)
        {
            j = 0;
            isValid = 1;
            randomSymbol = (rand() % 10) % numSymbol;
           
            while (j < i)
            {
                if (getValue(codeToGuess, j) == randomSymbol + START_NUMBERS_ASCII)
                {
                    j = i;
                    isValid = 0;
                }
                j++;
            }
           
            if (isValid == 1)
            {
                codeToGuess = setValue(codeToGuess, i, (randomSymbol + START_NUMBERS_ASCII));
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
    return match;
}

Match initAttempts(Match match) {
    Code attempt;
    Result attemptResult;
    int codeLength;
    int i;
    int j;
    
    codeLength = getCodeLength(getParam(match));
    
    i = 0;
    j = 0;
    
    while (i < getAttemptsSoFar(match)) {
        j = 0;

        while (j < getCodeLength(getParam(match))) {
            attempt = setValue(attempt, j, '-');
            j++;
        }

        attemptResult = setElemResult(attemptResult, 0, 0);
        attemptResult = setElemResult(attemptResult, 1, 0);
        match = setAttempt(match, i, attempt);
        match = setAttemptResult(match, i, attemptResult);
        match = setAttemptResult(match, i, attemptResult);
        i++;
    }
    
    return match;
}

void printAttempts(Match match) {
    Code attempts;
    Result attemptResult;
    int i;
    int j;
    int codeLength;

    codeLength = getCodeLength(getParam(match));
    
    j = 0;
    // STYLING
    while (j < 62) {
        printf("%c", 196);
        j++;
    }
    printf("\n");
    printf("%c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  %c\n", 218, 191);
    // END STYLING
    
    i = 0;
    while (i < getNumAttempts(getParam(match))) {
        printf("%c Tentativo numero %d: ", 179, i + 1);
    
        // STYLING
        if (i < 9) {
            printf(" ");
        }
        // END STYLING
    
        attempts = getAttempts(match, i);
        attemptResult = getAttemptsResult(match, i);
    
        j = 0;
        while (j < codeLength) {
            printf(" %c ", getValue(attempts, j));
            j++;
        }
        printf("\t \t Esito: %d-%d  %c\n", getElemResult(attemptResult, 0), getElemResult(attemptResult, 1), 179);
        
        // STYLING
        if (i == getNumAttempts(getParam(match)) - 1) {
            printf("%c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  %c\n", 192, 217);
        } else {
            printf("%c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  %c\n", 179, 179);
        }
        // END STYLING
        
        i++;
    }

    // STYLING
    j = 0;
    while (j < 62) {
        printf("%c", 196);
        j++;
    }
    printf("\n");
    // END STYLING
    return;
}

int gameChoice(Match match) {
    Parameters param;
    Code codeToGuess;
    Code attempts;
    Result attemptsResult;

    int attemptsSoFar;
    int ended;
    char stage;
    char choice;
    int i;
    int j;

    ended = FALSE;
    stage = 'a';
    choice = ' ';
    i = 0;
    j = 0;
    
    // NECESSARIE PER CARICARE LA PARTITA   
    param = getParam(match);
    codeToGuess = getCodeToGuess(match);
    attemptsSoFar = getAttemptsSoFar(match);
    while (i < attemptsSoFar) {
        attemptsResult = getAttemptsResult(match, i);
        attempts = getAttempts(match, i);
        i++;
    }
    
    while (ended == FALSE) {
        showChoice(stage);
        choice = userChoice(1, 3);
        system("cls");

        if (choice == '1') {
            printAttempts(match);   
            match = newAttempt(match);
            printAttempts(match);
            match = winner(match);
            match = setAttemptsSoFar(match, getAttemptsSoFar(match) + 1);
            if (getAttemptsSoFar(match) == -1) {
                ended = TRUE;
            }
        } else if (choice == '2') {
            system("cls");
            saveGame(match);
            ended = TRUE;
            menu();
        } else if (choice == '3') {
            system("cls");
            ended = TRUE;
            menu();
        }
    }
    
    return ended;
}

Match newAttempt(Match match) {
    Code attemptCode;
    Code codeToGuess;
    int codeLength;
    int attemptsSoFar;

    codeToGuess = getCodeToGuess(match);
    codeLength = getCodeLength(getParam(match));
    attemptsSoFar = getAttemptsSoFar(match);

    match = validateInput(match, attemptsSoFar, attemptCode);
    
    system("cls");
    
    match = checkCode(match, getAttempts(match, attemptsSoFar), codeToGuess);
    return match;
}

Match validateInput(Match match, int attemptsSoFar, Code attempt) {
    int codeLength;
    int i;
    int j;
    int numSymbol;
    int validInput;
    char input;

    codeLength = getCodeLength(getParam(match));
    numSymbol = getNumSymbol(getParam(match));
    
    input = ' ';
    
    i = 0;
    validInput = 0;
    while (i < codeLength) {
        do {    
            printf("Inserire il numero in posizione %d: ", i + 1);
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
    int used[CODE_LENGTH_INTERMEDIATE];
    int userUsed[CODE_LENGTH_INTERMEDIATE];
    int i;
    int j;
    int found;

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

    j = 0;
    found = 0;
    
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

Match winner(Match match) {
    Code codeToGuess;
    Result attemptResult;
    int codeLength;
    int i;

    codeToGuess = getCodeToGuess(match);
    attemptResult = getAttemptsResult(match, getAttemptsSoFar(match));
    codeLength = getCodeLength(getParam(match));
    
    if (getElemResult(attemptResult, 0) == codeLength) {
        printf("PARTITA FINITA: HA VINTO IL DECODIFICATORE!\n");
        match = setAttemptsSoFar(match, -2);
    } else if (getAttemptsSoFar(match) == getNumAttempts(getParam(match)) - 1) {
        printf("PARTITA FINITA: HA VINTO IL CODIFICATORE!\n");
        printf("Il codice era: ---");
        i = 0;
        while (i < codeLength) {
            printf("  %c  ", getValue(codeToGuess, i));
            i++;
        }
        printf("---\n");
        match = setAttemptsSoFar(match, -2);
    } 
    return match;
}

