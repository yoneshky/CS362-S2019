/*
 * cardtest2.c
 * Kyle Yoneshige
 */

/* Adapted from cardtest4.c provided by professor
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TESTCARD "smithy"

void asserttrue(int x, int y) {
	if(x == y) {
		printf("Assertion Passed\n");
	}
	else {
		printf("Assertion Failed\n");
	}
}

void assertlessequals(int x, int y) {
	if(x <= y) {
		printf("Assertion Passed\n");
	}
	else {
		printf("Assertion Failed\n");
	}
}

int main() {
    int i, j, m;
	int choice1, choice2, choice3;
	int *bonus;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    //gamestate G and testG adapted from cardtest4.c provided by instructor
    struct gameState G, testG, testG1, testG2, testG3;
    
    int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, minion};
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("--- Card Test On: %s ---\n", TESTCARD);
    

	//negative test on wrong hand position provided to cardEFfect
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
	testG.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = smithy;
	G.handCount[thisPlayer]++;
	
	cardEffect(smithy, 0, 0, 0, &testG, testG.handCount[thisPlayer] - 2, 0);
	
	printf("--- Testing Smithy Should be in Hand if Wrong HandPos given ---\n");
	
	//flag set if smithy is discarded properly
	int smithFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == smithy) {
			printf("Smithy not properly discarded, test passed!\n");
			smithFlag = -1;
		}
	}
	if(smithFlag >= 0) {
		printf("Smithy properly discarded, test failed!\n");
	}

	printf("--- Boundary test On Deck with different Deck Counts ---\n");
	printf("--- Deck has 4 cards ---\n");
	memcpy(&testG1, &G, sizeof(struct gameState));
	testG1.deckCount[thisPlayer] = 4;
	
	testG1.hand[thisPlayer][testG1.handCount[thisPlayer]] = smithy;
	testG1.handCount[thisPlayer]++;
	
	if(cardEffect(smithy, choice1, choice2, choice3, &testG1, testG1.handCount[thisPlayer], 0) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
	}
	
	printf("--- Deck has 2 Cards ---\n");
	//this assumes smithy will be reshuffled into deck to make a deck size of 3 cards
	memcpy(&testG2, &G, sizeof(struct gameState));
	testG2.deckCount[thisPlayer] = 2;
	
	testG2.hand[thisPlayer][testG2.handCount[thisPlayer]] = smithy;
	testG2.handCount[thisPlayer]++;
	
	if(cardEffect(village, choice1, choice2, choice3, &testG2, testG2.handCount[thisPlayer], 0) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
	}
	
	printf("--- Deck has 0 Cards ---\n");
	memcpy(&testG3, &G, sizeof(struct gameState));
	testG3.deckCount[thisPlayer] = 0;
	
	testG3.hand[thisPlayer][testG3.handCount[thisPlayer]] = smithy;
	testG3.handCount[thisPlayer]++;
	
	if(cardEffect(village, choice1, choice2, choice3, &testG3, testG3.handCount[thisPlayer], 0) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
	}
	
    printf("--- Card Test 2 Complete! ---\n");
    
    return 0;
}
