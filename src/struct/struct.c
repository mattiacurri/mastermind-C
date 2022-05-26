#include <stdio.h>
#include <stdlib.h>
#include "./struct.h"

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

// FUNZIONI D'ACCESSO A MATCH
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

// FUNZIONI DI ACCESSO DI SCORE
int getScore(Record score) {
    int value;
    value = score.value;
    return value;
}

Record setScore(Record score, int value) {
    score.value = value;
    return score;
}

// FUNZIONI DI ACCESSO DI TOP 10
Record getRecord(Topten topten, int index) {
	Record record;
	record = topten.score[index];
	return record;
}

Topten setRecord(Topten topten, int index, Record score) {
    topten.score[index] = score;
    return topten;
}

Id getPlayerId(Topten topten, int index) {
	Id value;
	value = topten.pID[index];
	return value;
}

Topten setPlayerId(Topten topten, int index, Id value) {
	topten.pID[index] = value;
	return topten;
}

char getId(Id pID, int index) {
	char value;
	value = pID.playerID[index];
	return value;
}

Id setID(Id pID, int index, char value) {
	pID.playerID[index] = value;
	return pID;
}
