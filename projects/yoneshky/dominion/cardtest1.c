
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

#define TESTCARD "adventurer"

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
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
	testG.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = adventurer;
	G.handCount[thisPlayer]++;
	
	cardEffect(adventurer, 0, 0, 0, &testG, testG.handCount[thisPlayer] - 2, 0);
	
	printf("--- Testing Adveturer Should be in Hand if Wrong HandPos given ---\n");
	
	//flag set if adventurer is discarded properly
	int advFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == adventurer) {
			printf("Adventurer not properly discarded, test passed!\n");
			advFlag = -1;
		}
	}
	if(advFlag >= 0) {
		printf("Adventurer properly discarded, test failed!\n");
	}

	printf("--- Boundary test On Deck with different Treasure Counts ---\n");
	printf("--- Deck has 2 Treasure ---\n");
	memcpy(&testG1, &G, sizeof(struct gameState));
	for(i = 0; i < testG1.deckCount[thisPlayer] - 2; i++) {
		testG1.deck[thisPlayer][i] = estate;
	}
	for(i = testG1.deckCount[thisPlayer] - 2; i < testG1.deckCount[thisPlayer]; i++) {
		testG1.deck[thisPlayer][i] = copper;
	}
	
	testG1.hand[thisPlayer][testG1.handCount[thisPlayer]] = adventurer;
	testG1.handCount[thisPlayer]++;
	
	if(cardEffect(adventurer, choice1, choice2, choice3, &testG1, testG1.handCount[thisPlayer], &bonus)) {
		printf("Test Passed\n");
	}
	
	printf("--- Deck has 3 Treasure ---\n");
	memcpy(&testG2, &G, sizeof(struct gameState));
	for(i = 0; i < testG2.deckCount[thisPlayer] - 3; i++) {
		testG2.deck[thisPlayer][i] = estate;
	}
	for(i = testG2.deckCount[thisPlayer] - 3; i < testG2.deckCount[thisPlayer]; i++) {
		testG2.deck[thisPlayer][i] = copper;
	}
	
	testG2.hand[thisPlayer][testG2.handCount[thisPlayer]] = adventurer;
	testG2.handCount[thisPlayer]++;
	
	if(cardEffect(adventurer, choice1, choice2, choice3, &testG2, testG2.handCount[thisPlayer], &bonus)) {
		printf("Test Passed\n");
	}
	
	printf("--- Deck has 0 Treasure ---\n");
	memcpy(&testG3, &G, sizeof(struct gameState));
	for(i = 0; i < testG3.deckCount[thisPlayer]; i++) {
		testG3.deck[thisPlayer][i] = estate;
	}
	
	testG3.hand[thisPlayer][testG3.handCount[thisPlayer]] = adventurer;
	testG3.handCount[thisPlayer]++;
	
	if(cardEffect(adventurer, choice1, choice2, choice3, &testG3, testG3.handCount[thisPlayer], &bonus)) {
		printf("Test Passed\n");
	}
	
    printf("--- Card Test 1 Complete! ---\n");
    
    return 0;
}
