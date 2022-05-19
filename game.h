#ifndef _GAME_H
#define _GAME_H

#include "./struct/struct.h"
#include "./rules/rules.h"
#include "./save/saveGame.h"
#include "./top10/top10.h"

void menu();
char userChoice(int min, int max);
void showChoice(char choice);
void startMatch();
void gameLoop();

Match initAttempts(Match match);
Match generateCode(Match match);
void gameChoice(Match match, int isLoaded);
Match newAttempt(Match match);
Match validateInput(Match match, int attemptsSoFar, Code attempt);
Match checkCode(Match match, Code input, Code codeToGuess);
int wrongPosition(int i, char c, Code codeToGuess, int codeLength);
void printAttempts(Match match);
int winner(Match match);
void backToMenu();

#endif
