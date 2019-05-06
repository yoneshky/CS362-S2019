/*
 * cardtest3.c
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

#define TESTCARD "village"

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
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
	testG.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = village;
	G.handCount[thisPlayer]++;
	
	cardEffect(village, 0, 0, 0, &testG, testG.handCount[thisPlayer] - 2, 0);
	
	printf("--- Testing village Should be in Hand if Wrong HandPos given ---\n");
	
	//flag set if village is discarded properly
	int vilFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == village) {
			printf("Village not properly discarded, test passed!\n");
			vilFlag = -1;
		}
	}
	if(vilFlag >= 0) {
		printf("Village properly discarded, test failed!\n");
	}
	
	printf("--- Boundary test On Deck with different Deck Counts ---\n");
	printf("--- Deck has 2 cards ---\n");
	memcpy(&testG1, &G, sizeof(struct gameState));
	testG1.deckCount[thisPlayer] = 2;
	
	testG1.hand[thisPlayer][testG1.handCount[thisPlayer]] = village;
	testG1.handCount[thisPlayer]++;
	
	if(cardEffect(village, choice1, choice2, choice3, &testG1, testG1.handCount[thisPlayer], 0) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
	}
	
	printf("--- Deck has 1 Cards ---\n");
	//this assumes village will be reshuffled into deck to make a deck size of 2 cards
	memcpy(&testG2, &G, sizeof(struct gameState));
	testG2.deckCount[thisPlayer] = 1;
	
	testG2.hand[thisPlayer][testG2.handCount[thisPlayer]] = village;
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
	
	testG3.hand[thisPlayer][testG3.handCount[thisPlayer]] = village;
	testG3.handCount[thisPlayer]++;
	
	if(cardEffect(village, choice1, choice2, choice3, &testG3, testG3.handCount[thisPlayer], 0) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
	}
	
	//positive tests
	printf("--- Testing Hand Count is Correct ---\n");
	int initHandCount = G.handCount[thisPlayer];
	int finHandCount = testG.handCount[thisPlayer];
	
	printf("Hand count = %d, expected = %d\n", finHandCount, initHandCount);
	asserttrue(initHandCount, finHandCount);
	
	printf("--- Testing Deck Count is 1 less than starting ---\n");
	
	int initDeckCount = G.deckCount[thisPlayer];
	int finDeckCount = testG.deckCount[thisPlayer];
	
	printf("Final Deck Count = %d, expected = %d\n", finDeckCount, initDeckCount - 1);
	asserttrue(finDeckCount, initDeckCount - 1);
	
	printf("--- Testing Action Count is 3 ---\n");
	
	int initNumActions = G.numActions;
	int finNumActions = testG.numActions;
	
	printf("Final number of actions = %d, expected = %d\n", finNumActions, initNumActions + 2);
	asserttrue(finNumActions, initNumActions + 2);
	
	printf("--- Testing Buy Count is unchanged ---\n");
	
	int initBuyCount = G.numBuys;
	int finBuyCount = testG.numBuys;
	
	printf("Final buy count = %d, expected = %d\n", finBuyCount, initBuyCount);
	asserttrue(finBuyCount, initBuyCount);
	
	printf("--- Testing No State Change for Other Player ---\n");
	
	int initHandCountPlayer2 = G.handCount[thisPlayer+1];
	int finHandCountPlayer2 = testG.handCount[thisPlayer+1];
	
	printf("Other Player Hand Count = %d, expected = %d\n", finHandCountPlayer2, initHandCountPlayer2);
	asserttrue(finHandCountPlayer2, initHandCountPlayer2);
	
	int initDeckCountPlayer2 = G.deckCount[thisPlayer+1];
	int finDeckCountPlayer2 = testG.deckCount[thisPlayer+1];
	
	printf("Other Player Deck Count = %d, expected = %d\n", finDeckCountPlayer2, initDeckCountPlayer2);
	asserttrue(finDeckCountPlayer2, initDeckCountPlayer2);
	
	
	printf("--- Testing No State Change for Victory Card Pile and Kingdom Card Pile ---\n");
	
	int initKingdomCount[10];
	int finKingdomCount[10];
	
	for(i = adventurer; i <= treasure_map; i++) {
		for(j = 0; j < 10; j++) {
			if(k[j] == i) {
				initKingdomCount[j] = G.supplyCount[i];
			}
		}
	}
	
	for(i = adventurer; i <= treasure_map; i++) {
		for(j = 0; j < 10; j++) {
			if(k[j] == i) {
				finKingdomCount[j] = testG.supplyCount[i];
			}
		}
	}
	printf("--- Testing if each kingdom supply is unchanged ---\n");
	for(i = 0; i < 10; i++) {
		printf("kingdom card: %d\n", i+1);
		asserttrue(initKingdomCount[i], finKingdomCount[i]);
	}
	
	printf("--- Testing if each victory supply is unchanged ---\n");
	
	int initEstateCount = G.supplyCount[estate];
	int initDuchyCount = G.supplyCount[duchy];
	int initProvinceCount = G.supplyCount[province];
	
	int finEstateCount = testG.supplyCount[estate];
	int finDuchyCount = testG.supplyCount[duchy];
	int finProvinceCount = testG.supplyCount[province];
	
	printf("Estate Supply Count = %d, expected = %d\n", finEstateCount, initEstateCount);
	asserttrue(finEstateCount, initEstateCount);
	
	printf("Duchy Supply Count = %d, expected = %d\n", finDuchyCount, initDuchyCount);
	asserttrue(finDuchyCount, initDuchyCount);
	
	printf("Province Supply Count = %d, expected = %d\n", finEstateCount, initEstateCount);
	asserttrue(finProvinceCount, initProvinceCount);
	
	printf("--- Testing if each treasure supply is unchanged ---\n");
	
	int initCopperCount = G.supplyCount[copper];
	int initSilverCount = G.supplyCount[silver];
	int initGoldCount = G.supplyCount[gold];
	
	int finCopperCount = testG.supplyCount[copper];
	int finSilverCount = testG.supplyCount[silver];
	int finGoldCount = testG.supplyCount[gold];
	
	printf("Copper Supply Count = %d, expected = %d\n", finCopperCount, initCopperCount);
	asserttrue(finCopperCount, initCopperCount);
	
	printf("Silver Supply Count = %d, expected = %d\n", finSilverCount, initSilverCount);
	asserttrue(finSilverCount, initSilverCount);
	
	printf("Gold Supply Count = %d, expected = %d\n", finGoldCount, initGoldCount);
	asserttrue(finGoldCount, initGoldCount);
	
    printf("--- Card Test 3 Complete! ---\n");
	
	
    return 0;
}
