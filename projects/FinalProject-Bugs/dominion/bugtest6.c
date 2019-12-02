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
    int res, expected;
    int choice1 = curse;
    initializeGame(2, k, seed, &G);

    G.whoseTurn = 0;
    G.handCount[0] = 3;
    G.supplyCount[curse] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = curse;
    }

    expected = G.handCount[0] + 1;

    cardEffect(feast, choice1, 0, 0, &G, 0, 0); 
    res = G.handCount[0];

    printf("***************Begin Unit Testing for bug 7******************\n");
    printf("Results of player1 handCount: %d. Expected %d.\n", res, expected);
    myAssert(res == expected);

    return 0;
}
