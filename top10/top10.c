#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include <time.h> // DA RIMUOVERE

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
		i++;
	}

	i = indexScore;
	while (i < 9) {
		topten = setRecord(topten, i + 1, getRecord(temp, i));
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
		if (getAttemptsSoFar(match) <= getScore(record)) {
			isTopScore = TRUE;
		}
		i++;
	}
	return isTopScore;
}

Topten addScoreInTopTen(Match match, Topten topten) {
	Record record;
	int indexScore;
	int found;
	int i;
	indexScore = 0;
	i = 0;
	found = FALSE;
	while (i < 10 && found == FALSE) {
		record = getRecord(topten, i);
		printf("[%d]: %d\n", i, getScore(record));
		if (getAttemptsSoFar(match) < getScore(record)) {
			indexScore = i;
			topten = rightShift(topten, indexScore);
			record = setScore(record, getAttemptsSoFar(match));
			topten = setRecord(topten, i, record);
			found = TRUE;
		}
		i++;
	}
	Id id;
	id = setPlayerId(id, 0, 'a');
	id = setPlayerId(id, 1, 'b');
	id = setPlayerId(id, 2, 'c');
	topten = setID(topten, indexScore, id);
	return topten;
}


Topten loadTop10(Match match) {
	Topten topten;
	FILE *fp;

	// OTTIMIZZARE: VARIABILE IN SCELTA DIFFICOLTA'
	if (getNumSymbol(getParam(match)) == NUM_SYMBOL_BASIC) {
		topten.level = 1;
		fp = fopen(BASTOP10PATH, "rb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_INTERMEDIATE) {
		topten.level = 2;
		fp = fopen(INTTOP10PATH, "rb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_ADVANCED) {
		topten.level = 3;
		fp = fopen(ADVTOP10PATH, "rb");
	}
	if (fp == NULL) {
		printf("ERRORE\n");
	}
	fread(&topten, sizeof(Topten), 1, fp);
	fclose(fp);
	return topten;
}

void saveTop10(Match match, Topten topten) {
	FILE *fp;

	// OTTIMIZZARE: VARIABILE IN SCELTA DIFFICOLTA'
	if (getNumSymbol(getParam(match)) == NUM_SYMBOL_BASIC) {
		topten.level = 1;
		fp = fopen(BASTOP10PATH, "wb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_INTERMEDIATE) {
		topten.level = 2;
		fp = fopen(INTTOP10PATH, "wb");
	} else if (getNumSymbol(getParam(match)) == NUM_SYMBOL_ADVANCED) {
		topten.level = 3;
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
	choice = ' ';
	printf("Scegliere la top 10 di quale livello di difficolta' si vuole visualizzare\n");
	printf("1. Principiante\n");
	printf("2. Intermedio\n");
	printf("3. Avanzato\n");
	printf("\n");
	printf("0. Torna al menu\n");
	choice = userChoice(0, 3);
	if (choice == '0') {
		menu();
	} else if (choice == '1') {
		fp = fopen(BASTOP10PATH, "rb");
	} else if (choice == '2') {
		fp = fopen(INTTOP10PATH, "rb");
	} else if (choice == '3') {
		fp = fopen(ADVTOP10PATH, "rb");
	}

	fread(&topten, sizeof(topten), 1, fp);

	int i;
	i = 0;
	int j;
	j = 0;
	Record score;
	Id pID;
	char value[MAX_DIM_ID];
	while (i < MAX_DIM_ID) {
		value[i] = getPlayerId(pID, i);
		i++;
	}



	i = 0;
	printf("NOME    POSIZIONE\n");
	while (i < 10) {
		score = getRecord(topten, i);
		j = 0;
		while (j < MAX_DIM_ID) {
			printf("%c", value[j]);
			j++;
		}
		printf("%d\n", getScore(score));
		i++;
	}

	return;
}

