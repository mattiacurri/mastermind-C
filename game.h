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

#endif