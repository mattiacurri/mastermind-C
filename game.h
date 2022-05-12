#ifndef _GAME_H
#define _GAME_H

#include "./struct.h"
#include "./rules.h"

void menu();
char userChoice(int min, int max);
void showChoice(char choice);
int startMatch();
int newGameLoop();

Match generateCode(Match match);
int newAttempt(Match match);
Match validateInput(Match match, int attemptsSoFar, Code attempt);
Match checkCode(Match match, Code input, Code codeToGuess);
int wrongPosition(int i, char c, Code codeToGuess, int codeLength);
void printAttempts(Match match);
int winner(Match match);

#endif