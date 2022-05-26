#ifndef TOP10_H_
#define TOP10_H_

#define BASTOP10PATH ""
#define INTTOP10PATH ""
#define ADVTOP10PATH ""

Topten rightShift(Topten topten, int indexScore);
int isTopScore(Match match, Topten topten);
Topten addScoreInTopTen(Match match, Topten topten, char playerName[MAX_DIM_ID]);
Topten loadTop10(Match match);
void saveTop10(Match match, Topten topten);
void viewTop10();
void cleanTop10(FILE *fp, int level);

#endif
