
/* Adapted from cardtest4.c provided by professor
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
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

#define TESTCARD "adventurer"


int main() {
    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    //gamestate G and testG adapted from cardtest4.c provided by instructor
    struct gameState G, testG;
    
    int k[10] = {adventurer, smithy, council_room, feast, mine, remodel, village, baron, great_hall, minion};
    
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("--- Unit Test On: %s ---\n", TESTCARD);
    
    printf("--- Testing If Two Additional Treasure Cards Are Drawn ---\n");
    adventurerEffect(testG);
	
	//line 38
    //initial treasure in hand count
    int initTreasureCount;
    int initCards;
    
    for(i = 0; i < G.handCount[thisPlayer]; i++) {
        initCards = G.hand[thisPlayer][i];
        if(initCards == copper || initCards == silver || initCards == gold) {
            initTreasureCount++;
        }
    }
    //line 49
    //final treasure in hand count
    int finTreasureCount;
    int finCards;
    
    for(i = 0; i < testG.handCount[thisPlayer]; i++) {
        finCards = testG.hand[thisPlayer][i];
        if(finCards == copper || finCards == silver || finCards == gold) {
            finTreasureCount++;
        }
    }
    
    printf("Drawn treasure count = %d, expected = %d\n", finTreasureCount - initTreasureCount, 2);
    assert(finTreasureCount == 2);
    
    printf("Testing Deck Count is at least 2 Less Than Starting Count\n");
    
    int initDeckCount = G.deckCount[thisPlayer];
    int finDeckCount = testG.deckCount[thisPlayer];
    
    printf("Final Deck Count = %d, expected (at most) = %d\n", finDeckCount, initDeckCount - 2);
    assert(finDeckCount <= initDeckCount - 2);
    
    printf("Testing Hand Count Is 2 More Than Starting Hand\n");
    
    int initHandCount = G.handCount[thisPlayer];
    int finHandCount = testG.handCount[thisPlayer];
    
    printf("Final Hand Count = %d, expected = %d\n", finHandCount, initHandCount + 1);
    assert(finHandCount == initHandCount +1);
    
    printf("Testing No State Change for Other Player\n");
    
    int initHandCountPlayer2 = G.handCount[thisPlayer+1];
    int finHandCountPlayer2 = testG.handCount[thisPlayer+1];
    
    printf("Other Player Hand Count = %d, expected = %d\n", finHandCountPlayer2, initHandCountPlayer2);
    assert(finHandCountPlayer2 == initHandCountPlayer2);
    
    int initDeckCountPlayer2 = G.deckCount[thisPlayer+1];
    int finDeckCountPlayer2 = testG.deckCount[thisPlayer+1];
    
    printf("Other Player Deck Count = %d, expected = %d\n", finDeckCountPlayer2, initDeckCountPlayer2);
    assert(finDeckCountPlayer2 == initDeckCountPlayer2);
    
    
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
	
	for(i = 0; i < 10; i++) {
    	assert(initKingdomCount[i] = finKingdomCount[i]);
	}
    
    int initEstateCount = G.supplyCount[estate];
    int initDuchyCount = G.supplyCount[duchy];
    int initProvinceCount = G.supplyCount[province];
    
    int finEstateCount = testG.supplyCount[estate];
    int finDuchyCount = testG.supplyCount[duchy];
    int finProvinceCount = testG.supplyCount[province];
    
    printf("Estate Supply Count = %d, expected = %d\n", finEstateCount, initEstateCount);
    assert(finEstateCount == initEstateCount);
    
    printf("Duchy Supply Count = %d, expected = %d\n", finDuchyCount, initDuchyCount);
    assert(finDuchyCount == initDuchyCount);
    
    printf("Province Supply Count = %d, expected = %d\n", finEstateCount, initEstateCount);
    assert(finProvinceCount == initProvinceCount);
    
    printf("--- Unit Test 1 Complete! ---\n");
    
    return 0;
}
