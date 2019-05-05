
/* Adapted from cardtest4.c provided by professor
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TESTCARD "sea_hag"

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
	int i, j;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    //gamestate G and testG adapted from cardtest4.c provided by instructor
    struct gameState G, testG;
    
    int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, minion};
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("--- Unit Test On: %s ---\n", TESTCARD);
    
    printf("--- Testing Top card is Discarded ---\n");
	
	//mimic sea_hag draw to use hand pos for seaHag effect
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = sea_hag;
	testG.handCount[thisPlayer]++;
	G.hand[thisPlayer][testG.handCount[thisPlayer]] = sea_hag;
	G.handCount[thisPlayer]++;
	
    seaHagEffect(&testG, testG.handCount[thisPlayer] - 1);
	
	int initTopCard;
	int finTopCard;
	
	for(i = 0; i < testG.numPlayers; i++) {
		initTopCard = G.deck[i][state->deckCount[i]--];
		finTopCard = testG.deck[i][state->deckCount[i]--];
		
		if (initTopCard == finTopCard && initTopCard != curse) {
				printf("Player: %d, top card was not properly discarded\n", i)
		}
		else {
				printf("Player: %d, top card was properly discarded\n", i)
		}
	}
	
	printf("Testing Top of Deck is Curse\n");
	for(i = 0; i < testG.numPlayers; i++) {
		initTopCard = G.deck[i][state->deckCount[i]--];
		finTopCard = testG.deck[i][state->deckCount[i]--];
		
		if (curse == finTopCard) {
			printf("Player: %d, top card was properly discarded\n", i)
		}
		else if (curse == initTopCard && testG.deckCount == G.deckCount) {
			printf("Player: %d, top card was properly discarded\n", i)

		}
		else {
			printf("Player: %d, top card was not properly discarded\n", i)
		}
	}
	
	
    printf("Testing Deck Count is The Same as Starting\n");
    
    int initDeckCount = G.deckCount[thisPlayer];
    int finDeckCount = testG.deckCount[thisPlayer];
    
    printf("Final Deck Count = %d, expected = %d\n", finDeckCount, initDeckCount);
    asserttrue(finDeckCount, initDeckCount);
	
	printf("Testing Curse Supply is Less Than Starting\n");
	
	int initCurseSupply = G.supplyCount[curse];
	int finCurseSupply = testG.supplyCount[curse];
	
	if(initCurseSupply <= numPlayers) {
		printf("Final Curse Supply Count = %d, expected = %d\n", finCurseSupply, 0);
		asserttrue(finCurseSupply, 0);
	}
	else {
		printf("Final Curse Supply Count = %d, expected = %d\n", finCurseSupply, initCurseSupply-numPlayers);
		asserttrue(finCurseSupply, initCurseSupply-numPlayers);
	}
    
    printf("Testing Great Hall Not in Hand Anymore\n");
	
	//flag set if sea hag is discarded properly
	int seaHagFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == sea_hag) {
			printf("Sea Hag not properly discarded\n");
			seaHagFlag = -1;
		}
	}
	if(seaHagFlag >= 0) {
		printf("Sea Hag properly discarded\n");
	}
	
	printf("Testing Action Count is 1\n");
	
	int initNumActions = G.numActions;
	int finNumActions = testG.numActions;
	
	printf("Final number of actions = %d, expected = %d\n", finNumActions, initNumActions);
	asserttrue(finNumActions, initNumActions);
	
	printf("Testing Buy Count is unchanged\n");
	
	int initBuyCount = G.numBuys;
	int finBuyCount = testG.numBuys;
	
	printf("Final buy count = %d, expected = %d\n", finBuyCount, initBuyCount);
	asserttrue(finBuyCount, initBuyCount);
    
    printf("Testing No State Change for Other Player\n");
    
    int initHandCountPlayer2 = G.handCount[thisPlayer+1];
    int finHandCountPlayer2 = testG.handCount[thisPlayer+1];
    
    printf("Other Player Hand Count = %d, expected = %d\n", finHandCountPlayer2, initHandCountPlayer2);
    asserttrue(finHandCountPlayer2, initHandCountPlayer2);
    
    int initDeckCountPlayer2 = G.deckCount[thisPlayer+1];
    int finDeckCountPlayer2 = testG.deckCount[thisPlayer+1];
    
    printf("Other Player Deck Count = %d, expected = %d\n", finDeckCountPlayer2, initDeckCountPlayer2);
    asserttrue(finDeckCountPlayer2, initDeckCountPlayer2);
    
    
    printf("Testing No State Change for Victory Card Pile and Kingdom Card Pile\n");
    
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
	printf("Testing if each kingdom supply is unchanged\n");
	for(i = 0; i < 10; i++) {
		printf("kingdom card: %d\n", i+1);
    	asserttrue(initKingdomCount[i], finKingdomCount[i]);
	}
	printf("Kingdom Supply unchanged\n");
	
	printf("Testing if each victory supply is unchanged\n");
	
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

	printf("Testing if each treasure supply is unchanged\n");
	
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
    
    printf("--- Unit Test 4 Complete! ---\n");
    
    return 0;
}
