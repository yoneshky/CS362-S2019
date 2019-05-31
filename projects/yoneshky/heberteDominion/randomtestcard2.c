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
#include <assert.h>
#include <string.h>

#define TESTCARD "village"

int main() {
	
	int n;
	int vilPass = 0;
	int vilFail = 0;
	
	srand(time(NULL));
	printf("--- RANDOM TEST ON VILLAGE ---\n");
	for(n = 0; n < 2000; n++) {
		
		printf("--- Executing test: %d ---\n", n+1);
		int seed = 1000;
		int numPlayers = rand()%4 + 1;
		int thisPlayer = 0;
		int testPass = 0;
		int i, j;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		
		//gamestate G and testG adapted from cardtest4.c provided by instructor
		struct gameState G, testG;
		int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, minion};
		
		initializeGame(numPlayers, k, seed, &G);
		
		//randomize hand and deck count of all players
		for(i = 0; i < numPlayers; i++) {
			G.deckCount[i] = rand() % MAX_DECK +1;
			G.handCount[i] = rand() % MAX_HAND +1;
		}
		
		memcpy(&testG, &G, sizeof(struct gameState));
		
		//mimic smithy draw to use hand pos for VILLAGE effect
		testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
		testG.handCount[thisPlayer]++;
		G.hand[thisPlayer][G.handCount[thisPlayer]] = village;
		G.handCount[thisPlayer]++;
		
		cardEffect(village, choice1, choice2, choice3, &testG, testG.handCount[thisPlayer]-1, 0);
		int testCount = 0;
		
		//test 1 cards drawn
		int initHandCount = 0;
		int finHandCount = 0;
		int initDeckCount = 0;
		int finDeckCount = 0;
		
		//test hand count unchanged (card drawn but card discarded so net change is 0)
		initHandCount = G.handCount[thisPlayer];
		finHandCount = testG.handCount[thisPlayer];
		if(finHandCount == initHandCount) {
			testPass++;
		}
		testCount++;
		
		//test deck Count 1 less than starting
		initDeckCount = G.deckCount[thisPlayer];
		finDeckCount = testG.deckCount[thisPlayer];
		if(finDeckCount == initDeckCount - 1) {
			testPass++;
		}
		testCount++;
		
		//test if smithy was discarded
		//flag set if smithy is discarded properly
		int vilFlag = 0;
		for(i = 0; i < testG.handCount[thisPlayer]; i++) {
			if (testG.hand[thisPlayer][i] == village) {
				vilFlag = -1;
			}
		}
		if(vilFlag < 0) {
			testPass++;
		}
		testCount++;
		
		//test action count +2
		int initNumActions = G.numActions;
		int finNumActions = testG.numActions;
		if(initNumActions +2 == finNumActions) {
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
			vilPass++;
			printf("Test #%d passed!\n", n+1);
			printf("Tests Passed: %d, Test Count: %d \n", testPass, testCount);
		}
		else {
			vilFail++;
			printf("Test #%d failed!\n", n+1);
			printf("Test Passed: %d, Test Count: %d \n", testPass, testCount);
		}
		
	}
	printf("Out of %d tests -> Pass:  %d, Fail:  %d\n", 2000, vilPass, vilFail);
}
