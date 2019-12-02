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
    initializeGame(2, k, seed, &G);
    G.whoseTurn = 0;
    G.coins = 0;
    G.hand[0][0] = estate;

    cardEffect(baron, 1, 0, 0, &G, 0, 5);
    printf("***************Begin Unit Testing for bug 8******************\n");
    printf("Results of bonus coin added from baron case in cardEffect: %d. Expected %d.\n", G.coins, 9);
    myAssert(G.coins == 9);
 
    initializeGame(2, k, seed, &G);
    G.whoseTurn = 0;
    G.coins = 0;
    cardEffect(minion, 1, 0, 0, &G, 0, 5);
    printf("Results of bonus coin added from minion case in cardEffect: %d. Expected %d.\n", G.coins, 7);
    myAssert(G.coins == 7);

    G.whoseTurn = 0;
    int nextPlayer = 1;
    G.discardCount[nextPlayer] = 0;
    G.deckCount[nextPlayer] = 4;
    G.coins = 0;
    G.deck[nextPlayer][0] = copper;
    G.deck[nextPlayer][1] = estate;

    cardEffect(tribute, 1, 0, 0, &G, 0, 5);
    printf("Results of bonus coin added from tribute case in cardEffect: %d. Expected %d.\n", G.coins, 7);
    myAssert(G.coins == 7);

    initializeGame(2, k, seed, &G);
    G.whoseTurn = 0;
    G.coins = 0;
    cardEffect(embargo, 0, 0, 0, &G, 0, 5);
    printf("Results of bonus coin added from embargo case in cardEffect: %d. Expected %d.\n", G.coins, 7);
    myAssert(G.coins == 7);

    return 0;
}

