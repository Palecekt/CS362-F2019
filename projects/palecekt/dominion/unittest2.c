//This is the unit test for the minion cardEffect function

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
    printf("***************Beginning Tests for Minion***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;
    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test1 - Gain coins
    printf("\n<<< Test 1 - Choose to gain 2 coins >>>\n");
    test.hand[0][0] = minion;
    memcpy(&G, &test, sizeof(struct gameState));
    minionEffect(1, 0, &test, 0, 0);
    //Assert number of actions increased by 1
    printf("Result %d Actions. Expected %d.\n", test.numActions, G.numActions+1);
    assert(test.numActions, G.numActions+1);
    //Assert number of gold increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins+2);
    assert(test.coins, G.coins+2);
    //Assert number of minion cards in hand reduced by 1
    int testMinions = 0;
    int GMinions = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == minion){
            testMinions++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == minion){
            GMinions++;
        }
    }
    printf("Result %d minions. Expected %d.\n", testMinions, GMinions-1);
    assert(testMinions, GMinions-1);
    //Assert number of cards in hand reduced by 1
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in discard increased by 1
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + 1);
    assert(test.discardCount[0], G.discardCount[0] + 1);

    //Test2 - Discard hand
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 2 - Choose to discard hand >>>\n");
    test.hand[0][0] = minion;
    test.handCount[0] = 5;
    for(int i = 0; i < test.handCount[0]; i++){
        test.hand[0][i] = copper;
    }
    test.handCount[1] = 5;
    for(int i = 0; i < test.handCount[1]; i++){
        test.hand[1][i] = copper;
    }
    test.deckCount[0] = 10;
    for(int i = 0; i < test.deckCount[0]; i++){
        test.deck[0][i] = silver;
    }
    test.deckCount[1] = 10;
    for(int i = 0; i < test.deckCount[1]; i++){
        test.deck[1][i] = silver;
    }
    memcpy(&G, &test, sizeof(struct gameState));
    minionEffect(0, 1, &test, 0, 0);
    //Assert number of actions increased by 1
    printf("Result %d Actions. Expected %d.\n", test.numActions, G.numActions+1);
    assert(test.numActions, G.numActions+1);
    //Assert number of gold is unchanged
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins);
    assert(test.coins, G.coins);
    //Assert number of cards in hand is 4
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], 4);
    assert(test.handCount[0], 4);
    //Assert number of cards in discard increased by number of cards in hand
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + G.handCount[0]);
    assert(test.discardCount[0], G.discardCount[0] + G.handCount[0]);
    //Assert number of cards in OPPONENT hand is 4
    printf("Result %d opponent hand cards. Expected %d.\n", test.handCount[1], 4);
    assert(test.handCount[1], 4);
    //Assert number of cards in OPPONENT discard increased by number of cards in OPPONENT hand
    printf("Result %d opponent discard cards. Expected %d.\n", test.discardCount[1], G.discardCount[1] + G.handCount[1]);
    assert(test.discardCount[1], G.discardCount[1] + G.handCount[1]);

    //Test3 - Discard hand - Opponent has 4 cards
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 3 - Choose to discard hand - Opponent has 4 cards >>>\n");
    test.hand[0][0] = minion;
    test.deckCount[0] = 10;
    for(int i = 0; i < test.deckCount[0]; i++){
        test.deck[0][i] = silver;
    }
    test.deckCount[1] = 10;
    for(int i = 0; i < test.deckCount[1]; i++){
        test.deck[1][i] = silver;
    }
    test.handCount[1] = 4;
    for(int i = 0; i < test.handCount[1]; i++){
        test.hand[1][i] = feast;
    }
    memcpy(&G, &test, sizeof(struct gameState));
    minionEffect(0, 1, &test, 0, 0);
    //Assert number of actions increased by 1
    printf("Result %d Actions. Expected %d.\n", test.numActions, G.numActions+1);
    assert(test.numActions, G.numActions+1);
    //Assert number of gold is unchanged
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins);
    assert(test.coins, G.coins);
    //Assert number of cards in hand is 4
    printf("Result %d hand cards. Expected %d.\n", test.handCount[0], 4);
    assert(test.handCount[0], 4);
    //Assert number of cards in deck is reduced by 4
    printf("Result %d deck cards. Expected %d.\n", test.deckCount[0], G.deckCount[0]-4);
    assert(test.handCount[0], G.deckCount[0] - 4);
    //Assert number of cards in discard increased by number of cards in hand
    printf("Result %d discard cards. Expected %d.\n", test.discardCount[0], G.discardCount[0] + G.handCount[0]);
    assert(test.discardCount[0], G.discardCount[0] + G.handCount[0]);
    //Assert number of cards in OPPONENT hand is 4
    printf("Result %d opponent hand cards. Expected %d.\n", test.handCount[1], 3);
    assert(test.handCount[1], 3);
    //Assert opponent hand contains all copper
    int oppFeasts = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == feast){
            oppFeasts++;
        }
    }
    printf("Result %d opponent feasts. Expected %d.\n", oppFeasts, 4);
    assert(oppFeasts, 4);
    //Assert number of cards in OPPONENT discard is unchanged
    printf("Result %d opponent discard cards. Expected %d.\n", test.discardCount[1], G.discardCount[1]);
    assert(test.discardCount[1], G.discardCount[1]);
    return 0;
}
