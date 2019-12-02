/*******************************
 CS 362 - Final Project Part B
 Author: Kendrick Chu
 Date: 12/1/19
 Description: Unit test for minion card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//#define TESTCARD "minion"

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
    
    struct gameState state, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.hand[thisPlayer][0] = minion;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = smithy;
    state.handCount[thisPlayer] = 5;
    
    //set other player's cards
    state.hand[1][0] = minion;
    state.hand[1][1] = state.hand[1][2] = state.hand[1][3] = state.hand[1][4] = copper;
    state.handCount[1] = 5;
    
    handpos = 0;
    printf("***************Beginning Test for Bug 11***************\n");
    
    //set coins to 1 to better detect issues with adding coins
    state.coins = 1;
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses neither to gain 2 coins nor discard and draw 4 cards
    choice1 = 0;
    choice2 = 0;
    choice3 = -1;
    
    int status = cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Invalid game state, choice 1 or choice 2 must be set.\n");
    assert(-1, status);
    
    printf("***************Ending Test for Bug 11***************\n");
    
    return 0;
}
