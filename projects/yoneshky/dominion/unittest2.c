
/* Adapted from cardtest4.c provided by professor
 * Include the following lines in your makefile:
 *
 * unittest2: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    
    printf("--- Testing If Three cards are drawn ---\n");
	
	//mimic smithy draw to use hand pos for smithy effect
	testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
	testG.handCount[thisPlayer]++;
	
    smithyEffect(&testG, testG.handCount[thisPlayer] - 1);
	
	
    //initial treasure in hand count
    int initHandCount = G.handCount[thisPlayer];
	int finHandCount = testG.handCount[thisPlayer];
	
	printf("Hand count = %d, expected = %d\n", finHandCount, initHandCount + 2);
	asserttrue(initHandCount, finHandCount);
	
    printf("Testing Deck Count is 3 less than starting\n");
    
    int initDeckCount = G.deckCount[thisPlayer];
    int finDeckCount = testG.deckCount[thisPlayer];
    
    printf("Final Deck Count = %d, expected = %d\n", finDeckCount, initDeckCount);
    asserttrue(finDeckCount, initDeckCount - 3);
    
    printf("Testing Smithy Not in Hand Anymore\n");
	
	//flag set if smithy is discarded properly
	int smithyFlag = 0;
	
	for(i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == smithy) {
			printf("Smithy not properly discarded\n");
			smithyFlag = -1;
			return;
		}
	}
	if(smithyFlag >= 0) {
		printf("Smithy properly discarded\n");
	}
    
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
    
    printf("--- Unit Test 2 Complete! ---\n");
    
    return 0;
}
