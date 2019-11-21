//This is the unit test for the ambassador cardEffect function

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
    printf("***************Beginning Tests for Ambassador***************\n");
    int seed = 10;
    int numPlayers = 2;
    //set your card array
    int k[10] = { ambassador, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    // declare the game states
    struct gameState initial;
    struct gameState G;
    struct gameState test;
    initializeGame(numPlayers, k, seed, &initial);
    memcpy(&test, &initial, sizeof(struct gameState));

    //Test1 - Return 2 cards
    printf("\n<<< Test 1 - Return 2 cards from hand >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = baron;
    test.hand[0][2] = baron;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, minion, 2, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand reduced by 1
    int testAmbassadors = 0;
    int GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors-1);
    assert(testAmbassadors, GAmbassadors-1);
    //Assert number of baron cards in hand reduced by 2
    int testBarons = 0;
    int GBarons = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == baron){
            testBarons++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == baron){
            GBarons++;
        }
    }
    printf("Result %d barons in hand. Expected %d.\n", testBarons, GBarons-2);
    assert(testBarons, GBarons-2);
    //Assert number of barons in opponent discard increased by 1
    int testBaronsOpp = 0;
    int GBaronsOpp = 0;
    for(int i = 0; i < test.discardCount[1]; i++){
        if (test.discard[1][i] == baron){
            testBaronsOpp++;
        }
    }
    for(int i = 0; i < G.discardCount[1]; i++){
        if (G.discard[1][i] == baron){
            GBaronsOpp++;
        }
    }
    printf("Result %d opp discard barons. Expected %d.\n", testBaronsOpp, GBaronsOpp+1);
    assert(testBaronsOpp, GBaronsOpp+1);
    //Assert number of barons in supply reduced by 1
    printf("Result %d barons in supply. Expected %d.\n", test.supplyCount[baron], G.supplyCount[baron] - 1);
    assert(test.supplyCount[baron], G.supplyCount[baron] - 1); 

    //Test2 - Return 1 card
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 2 - Return 1 card from hand >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = baron;
    test.hand[0][2] = baron;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 2, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand reduced by 1
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors-1);
    assert(testAmbassadors, GAmbassadors-1);
    //Assert number of baron cards in hand reduced by 2
    testBarons = 0;
    GBarons = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == baron){
            testBarons++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == baron){
            GBarons++;
        }
    }
    printf("Result %d barons in hand. Expected %d.\n", testBarons, GBarons-1);
    assert(testBarons, GBarons-1);
    //Assert number of barons in opponent discard increased by 1
    testBaronsOpp = 0;
    GBaronsOpp = 0;
    for(int i = 0; i < test.discardCount[1]; i++){
        if (test.discard[1][i] == baron){
            testBaronsOpp++;
        }
    }
    for(int i = 0; i < G.discardCount[1]; i++){
        if (G.discard[1][i] == baron){
            GBaronsOpp++;
        }
    }
    printf("Result %d opp discard barons. Expected %d.\n", testBaronsOpp, GBaronsOpp+1);
    assert(testBaronsOpp, GBaronsOpp+1);
    //Assert number of barons in supply unchanged
    printf("Result %d barons in supply. Expected %d.\n", test.supplyCount[baron], G.supplyCount[baron]);
    assert(test.supplyCount[baron], G.supplyCount[baron]); 


    //Test3 - Return more cards than in hand
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 3 - Return more cards than in hand >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = baron;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 2, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand reduced by 1
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors-1);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of baron cards in hand reduced by 2
    testBarons = 0;
    GBarons = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == baron){
            testBarons++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == baron){
            GBarons++;
        }
    }
    printf("Result %d barons in hand. Expected %d.\n", testBarons, GBarons);
    assert(testBarons, GBarons);
    //Assert number of barons in opponent discard increased by 1
    testBaronsOpp = 0;
    GBaronsOpp = 0;
    for(int i = 0; i < test.discardCount[1]; i++){
        if (test.discard[1][i] == baron){
            testBaronsOpp++;
        }
    }
    for(int i = 0; i < G.discardCount[1]; i++){
        if (G.discard[1][i] == baron){
            GBaronsOpp++;
        }
    }
    printf("Result %d opp discard barons. Expected %d.\n", testBaronsOpp, GBaronsOpp);
    assert(testBaronsOpp, GBaronsOpp);
    //Assert number of barons in supply unchanged
    printf("Result %d barons in supply. Expected %d.\n", test.supplyCount[baron], G.supplyCount[baron]);
    assert(test.supplyCount[baron], G.supplyCount[baron]); 

    //Test4 - Return more ambassador cards than in hand
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 4 - Return more ambassador cards than in hand >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = ambassador;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 2, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand is unchanged
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors-1);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of ambassadors in supply unchanged
    printf("Result %d ambassadors in supply. Expected %d.\n", test.supplyCount[ambassador], G.supplyCount[ambassador]);
    assert(test.supplyCount[ambassador], G.supplyCount[ambassador]); 

    //Test5 - Return more cards than in hand
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 4 - Return more cards than in hand >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = baron;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 2, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand reduced by 1
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors-1);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of baron cards in hand reduced by 2
    testBarons = 0;
    GBarons = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == baron){
            testBarons++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == baron){
            GBarons++;
        }
    }
    printf("Result %d barons in hand. Expected %d.\n", testBarons, GBarons);
    assert(testBarons, GBarons);
    //Assert number of barons in opponent discard increased by 1
    testBaronsOpp = 0;
    GBaronsOpp = 0;
    for(int i = 0; i < test.discardCount[1]; i++){
        if (test.discard[1][i] == baron){
            testBaronsOpp++;
        }
    }
    for(int i = 0; i < G.discardCount[1]; i++){
        if (G.discard[1][i] == baron){
            GBaronsOpp++;
        }
    }
    printf("Result %d opp discard barons. Expected %d.\n", testBaronsOpp, GBaronsOpp);
    assert(testBaronsOpp, GBaronsOpp);
    //Assert number of barons in supply unchanged
    printf("Result %d barons in supply. Expected %d.\n", test.supplyCount[baron], G.supplyCount[baron]);
    assert(test.supplyCount[baron], G.supplyCount[baron]); 

    //Test4 - Return no cards
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 6 - Return no cards >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = ambassador;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 0, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand is unchanged
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of ambassadors in supply decreased by 1
    printf("Result %d ambassadors in supply. Expected %d.\n", test.supplyCount[ambassador], G.supplyCount[ambassador] - 1);
    assert(test.supplyCount[ambassador], G.supplyCount[ambassador] - 1); 
    
    //Test5 - Return played card
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 6 - Return played card >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = ambassador;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 0, 1, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand is unchanged
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of ambassadors in supply unchanged
    printf("Result %d ambassadors in supply. Expected %d.\n", test.supplyCount[ambassador], G.supplyCount[ambassador]);
    assert(test.supplyCount[ambassador], G.supplyCount[ambassador]);
    
    //Test6 - Return more than 2 cards
    memcpy(&test, &initial, sizeof(struct gameState));
    printf("\n<<< Test 6 - Return played card >>>\n");
    test.hand[0][0] = ambassador;
    test.hand[0][1] = ambassador;
    memcpy(&G, &test, sizeof(struct gameState));
    ambassadorCardEffect(ambassador, 1, 3, -1, &test, 0, 0, 0);
    //Assert number of ambassador cards in hand is unchanged
    testAmbassadors = 0;
    GAmbassadors = 0;
    for(int i = 0; i < test.handCount[0]; i++){
        if (test.hand[0][i] == ambassador){
            testAmbassadors++;
        }
    }
    for(int i = 0; i < G.handCount[0]; i++){
        if (G.hand[0][i] == ambassador){
            GAmbassadors++;
        }
    }
    printf("Result %d ambassadors in hand. Expected %d.\n", testAmbassadors, GAmbassadors);
    assert(testAmbassadors, GAmbassadors);
    //Assert number of ambassadors in supply unchanged
    printf("Result %d ambassadors in supply. Expected %d.\n", test.supplyCount[ambassador], G.supplyCount[ambassador]);
    assert(test.supplyCount[ambassador], G.supplyCount[ambassador]);


    return 0;
}
