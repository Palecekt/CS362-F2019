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
    printf("***************Beginning Test for Bug 1***************\n");
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
    int choice2 = silver;
    int choice3 = -1;
    memcpy(&G, &test, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &test, 0, 0);
    //Assert number of copper cards in hand reduced by 1
    int testCoppers = 0;
    int GCoppers = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == mine){
            testCoppers++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == mine){
            GCoppers++;
        }
    }
    printf("Result %d copper in hand. Expected %d.\n", testCoppers, GCoppers-1);
    assert(testCoppers, GCoppers-1);
    //Assert number coppers in discard is unchanged
    int testCopper = 0;
    int GCopper = 0;
    for(int i = 0; i < test.discardCount[0]; i++){
        if (test.discard[0][i] == copper){
            testCopper++;
        }
    }
    for(int i = 0; i < G.discardCount[0]; i++){
        if (G.discard[0][i] == copper){
            GCopper++;
        }
    }
    printf("Result %d copper in discard. Expected %d.\n", testCopper, GCopper);
    assert(testCopper, GCopper); 
 
    return 0;
}
