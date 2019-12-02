/*******************************
 CS 362 - Final Project Part B
 Author: Kendrick Chu
 Date: 12/1/19
 Description: Unit test for ambassador card in dominion game.
 *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//#define TESTCARD "ambassador"

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
    int k[10] = {adventurer, ambassador, feast, gardens, mine, remodel, smithy, village, baron, estate};
    
    //initialize game state and player cards
    initializeGame(numPlayers, k, seed, &state);
    state.handCount[thisPlayer] = 5;
    state.hand[thisPlayer][0] = ambassador;
    state.hand[thisPlayer][1] = state.hand[thisPlayer][2] = state.hand[thisPlayer][3] = state.hand[thisPlayer][4] = silver;
    
    handpos = 0;
    printf("***************Beginning Test for Bug 10***************\n");
    
    //copy the current game state to a test case
    memcpy(&test, &state, sizeof(struct gameState));
    
    //player chooses to return silver card
    choice1 = 1;
    choice2 = 2;
    choice3 = -1;
    chosenCard = test.hand[thisPlayer][choice1];
    
    cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);
    
    printf("Player's hand should be decremented by 3\n");
    assert(state.handCount[thisPlayer] - 3, test.handCount[thisPlayer]);
    
    //get number of silver cards in player's hand before and after function call
    stateNumSilver = 0;
    testNumSilver = 0;
    int i;
    for(i = 0; i < state.handCount[thisPlayer]; i++) {
        if(state.hand[thisPlayer][i] == silver) {
            stateNumSilver++;
        }
    }
    for(i = 0; i < test.handCount[thisPlayer]; i++) {
        if(test.hand[thisPlayer][i] == silver) {
            testNumSilver++;
        }
    }
    
    printf("Player should have 2 less silver cards in hand\n");
    aasert(stateNumSilver - 2, testNumSilver);

    printf("***************Ending Test for Bug 10***************\n");
    
    return 0;
}
