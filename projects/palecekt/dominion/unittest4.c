//This is the unit test for the tribute cardEffect function

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
    printf("***************Beginning Tests for Tribute***************\n");
    int seed = 10;
    int numPlayers = 2;
    int tributeRevealedCards[2] = {-1, -1};
    //set your card array
    int k[10] = { ambassador, tribute, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;

    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test1 - Reveal an action and a treasure card
    printf("\n<<< Test 1 - Opponent reveals an action and a treasure>>>\n");
    test.hand[0][0] = tribute;
    test.deckCount[1] = 2;
    test.deck[1][0] = tribute;
    test.deck[1][1] = copper;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    int testTributes = 0;
    int GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions increased by 2
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions + 2);
    assert(test.numActions, G.numActions + 2); 
    //Assert number of coins increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 2);
    assert(test.coins, G.coins + 2);
    //Assert number of cards in hand decreased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] -1);
    //Assert number of cards in opponent deck decreased by 2
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1] - 2);
    assert(test.deckCount[1], G.deckCount[1] - 2);

    //Test2 - Reveal an action and a victory card
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 2 - Opponent reveals an action and a victory>>>\n");
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    test.hand[0][0] = tribute;
    test.deckCount[1] = 2;
    test.deck[1][0] = tribute;
    test.deck[1][1] = estate;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    testTributes = 0;
    GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions increased by 2
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions + 2);
    assert(test.numActions, G.numActions + 2); 
    //Assert number of coins increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 2);
    assert(test.coins, G.coins + 2);
    //Assert number of cards in hand increased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] + 1);
    assert(test.handCount[0], G.handCount[0] + 1);
    //Assert number of cards in opponent deck decreased by 2
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1] - 2);
    assert(test.deckCount[1], G.deckCount[1] - 2);

    //Test3 - Reveal an victory card from deck. no other cards
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 3 - Opponent has 1 card in deck none in discard >>>\n");
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    test.hand[0][0] = tribute;
    test.deckCount[1] = 1;
    test.deck[1][0] = copper;
    test.discardCount[1] = 0;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    testTributes = 0;
    GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d tributes in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions unchanged
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions);
    assert(test.numActions, G.numActions); 
    //Assert number of coins increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 2);
    assert(test.coins, G.coins + 2);
    //Assert number of cards in hand decreased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in opponent deck decreased by 1
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1] - 1);
    assert(test.deckCount[1], G.deckCount[1] - 1);

    //Test4 - Opponent has no cards in deck or discard
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 4 - Opponent has no cards in deck or discard>>>\n");
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    test.hand[0][0] = tribute;
    test.deckCount[1] = 0;
    test.discardCount[1] = 0;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    testTributes = 0;
    GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d tributes in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions unchanged
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions);
    assert(test.numActions, G.numActions); 
    //Assert number of coins to be unchanged
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins);
    assert(test.coins, G.coins);
    //Assert number of cards in hand decreased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in opponent deck to be unchanged
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1]);
    assert(test.deckCount[1], G.deckCount[1]);

    //Test5 - Opponent has no cards in deck 1 in discard
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 5 - Opponent has no cards in deck 1 in discard>>>\n");
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    test.hand[0][0] = tribute;
    test.deckCount[1] = 0;
    test.discardCount[1] = 1;
    test.discard[1][0] = copper;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    testTributes = 0;
    GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d tributes in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions unchanged
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions);
    assert(test.numActions, G.numActions); 
    //Assert number of coins increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 2);
    assert(test.coins, G.coins + 2);
    //Assert number of cards in hand decreased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in opponent deck to be unchanged
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1]);
    assert(test.deckCount[1], G.deckCount[1]);

    //Test6 - Opponent has no cards in deck 2 in discard
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 6 - Opponent has no cards in deck 2 in discard>>>\n");
    tributeRevealedCards[0] = -1;
    tributeRevealedCards[1] = -1;
    test.hand[0][0] = tribute;
    test.deckCount[1] = 0;
    test.discardCount[1] = 2;
    test.discard[1][0] = copper;
    test.discard[1][0] = tribute;
    memcpy(&G, &test, sizeof(struct gameState));
    tributeEffect(&test, 0, 1, tributeRevealedCards, 0);
    //Assert number of tribute cards in hand reduced by 1
    testTributes = 0;
    GTributes = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == tribute){
            testTributes++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == tribute){
            GTributes++;
        }
    }
    printf("Result %d tributes in hand. Expected %d.\n", testTributes, GTributes-1);
    assert(testTributes, GTributes-1);
    //Assert number of actions increased by 2
    printf("Result %d actions. Expected %d.\n", test.numActions, G.numActions + 2);
    assert(test.numActions, G.numActions + 2); 
    //Assert number of coins increased by 2
    printf("Result %d coins. Expected %d.\n", test.coins, G.coins + 2);
    assert(test.coins, G.coins + 2);
    //Assert number of cards in hand decreased by 1
    printf("Result %d cards in hand. Expected %d.\n", test.handCount[0], G.handCount[0] - 1);
    assert(test.handCount[0], G.handCount[0] - 1);
    //Assert number of cards in opponent deck to be unchanged
    printf("Result %d cards in opponent deck. Expected %d.\n", test.deckCount[1], G.deckCount[1]);
    assert(test.deckCount[1], G.deckCount[1]);
    //Assert discard cards are valid cards
    int isValid = 1;
    for(int i = 0; i < test.discardCount[1]; i++){
        if(test.discard[1][i] == -1){
            isValid = 0;
            break;
        }
    }
    printf("Result opponent discard cards are valid?.\n");
    assert(isValid, 1);
    
    return 0;
}
