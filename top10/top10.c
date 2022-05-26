#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "../game.h"
#include "./top10.h"

#define BASTOP10PATH "C:\\eclipse\\workspace\\mastermind18-05\\src\\top10\\BAStop10.dat"
#define INTTOP10PATH "C:\\eclipse\\workspace\\mastermind18-05\\src\\top10\\INTtop10.dat"
#define ADVTOP10PATH "C:\\eclipse\\workspace\\mastermind18-05\\src\\top10\\ADVtop10.dat"

Topten rightShift(Topten topten, int indexScore) {
	Topten temp;

	int i;
	i = indexScore;
	while (i < 9) {
		temp = setRecord(temp, i, getRecord(topten, i));
		temp = setPlayerId(temp, i, getPlayerId(topten, i));
		i++;
	}

	i = indexScore;
	while (i < 9) {
		topten = setRecord(topten, i + 1, getRecord(temp, i));
		topten = setPlayerId(topten, i + 1, getPlayerId(temp, i));
		i++;
	}

	return topten;
}

int isTopScore(Match match, Topten topten) {
	Record record;
	int isTopScore;
	int i;
	isTopScore = FALSE;
	i = 0;

	while (i < 10 && isTopScore == FALSE) {
		record = getRecord(topten, i);
		if ((getAttemptsSoFar(match) + 1) < getScore(record)) {
			isTopScore = TRUE;
		}
		i++;
	}
	return isTopScore;
}

Topten addScoreInTopTen(Match match, Topten topten, char playerName[MAX_DIM_ID]) {
	Record record;
	int indexScore;
	int found;
	int i;
	indexScore = 0;
	i = 0;
	found = FALSE;

	while (i < 10 && found == FALSE) {
		record = getRecord(topten, i);
		if ((getAttemptsSoFar(match) + 1) < getScore(record)) {
			indexScore = i;
			topten = rightShift(topten, indexScore);
			record = setScore(record, (getAttemptsSoFar(match) + 1));
			topten = setRecord(topten, i, record);
			found = TRUE;
		}
		i++;
	}

	Id id;
	int j;
	j = 0;
	while (j < MAX_DIM_ID) {
		id = setID(id, j, playerName[j]);
		j++;
	}

	topten = setPlayerId(topten, indexScore, id);
	return topten;
}

Topten loadTop10(Match match) {
	Topten topten;
	FILE *fp;

	// OTTIMIZZARE: VARIABILE IN SCELTA DIFFICOLTA'
	if (getNumSymbol(getParam(match)) == NUM_SYMBOL_BASIC) {
		fp = fopen(BASTOP10PATH, "rb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_INTERMEDIATE) {
		fp = fopen(INTTOP10PATH, "rb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_ADVANCED) {
		fp = fopen(ADVTOP10PATH, "rb");
	}
	if (fp == NULL) {
		printf("ERRORE NEL CARICAMENTO DELLA TOP 10\n");
	}
	fread(&topten, sizeof(Topten), 1, fp);
	fclose(fp);
	return topten;
}

void saveTop10(Match match, Topten topten) {
	FILE *fp;

	if (getNumSymbol(getParam(match)) == NUM_SYMBOL_BASIC) {
		fp = fopen(BASTOP10PATH, "wb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_INTERMEDIATE) {
		fp = fopen(INTTOP10PATH, "wb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_ADVANCED) {
		fp = fopen(ADVTOP10PATH, "wb");
	}

	fwrite(&topten, sizeof(Topten), 1, fp);
	fclose(fp);
	return;
}

void viewTop10() {
	FILE *fp;
	Topten topten;
	char choice;
	char stage;
	int level;

	choice = ' ';
	stage = 't';
	level = 0;

	showChoice(stage);
	choice = userChoice(0, 3);

	if (choice == '0') {
		system("cls");
		menu();
	} else {
		system("cls");
		if (choice == '1') {
			fp = fopen(BASTOP10PATH, "rb");
			level = 1;
			if (fp == NULL) {
				printf(
						"Errore nell'apertura della top 10 di difficolta' principiante");
			}
		} else if (choice == '2') {
			fp = fopen(INTTOP10PATH, "rb");
			level = 2;
			if (fp == NULL) {
				printf(
						"Errore nell'apertura della top 10 di difficolta' intermedia");
			}
		} else if (choice == '3') {
			fp = fopen(ADVTOP10PATH, "rb");
			level = 3;
			if (fp == NULL) {
				printf(
						"Errore nell'apertura della top 10 di difficolta' avanzata");
			}
		}
		if (fp != NULL) {
			system("cls");
			stage = 's';
			showChoice(stage);
			choice = userChoice(0, 2);
			if (choice == '1') {
				system("cls");
				fread(&topten, sizeof(topten), 1, fp);
				int i;
				int j;
				Record score;
				Id pID;

				i = 0;
				j = 0;
				showLogo();
				printf("%c-------------------------%c\n", 218, 191);
				printf("|         TOP 10          |\n");
				printf("|-------------------------|\n");
				printf("|     NOME    PUNTEGGIO   |\n");
				printf("|-------------------------|\n");
				while (i < 10) {
					printf("| %d. ", i + 1);
					if (i < 9) {
						printf(" ");
					}
					score = getRecord(topten, i);
					pID = getPlayerId(topten, i);
					j = 0;
					while (j < MAX_DIM_ID) {
						printf("%c", getId(pID, j));
						j++;
					}
					printf("        ");
					if (getScore(score) < 10) {
						printf(" ");
					}
					printf("%d       |\n", getScore(score));
					i++;
				}
				printf("%c-------------------------%c\n", 192, 217);
				backToMenu();
			} else if (choice == '2') {
				cleanTop10(fp, level);
				backToMenu();
			} else {
				system("cls");
				menu();
			}
		}

	}
	return;
}

void cleanTop10(FILE *fp, int level) {
	Topten topten;
	Id pid;
	Record s;
	Parameters param;
	int i;
	i = 0;
	while (i < MAX_DIM_ID - 1) {
		pid = setID(pid, i, '_');
		i++;
	}
	i = 0;
	while (i < 10) {
		topten = setPlayerId(topten, i, pid);
		i++;
	}
	i = 0;
	s = setScore(s, 99);
	while (i < 10) {
		topten = setRecord(topten, i, s);
		i++;
	}
	Match m;
	if (level == 1) {
		param = setNumSymbol(param, NUM_SYMBOL_BASIC);
	} else if (level == 2) {
		param = setNumSymbol(param, NUM_SYMBOL_INTERMEDIATE);
	} else if (level == 3) {
		param = setNumSymbol(param, NUM_SYMBOL_ADVANCED);
	}
	m = setParameters(m, param);

	saveTop10(m, topten);
	return;
}
