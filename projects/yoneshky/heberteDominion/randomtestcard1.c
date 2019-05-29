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

#define TESTCARD "smithy"

int main() {
	
	int n;
	int smiPass = 0;
	int smiFail = 0;
	printf("--- RANDOM TEST ON SMITHY ---\n");
	srand(time(NULL));
	
	for(n = 0; n < 2000; n++) {
		
		printf("--- Executing test: %d ---\n", n+1);
		int seed = 1000;
		int numPlayers = rand()%4 + 1;
		int thisPlayer = 0;
		int testPass = 0;
		int i, j;
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
		
		//mimic smithy draw to use hand pos for smithy effect
		testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
		testG.handCount[thisPlayer]++;
		G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy;
		G.handCount[thisPlayer]++;
		
    	smithyEffect(&testG, testG.handCount[thisPlayer] - 1);
		int testCount = 0;
		
		//test 3 cards drawn
		int initHandCount = 0;
		int finHandCount = 0;
		int initDeckCount = 0;
		int finDeckCount = 0;
		
		//test hand count +2
		initHandCount = G.handCount[thisPlayer];
		finHandCount = testG.handCount[thisPlayer];
		if(finHandCount == initHandCount + 2) {
			testPass++;
		}
		testCount++;
		
		//test deck Count 3 less than starting
		initDeckCount = G.deckCount[thisPlayer];
		finDeckCount = testG.deckCount[thisPlayer];
		if(finDeckCount == initDeckCount - 3) {
			testPass++;
		}
		testCount++;
		
		//test if smithy was discarded
		//flag set if smithy is discarded properly
		int smithyFlag = 0;
		for(i = 0; i < testG.handCount[thisPlayer]; i++) {
			if (testG.hand[thisPlayer][i] == smithy) {
				smithyFlag = -1;
			}
		}
		if(smithyFlag < 0) {
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
			smiPass++;
			printf("Test #%d passed!\n", n+1);
			printf("Tests Passed: %d, Test Count: %d \n", testPass, testCount);
		}
		else {
			smiFail++;
			printf("Test #%d failed!\n", n+1);
			printf("Test Passed: %d, Test Count: %d \n", testPass, testCount);
		}
		
	}
	printf("Out of %d tests -> Pass:  %d, Fail:  %d\n", 2000, smiPass, smiFail);
}
