//
//  randomtestcard1.c
//  yoneshky-assignment-4
//
//  Created by Kyle Yoneshige on 5/15/19.
//  Copyright © 2019 Kyle Yoneshige. All rights reserved.
//
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int i, j, n, advPass = 0, testPass = 0, advFail = 0, initTreasure = 0, postTreasure = 0, treasureCount = 0;
	int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, minion};
	
	for(int n = 0; n < 2000; n++) {
		int seed = 1000;
		int numPlayers = rand()%5;
		int thisPlayer = 0;
		//gamestate G and testG adapted from cardtest4.c provided by instructor
		struct gameState G, testG;
		initializeGame(numPlayers, k, seed, &G);
		
		//randomize hand and deck count of all players
		for(i = 0; i < numPlayers; i++) {
			G.deckCount[i] = rand() % MAX_DECK;
			G.handCount[i] = rand() % MAX_HAND;
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		adventurerEffect(&testG);
		int testCount = 0;
		
		//test 2 treasure drawn
		int card;
		//treasure in hand count before adventurer
		for(i = 0; i < G.handCount[thisPlayer]; i++) {
			card = G.hand[thisPlayer][i];
			if(card == copper || card == silver || card == gold) {
				initTreasure++;
			}
		}
		//treasure in hand count after adventurer
		for(i = 0; i < testG.handCount[thisPlayer]; i++) {
			printf("Executing test: %d\n", n);
			card = testG.hand[thisPlayer][i];
			if(card == copper || card == silver || card == gold) {
				postTreasure++;
			}
		}
		
		treasureCount = postTreasure - initTreasure;
		if(treasureCount == 2) {
			testPass++;
		}
		testCount++;
		
		int initHandCount = 0;
		int finHandCount = 0;
		int initDeckCount = 0;
		int finDeckCount = 0;
		
		//test hand count +1
		initHandCount = G.handCount[thisPlayer];
		finHandCount = testG.handCount[thisPlayer];
		if(finHandCount == initHandCount + 1) {
			testPass++;
		}
		testCount++;
		
		//test deck Count -2
		initDeckCount = G.deckCount[thisPlayer];
		finDeckCount = testG.deckCount[thisPlayer];
		if(finDeckCount == initDeckCount - 2) {
			testPass++;
		}
		testCount++;
		
		//test no state change for all other players
		for(j = 1; j < numPlayers; j++) {
			initHandCount = G.handCount[j];
			finHandCount = testG.handCount[j];
			if(finHandCount == initHandCount) {
				testPass++;
			}
			testCount++;
			
			initDeckCount = G.deckCount[j];
			finDeckCount = testG.deckCount[j];
			if(finDeckCount == initDeckCount) {
				testPass++;
			}
			testCount++;
		}
		
		if(testCount == testPass) {
			advPass++;
		}
		else {
			advFail++;
		}
		
	}
	
	printf("Out of %d tests -> Pass:  %d, Fail:  %d\n", 2000, advPass, advFail);

}
