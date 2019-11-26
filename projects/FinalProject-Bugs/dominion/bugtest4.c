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
    printf("***************Beginning Test for Bug 4***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { ambassador, tribute, feast, gardens, mine, remodel, smithy, village, treasure_map, sea_hag };

    // declare the game state
    struct gameState test;
    initializeGame(numPlayers, k, seed, &test);

    //Test
    test.supplyCount[estate] = 0;
    test.supplyCount[treasure_map] = 0;
    test.supplyCount[sea_hag] = 0;
    int result = isGameOver(&test);
    
    //Assert cardEffect return value is 0
    printf("Result isGameOver function returned %d . Expected 1.\n", result);
    assert(result, 1);
 
    return 0;
}
