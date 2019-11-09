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
    printf("***************Beginning Tests for Mine***************\n");
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

    //Test1 - Valid choices
    printf("\n<<< Test 1 - Trash and gain cards are valid >>>\n");
    test.handCount[0] = 2;
    test.hand[0][0] = mine;
    test.hand[0][1] = copper;
    int choice1 = 1;
    int choice2 = silver;
    memcpy(&G, &test, sizeof(struct gameState));
    mineEffect(choice1, choice2, &test, 0, 0);
    //Assert number of mine cards in hand reduced by 1
    int testMines = 0;
    int GMines = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == mine){
            testMines++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == mine){
            GMines++;
        }
    }
    printf("Result %d mines in hand. Expected %d.\n", testMines, GMines-1);
    assert(testMines, GMines-1);
    //Assert number silvers in discard increased by 1
    int testSilvers = 0;
    int GSilvers = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == silver){
            testSilvers++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == silver){
            GSilvers++;
        }
    }
    printf("Result %d silvers. Expected %d.\n", testSilvers, GSilvers +1);
    assert(testSilvers, GSilvers + 1); 
    //Assert 1 silver is removed from supply
    printf("Result %d silvers in supply. Expected %d.\n", test.supplyCount[silver], G.supplyCount[silver]-1);
    assert(test.supplyCount[silver], G.supplyCount[silver]-1); 

    //Test2 - Choice too expensive
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 2 - Player chooses to gain a card that is too expensive >>>\n");
    test.handCount[0] = 2;
    test.hand[0][0] = mine;
    test.hand[0][1] = copper;
    choice1 = 1;
    choice2 = gold;
    memcpy(&G, &test, sizeof(struct gameState));
    mineEffect(choice1, choice2, &test, 0, 0);
    //Assert number of mine cards in hand is unchanged
    testMines = 0;
    GMines = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == mine){
            testMines++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == mine){
            GMines++;
        }
    }
    printf("Result %d mines in hand. Expected %d.\n", testMines, GMines);
    assert(testMines, GMines);
    //Assert number golds in hand is unchanged
    testSilvers = 0;
    GSilvers = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == silver){
            testSilvers++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == silver){
            GSilvers++;
        }
    }
    printf("Result %d golds. Expected %d.\n", testSilvers, GSilvers);
    assert(testSilvers, GSilvers); 
    //Assert gold supply is unchanged
    printf("Result %d gold in supply. Expected %d.\n", test.supplyCount[gold], G.supplyCount[gold]);
    assert(test.supplyCount[gold], G.supplyCount[gold]); 
    
    //Test3 - Invalid trash - Valid gain
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 2 - Player chooses to gain a card that is too expensive >>>\n");
    test.handCount[0] = 2;
    test.hand[0][0] = mine;
    test.hand[0][1] = village;
    choice1 = 1;
    choice2 = gold;
    memcpy(&G, &test, sizeof(struct gameState));
    mineEffect(choice1, choice2, &test, 0, 0);
    //Assert number of mine cards in hand is unchanged
    testMines = 0;
    GMines = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == mine){
            testMines++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == mine){
            GMines++;
        }
    }
    printf("Result %d mines in hand. Expected %d.\n", testMines, GMines);
    assert(testMines, GMines);
    //Assert number of village cards in hand is unchanged
    testMines = 0;
    GMines = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == village){
            testMines++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == village){
            GMines++;
        }
    }
    printf("Result %d villages in hand. Expected %d.\n", testMines, GMines);
    assert(testMines, GMines);
    //Assert number golds in hand is unchanged
    testSilvers = 0;
    GSilvers = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == silver){
            testSilvers++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == silver){
            GSilvers++;
        }
    }
    printf("Result %d golds. Expected %d.\n", testSilvers, GSilvers);
    assert(testSilvers, GSilvers); 
    //Assert gold supply is unchanged
    printf("Result %d gold in supply. Expected %d.\n", test.supplyCount[gold], G.supplyCount[gold]);
    assert(test.supplyCount[gold], G.supplyCount[gold]); 
 
    return 0;
}
