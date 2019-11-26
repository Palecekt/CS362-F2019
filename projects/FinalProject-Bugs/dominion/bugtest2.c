//This is the unit test for the mine cardEffect function

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
void assert(int a, int b){
    if(a == b){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\n");
    }
}
int main(){
    printf("***************Beginning Test for Bug 2***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { ambassador, tribute, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;

    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test
    test.handCount[0] = 2;
    test.hand[0][0] = mine;
    test.hand[0][1] = copper;
    int choice1 = 1;
    int choice2 = copper;
    int choice3 = -1;
    memcpy(&G, &test, sizeof(struct gameState));
    int result = cardEffect(mine, choice1, choice2, choice3, &test, 0, 0);
    
    //Assert cardEffect return value is 0
    printf("Result cardEffect function returned %d . Expected 0.\n", result);
    assert(result, 0);
 
    return 0;
}
