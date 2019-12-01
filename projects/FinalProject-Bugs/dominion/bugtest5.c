#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> 
#include <time.h>


int myAssert(int boolean) {
    if (boolean == 0) {
        printf("FAILED\n");
        return 0;
    }

    printf("PASSED\n");
    return 1;
}

int main() {

    int seed = 1000;
    // set your card array    
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;  // the original state
    int curPlayer = 0, res;
    initializeGame(2, k, seed, &G);
    G.whoseTurn = curPlayer;
    G.discardCount[curPlayer] = 1;
    G.discard[curPlayer][0] = estate;
    G.handCount[curPlayer] = 1;
    G.hand[curPlayer][0] = estate;
    G.deckCount[curPlayer] = 2;
    G.deck[curPlayer][0] = estate;
    G.deck[curPlayer][1] = duchy;

    res  = scoreFor(curPlayer, &G);	
    printf("***************Begin Unit Testing for bug 5******************\n");
    printf("Results score of: %d. Expected 6.\n", res);    
    myAssert(res == 6);

    return 0;
} 

