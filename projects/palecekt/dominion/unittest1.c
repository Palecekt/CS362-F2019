//This is the unit test for the baron cardEffect function
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

void assert(int a, int b){
    if(a == b){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\n");
    }
}

int main(){
    printf("***************Beginning Tests for Baron***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;
    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test1 - Discard estate card
    printf("\n<<< Test 1 - Discard estate card >>>\n");
    test.hand[0][0] = baron;
    test.hand[0][1] = estate;
    memcpy(&G, &test, sizeof(struct gameState));
    baronEffect(1, &test, 0, 0);
    //Assert number of buys increased by 1
    printf("Result %d Buys. Expected %d.\n", test.numBuys, G.numBuys+1);
    assert(test.numBuys, G.numBuys+1);
    //Assert number of gold increased by 4
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins+4);
    assert(test.coins, G.coins+4);
    //Assert number of estate cards in hand reduced by 1
    int testEstates = 0;
    int GEstates = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == estate){
            testEstates++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == estate){
            GEstates++;
        }
    }
    printf("Result %d estates. Expected %d.\n", testEstates, GEstates-1);
    assert(testEstates, GEstates-1);
    //Assert number of cards in hand reduced by 2
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], G.handCount[0] - 2);
    assert(test.handCount[0], G.handCount[0] - 2);
    //Assert number of cards in discard increased by 2
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + 2);
    assert(test.discardCount[0], G.discardCount[0] + 2);

    //Test2 - Discard estate card at last hand position
    printf("\n<<< Test 2 - Discard estate card without estate in hand>>>\n");
    memcpy(&test, &initial, sizeof(struct gameState));
    test.hand[0][0] = baron;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == estate){
            test.hand[0][i] = copper;
        }
    }
    memcpy(&G, &test, sizeof(struct gameState));
    baronEffect(1, &test, 0, 0);
    //Assert number of buys increased by 1
    printf("Result %d Buys. Expected %d.\n", test.numBuys, G.numBuys+1);
    assert(test.numBuys, G.numBuys+1);
    //Assert number of gold increased by 4
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 4);
    assert(test.coins, G.coins + 4);
    //Assert number of estate cards in hand reduced by 1
    testEstates = 0;
    GEstates = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == estate){
            testEstates++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == estate){
            GEstates++;
        }
    }
    printf("Result %d estates. Expected %d.\n", testEstates, GEstates - 1);
    assert(testEstates, GEstates - 1);
    //Assert number of cards in hand reduced by 2
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], G.handCount[0] - 2);
    assert(test.handCount[0], G.handCount[0] - 2);
    //Assert number of cards in discard increased by 2
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + 2);
    assert(test.discardCount[0], G.discardCount[0] + 2);

    //Test3 - gain an estate
    printf("\n<<< Test 3 - gain an estate>>>\n");
    memcpy(&test, &initial, sizeof(struct gameState));
    test.hand[0][0] = baron;
    memcpy(&G, &test, sizeof(struct gameState));
    baronEffect(0, &test, 0, 0);
    //Assert number of buys increased by 1
    printf("Result %d Buys. Expected %d.\n", test.numBuys, G.numBuys+1);
    assert(test.numBuys, G.numBuys+1);
    //Assert number of gold is unchanged
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins);
    assert(test.coins, G.coins);
    //Assert number of estate cards in discard increased by 1
    testEstates = 0;
    GEstates = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.discard[0][i] == estate){
            testEstates++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.discard[0][i] == estate){
            GEstates++;
        }
    }
    printf("Result %d estates. Expected %d.\n", testEstates, GEstates+1);
    assert(testEstates, GEstates+1);
    //Assert number of cards in hand reduced by 1
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in discard increased by 2
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + 2);
    assert(test.discardCount[0], G.discardCount[0] + 2);
    //Assert Estate supply reduced by 1
    printf("Result %d estates in supply. Expected %d.\n", test.supplyCount[estate], G.supplyCount[estate]+1);
    assert(test.supplyCount[estate], G.supplyCount[estate]+1);

    return 0;
}
