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
    int  res, expected = 0, prevActions, nextPlayer = 1;
    initializeGame(2, k, seed, &G);
   
    G.whoseTurn = 0;
    G.discardCount[nextPlayer] = 0;
    G.deckCount[nextPlayer] = 4;
    G.deck[nextPlayer][0] = copper;
    G.deck[nextPlayer][1] = silver;

    prevActions = G.numActions;
    res = cardEffect(tribute, 0, 0, 0, &G, 0, 0);

    printf("***************Begin Unit Testing for bug 7******************\n");
    printf("Results of sucessfull tribute card call: %d. Expected %d.\n", res, expected);
    myAssert(res == expected); 
    printf("Results numActions of: %d. Expected %d.\n", G.numActions, prevActions);
    myAssert(G.numActions == prevActions);

    return 0;
}


