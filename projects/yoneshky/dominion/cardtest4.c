
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

#define TESTCARD "salvager"

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
    
    int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, salvager};
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("--- Card Test On: %s ---\n", TESTCARD);
	
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = salvager;
	testG.handCount[thisPlayer]++;
	G.hand[thisPlayer][G.handCount[thisPlayer]] = salvager;
	G.handCount[thisPlayer]++;
	updateCoins(thisPlayer, &G, 0);
	int initCoin = G.coins;
	
	cardEffect(salvager, 0, 0, 0, &testG, testG.handCount[thisPlayer], 0);
	
	printf("--- Testing Buy Count is +1 ---\n");
	
	int initBuyCount = G.numBuys;
	int finBuyCount = testG.numBuys;
	
	printf("Final buy count = %d, expected = %d\n", finBuyCount, initBuyCount + 1);
	asserttrue(finBuyCount, initBuyCount + 1);
	
	printf("--- Testing Salvager Discard Selected Card and Cost Gain ---\n");
	
	//flag set if village is discarded properly
	int discardFlag = 0;
	
	printf("--- Choice to Discard Copper (0 Cost) ---\n");
	memcpy(&testG1, &G, sizeof(struct gameState));
	
	testG1.hand[thisPlayer][4] = copper;
	
	cardEffect(salvager, 5, 0, 0, &testG1, testG1.handCount[thisPlayer], 0);

		if (testG1.hand[thisPlayer][4] == copper) {
			printf("Copper Properly discarded, test passed!\n");
			discardFlag = -1;
		}
	
	if(discardFlag >= 0) {
		printf("Copper not properly discarded, test failed!\n");
	}
	
	printf("--- Coin Gain from Copper ---\n");
	
	updateCoins(thisPlayer, &testG1, 0);
	int copperCoinCount = testG1.coins;
	printf("Final Coin Count = %d, expected = %d\n", copperCoinCount, initCoin);
	asserttrue(copperCoinCount, initCoin);
	
	printf("--- Choice to Discard Silver (3 Cost) ---\n");
	memcpy(&testG2, &G, sizeof(struct gameState));
	discardFlag = 0;
	testG2.hand[thisPlayer][4] = silver;
	
	cardEffect(salvager, 5, 0, 0, &testG2, testG2.handCount[thisPlayer], 0);
	
	if (testG2.hand[thisPlayer][4] == silver) {
		printf("Silver Properly discarded, test passed!\n");
		discardFlag = -1;
	}
	
	if(discardFlag >= 0) {
		printf("Silver not properly discarded, test failed!\n");
	}
	
	printf("--- Coin Gain from Silver ---\n");
	
	updateCoins(thisPlayer, &testG2, 0);
	int silverCoinCount = testG2.coins;
	printf("Final Coin Count = %d, expected = %d\n", silverCoinCount, initCoin + 3);
	asserttrue(silverCoinCount, initCoin + 3);
	
	printf("--- Choice to Discard Gold (6 Cost) ---\n");
	memcpy(&testG3, &G, sizeof(struct gameState));
	discardFlag = 0;
	testG3.hand[thisPlayer][4] = gold;
	
	cardEffect(salvager, 5, 0, 0, &testG3, testG3.handCount[thisPlayer], 0);
	
	if (testG3.hand[thisPlayer][4] == gold) {
		printf("Gold Properly discarded, test passed!\n");
		discardFlag = -1;
	}
	
	if(discardFlag >= 0) {
		printf("Gold not properly discarded, test failed!\n");
	}
	
	printf("--- Coin Gain from Gold ---\n");
	
	updateCoins(thisPlayer, &testG3, 0);
	int goldCoinCount = testG3.coins;
	printf("Final Coin Count = %d, expected = %d\n", goldCoinCount, initCoin + 6);
	asserttrue(goldCoinCount, initCoin + 6);
	
	printf("--- Testing Salvager Not in Hand Anymore ---\n");
	
	//flag set if salvage is discarded properly
	int salvageFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == great_hall) {
			printf("salvager not properly discarded\n");
			salvageFlag = -1;
		}
	}
	if(salvageFlag >= 0) {
		printf("salvage properly discarded\n");
	}

	printf("--- Testing Hand Count is Correct ---\n");
	int initHandCount = G.handCount[thisPlayer];
	int finHandCount = testG.handCount[thisPlayer];
	
	printf("Hand count = %d, expected = %d\n", finHandCount, initHandCount - 2);
	asserttrue(initHandCount, finHandCount);
	
	printf("--- Testing Deck Count is 1 less than starting ---\n");
	
	int initDeckCount = G.deckCount[thisPlayer];
	int finDeckCount = testG.deckCount[thisPlayer];
	
	printf("Final Deck Count = %d, expected = %d\n", finDeckCount, initDeckCount - 1);
	asserttrue(finDeckCount, initDeckCount - 1);
	
	printf("--- Testing Action Count is unchanged---\n");
	
	int initNumActions = G.numActions;
	int finNumActions = testG.numActions;
	
	printf("Final number of actions = %d, expected = %d\n", finNumActions, initNumActions);
	asserttrue(finNumActions, initNumActions);
	
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
	
    printf("--- Card Test 4 Complete! ---\n");
	
	
    return 0;
}
