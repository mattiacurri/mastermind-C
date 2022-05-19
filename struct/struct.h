#ifndef _STRUCT_H
#define _STRUCT_H

#include "../global.h"

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

typedef struct Id {
	char playerID[MAX_DIM_ID];
} Id;

typedef struct Record {
	int value;
} Record;

typedef struct Topten {
	Id pID[11];
	Record score[11];
	int level;
} Topten;

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
Match setParameters(Match match, Parameters param);
Match setAttempt(Match match, int index, Code attempt);
Match setAttemptResult(Match match, int index, Result attemptResult);
Match setAttemptsSoFar(Match match, int attemptsSoFar);

int getScore(Record score);
Record setScore(Record score, int value);

Record getRecord(Topten topten, int index);
Topten setRecord(Topten topten, int index, Record score);

Id getID();
Topten setID(Topten topten, int index, Id value);


char getPlayerId(Id pID, int index);
Id setPlayerId(Id pID, int index, char value);

#endif
