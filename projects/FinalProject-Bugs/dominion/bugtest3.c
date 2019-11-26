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
    test.hand[0][0] = remodel;
    test.hand[0][1] = gold;
    int handPos = 0;
    int card = remodel;
    int choice1 = 1;
    int choice2 = silver;
    int choice3 = -1;
    int bonus = 0;
    memcpy(&G, &test, sizeof(struct gameState));
    int result = cardEffect(card, choice1, choice2, choice3, &test, handPos, &bonus);
    
    //Assert cardEffect return value is 0
    printf("Result cardEffect function returned %d . Expected 0.\n", result);
    assert(result, 0);

    //Assert remodel card removed from hand
    int testRemodel = 0;
    int GRemodel = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == remodel){
            testRemodel++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == remodel){
            GRemodel++;
        }
    }
    printf("Result %d remodel in hand. Expected %d.\n", testRemodel, GRemodel);
    assert(testRemodel, GRemodel - 1);

    //assert gold card removed from hand
    int testGold = 0;
    int GGold = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == gold){
            testGold++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == gold){
            GGold++;
        }
    }
    printf("Result %d gold in hand. Expected %d.\n", testGold, GGold);
    assert(testGold, GGold - 1); 
    //assert silver card added to hand
    int testSilver = 0;
    int GSilver = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == silver){
            testSilver++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == silver){
            GSilver++;
        }
    }
    printf("Result %d silver in hand. Expected %d.\n", testSilver, GSilver);
    assert(testSilver, GSilver + 1); 
    return 0;
}
