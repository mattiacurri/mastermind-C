#ifndef _GAME_H
#define _GAME_H

#include "./struct.h"
#include "./rules.h"
#include "./savegame.h"

int menu();
char userChoice(int min, int max);
void showChoice(char choice);
int startMatch();
void gameLoop(int isNew);

Match initAttempts(Match match);
Match generateCode(Match match);
void gameChoice(Match match);
Match newAttempt(Match match);
Match validateInput(Match match, int attemptsSoFar, Code attempt);
Match checkCode(Match match, Code input, Code codeToGuess);
int wrongPosition(int i, char c, Code codeToGuess, int codeLength);
void printAttempts(Match match);
Match winner(Match match);

#endif