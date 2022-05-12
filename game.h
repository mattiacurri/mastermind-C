#ifndef _GAME_H
#define _GAME_H

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
#define START_NUMBERS_ASCII 48
#define NUM_RESULTS 2
#define TRUE 1
#define FALSE 0

typedef struct Code {
    char value[CODE_LENGTH_INTERMEDIATE];
} Code;

typedef struct Result {
    int attemptsResult[NUM_RESULTS];
} Result;
typedef struct Parameters {
    int numSymbol;
    int codeLength;
    int repeated;
    int numAttempts;
} Parameters;

typedef struct Match {
    Parameters param;
    Code codeToGuess;
    Code attempts[NUM_ATTEMPTS_BASIC];
    Result attemptsResult[NUM_ATTEMPTS_BASIC];
    int attemptsSoFar;
} Match;

void menu();
char userChoice(int min, int max);
void showChoice(char choice);
int startMatch();
int newGameLoop();

// FUNZIONI DI ACCESSO A CODE
char getValue(Code code, int index);
Code setValue(Code code, int index, char value);

// FUNZIONI DI ACCESSO A RESULT
int getElemResult(Result result, int index);
Result setElemResult(Result result, int index, int value);

// PROTOTIPI FUNZIONI DI ACCESSO A STRUCT PARAMETERS
int getNumSymbol(Parameters param);
int getCodeLength(Parameters param);
int getRepeated(Parameters param);
int getNumAttempts(Parameters param);
Parameters setNumSymbol(Parameters param, int numSymbol);
Parameters setCodeLength(Parameters param, int codeLength);
Parameters setNumAttempts(Parameters param, int numAttempts);
Parameters setRepeated(Parameters param, int repeated);

Code getCodeToGuess(Match match);
Parameters getParam(Match match);
Code getAttempts(Match match, int index);
Result getAttemptsResult(Match match, int index);
int getAttemptsSoFar(Match match);
Match setCodeToGuess(Match match, Code CodeToGuess);
Match setParam(Match match, Parameters param);
Match setAttempt(Match match, int index, Code attempt);
Match setAttemptResult(Match match, int index, Result attemptResult);
Match setAttemptsSoFar(Match match, int attemptsSoFar);

Match generateCode(Match match);
int newAttempt(Match match);
Match validateInput(Match match, int attemptsSoFar, Code attempt);

Match checkCode(Match match, Code input, Code codeToGuess);
int wrongPosition(int i, char c, Code codeToGuess, int codeLength);
void printAttempts(Match match);
int winner(Match match);

#endif