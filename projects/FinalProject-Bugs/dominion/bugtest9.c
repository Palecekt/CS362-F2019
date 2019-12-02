/*******************************
 CS 362 - Final Project Part B
 Author: Kendrick Chu
 Date: 12/1/19
 Description: Unit test for tribute card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//#define TESTCARD "tribute"

void assert(int expectedResult, int actualResult) {
    if(expectedResult != actualResult) {
        printf("Test failed\n");
    }
    else {
        printf("Test passed\n");
    }
}

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = thisPlayer + 1;
    
    struct gameState state, test;
    int k[10] = {adventurer, ambassador, duchy, gardens, mine, tribute, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.handCount[thisPlayer] = 5;
    state.hand[thisPlayer][0] = tribute;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    state.deckCount[nextPlayer] = 2;
    state.discardCount[nextPlayer] = 0;
    state.deck[nextPlayer][0] = copper;
    state.deck[nextPlayer][1] = copper;
    
    handpos = 0;
    //set coins to better detect bugs
    state.coins = 1;
    printf("***************Beginning Test for Bug 9***************\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 1\n");
    assert(state.handCount[thisPlayer] - 1, test.handCount[thisPlayer]);
    
    printf("Player should have unchanged number of actions\n");
    assert(state.numActions, test.numActions);
    
    printf("Player's coins should be incremented by 2\n");
    assert(state.coins + 2, test.coins);
    
    printf("***************Ending Test for Bug 9***************\n");
    
    return 0;
}
