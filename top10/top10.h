#ifndef TOP10_H_
#define TOP10_H_

Topten rightShift(Topten topten, int indexScore);
int isTopScore(Match match, Topten topten);
Topten addScoreInTopTen(Match match, Topten topten);
Topten loadTop10(Match match);
void saveTop10(Match match, Topten topten);
void viewTop10();

#endif
