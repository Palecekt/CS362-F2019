//This is the random tester for the 5 refactored cardEffect functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <time.h>

int NUM_CARDS = 17;
int NUM_BARON_TESTS = 500;
int NUM_MINION_TESTS = 500;
int NUM_AMBASSADOR_TESTS = 500;
int NUM_TRIBUTE_TESTS = 500;
int NUM_MINE_TESTS = 500;


void randomizeGameState(struct gameState *g, int k[10]);
void baronAssert(struct gameState *base, struct gameState *test, int choice, int k[10], int testNum);
void minionAssert(struct gameState *base, struct gameState *test, int choice1, int choice2, int k[10], int testNum);
void ambassadorAssert(struct gameState *base, struct gameState *test, int choice1, int choice2, int k[10], int testNum);
void tributeAssert(struct gameState *base, struct gameState *test, int k[10], int testNum, int revealed[]);
void mineAssert(struct gameState *base, struct gameState *test, int choice1, int choice2, int k[10], int testNum);



int main(){
    int k[10] = { baron, mine, minion, ambassador, tribute, gardens,  remodel, 
                smithy, village,  great_hall };
    srand(time(NULL));
    struct gameState test;
    struct gameState base;
    printf("**********BEGINNING TESTING: BARON**********\n");
    for(int i = 0; i < NUM_BARON_TESTS; i++){
        randomizeGameState(&test, k);
        memcpy(&base, &test, sizeof(struct gameState));
        //Give the player a copy of the baron card to be played
        int handPos = rand() % test.handCount[0];
        test.hand[0][handPos] = baron;
        //Set player choice to discard or not
        int choice1 = rand() % 2;
        baronEffect(choice1, &test, 0, handPos);
        baronAssert(&base, &test, choice1, k, i);
    }
    printf("**********BEGINNING TESTING: MINION**********\n");
    for(int i = 0; i < NUM_MINION_TESTS; i++){
        randomizeGameState(&test, k);
        memcpy(&base, &test, sizeof(struct gameState));
        //Give the player a copy of the minion card to be played
        int handPos = rand() % test.handCount[0];
        test.hand[0][handPos] = baron;
        //Set player choice
        int choice1 = rand() % 2;
        int choice2 = 1 - choice1;
        minionEffect(choice1, choice2, &test, handPos, 0);
        minionAssert(&base, &test, choice1, choice2, k, i);
    }
    printf("**********BEGINNING TESTING: AMBASSADOR**********\n");
    for(int i = 0; i < NUM_AMBASSADOR_TESTS; i++){
        randomizeGameState(&test, k);
        memcpy(&base, &test, sizeof(struct gameState));
        //Give the player a copy of the minion card to be played
        int handPos = rand() % test.handCount[0];
        test.hand[0][handPos] = ambassador;
        //Set player choice
        int choice1 = rand() % test.handCount[0] - 1;
        choice1++;
        int choice2 = rand() % 4;
        ambassadorEffect(choice1, choice2, &test, handPos, 0);
        ambassadorAssert(&base, &test, choice1, choice2, k, i);
    }
    printf("**********BEGINNING TESTING: TRIBUTE**********\n");
    for(int i = 0; i < NUM_TRIBUTE_TESTS; i++){
        randomizeGameState(&test, k);
        memcpy(&base, &test, sizeof(struct gameState));
        int revealed[2] = {-1, -1};
        //Give the player a copy of the minion card to be played
        int handPos = rand() % test.handCount[0];
        test.hand[0][handPos] = tribute;
        tributeEffect(&test, 0, 1, revealed, handPos);
        tributeAssert(&base, &test, k, i, revealed);
    }
    printf("**********BEGINNING TESTING: MINE**********\n");
    for(int i = 0; i < NUM_MINE_TESTS; i++){
        randomizeGameState(&test, k);
        memcpy(&base, &test, sizeof(struct gameState));
        //Give the player a copy of the minion card to be played
        int handPos = rand() % test.handCount[0];
        test.hand[0][handPos] = ambassador;
        //Set player choice
        int choice1 = rand() % test.handCount[0] - 1;
        choice1++;
        int choice2 = rand() % 10;
        switch(choice2){
            case 7:
                choice2 = baron;
                break;
            case 8:
                choice2 = minion;
                break;
            case 9:
                choice2 = 28;
                break;
        }
        mineEffect(choice1, choice2, &test, 0, handPos);
        mineAssert(&base, &test, choice1, choice2, k, i);
    }
    return 0;
}

void randomizeGameState(struct gameState *g, int k[10]){
    int numPlayers = rand() % 3 + 2;
    initializeGame(numPlayers, k, 50, g);
    //Randomize deck/hand/discard counts of all players
    for(int i = 0; i < g->numPlayers; i++){
        g->deckCount[i] = rand() % 11;
        g->handCount[i] = rand() % 6 + 1;
        g->discardCount[i] = rand() % 6;
    }
    //Randomize decks of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->deckCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->deck[i][j] = card;
            }
            else{
                g->deck[i][j] = k[card - 7];
            }
        }
    }
    //Randomize randomize hands of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->handCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->hand[i][j] = card;
            }
            else{
                g->hand[i][j] = k[card - 7];
            }
        }
    }
    //Randomize discards of all players
    for(int i = 0; i < g->numPlayers; i++){
        for(int j = 0; j < g->discardCount[i]; j++){
            int card = rand() % NUM_CARDS;
            if(card < 7){
                g->discard[i][j] = card;
            }
            else{
                g->discard[i][j] = k[card - 7];
            }
        }
    }
    //Randomize all supply counts
    for(int i = 0; i < 27; i++){
        g->supplyCount[i] = rand() % 10;
    }
}

void baronAssert(struct gameState *base, struct gameState *test, 
int choice, int k[10], int testNum){
    if(test->numBuys != base->numBuys + 1){
        printf("Failed test %d. Incorrect number of buys.\n", testNum);
        return;
    }
    if(choice == 1){
        //See if hand contains an Estate card
        int testEstates = 0;
        int baseEstates = 0;
        for(int i = 0; i < base->handCount[0]; i++){
            if (base->hand[0][i] == estate){
                baseEstates++;
            }
        }
        for(int i = 0; i < test->handCount[0]; i++){
            if (test->hand[0][i] == estate){
                testEstates++;
            }
        }
        if(baseEstates > 0){
            if(testEstates != baseEstates - 1){
                printf("Failed test %d. Incorrect number of estates in hand.\n", testNum);
            }
            if(test->coins != base->coins + 4){
                printf("Failed test %d. Incorrect number of coins.\n", testNum);
            }
            if(test->handCount != base->handCount - 2){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
        }
        else{
            if(test->supplyCount[baron] != base->supplyCount[baron] - 1){
                printf("Failed test %d. Incorrect number of baron cards in supply.\n", testNum);
            }
            if(test->handCount != base->handCount - 1){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(test->coins != base->coins){
                printf("Failed test %d. Incorrect number of coins.\n", testNum);
            }
        }
    }
    else{
        if(test->supplyCount[baron] != base->supplyCount[baron] - 1){
            printf("Failed test %d. Incorrect number of baron cards in supply.\n", testNum);
        }
        if(test->handCount != base->handCount - 1){
            printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
        }
        if(test->coins != base->coins){
            printf("Failed test %d. Incorrect number of coins.\n", testNum);
        }

    }
}

void minionAssert(struct gameState *base, struct gameState *test, 
int choice1, int choice2, int k[10], int testNum){
    
    for(int i = 0; i < 27; i++){
        if(test->supplyCount[i] != base->supplyCount[i]){
            printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
        }
    }
    
    if(test->numActions != base->numActions + 1){
        printf("Failed test %d. Incorrect number of actions.\n", testNum);
    }
    if(choice1){
        if(test->coins != base->coins + 2){
            printf("Failed test %d. Incorrect number of coins.\n", testNum);
        }
        if(test->handCount[0] != base->handCount[0] - 1){
            printf("Failed test %d. Incorrect number of coins.\n", testNum);
        }
    }
    else if(choice2){
        if(test->handCount[0] != 4){
            printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
        }
        for(int j = 1; j < base->numPlayers; j++){
            if(base->handCount[j] > 4){
                if(test->handCount[j] != 4){
                    printf("Failed test %d. Incorrect number of cards in opponent's hand.\n", testNum);
                }
            }
            else{
                if(test->handCount[j] != base->handCount[j]){
                    printf("Failed test %d. Incorrect number of cards in opponent's hand.\n", testNum);
                }
            }
        }
    }

}
void ambassadorAssert(struct gameState *base, struct gameState *test, int choice1, 
int choice2, int k[10], int testNum){
        if(choice2 == 0){
            if(test->handCount[0] != base->handCount[0]){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(base->supplyCount[base->hand[0][choice1]] < base->numPlayers - 1){
                if(test->supplyCount[base->hand[0][choice1]] != 0){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
            else{
                if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]] - (base->numPlayers - 1)){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
        }
        if(choice2 == 1){
            if(test->handCount[0] != base->handCount[0] - 1){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(base->supplyCount[base->hand[0][choice1]] < base->numPlayers){
                if(test->supplyCount[base->hand[0][choice1]] != 0){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
            else{
                if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]] + 1 - (base->numPlayers - 1)){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
        }
        if(choice2 == 2){
            if(test->handCount[0] != base->handCount[0] - 2){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(base->supplyCount[base->hand[0][choice1]] < base->numPlayers + 1){
                if(test->supplyCount[base->hand[0][choice1]] != 0){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
            else{
                if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]] + 2 - (base->numPlayers - 1)){
                    printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
                }
            }
        }
        else{
            if(test->handCount[0] != base->handCount[0]){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]]){
                printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
            }
        }
}
void tributeAssert(struct gameState *base, struct gameState *test, int k[10], int testNum, int revealed[]){
    int actions = 0;
    int coins = 0;
    int cards = 0;
    if(revealed[0] == revealed[1]){
        revealed[1] = -1;
    }
    if(revealed[0] == copper || revealed[0] == silver || revealed[0] == gold){
        coins += 2;
    }
    else if (revealed[0] == estate || revealed[0] == duchy || revealed[0] == province || revealed[0] == gardens || revealed[0] == great_hall){
        cards += 2;
    }
    else if(revealed[0] != -1){
        actions += 2;
    }
    if(revealed[1] == copper || revealed[1] == silver || revealed[1] == gold){
        coins += 2;
    }
    else if (revealed[1] == estate || revealed[1] == duchy || revealed[1] == province || revealed[1] == gardens || revealed[1] == great_hall){
        cards += 2;
    }
    else if(revealed[1] != -1){
        actions += 2;
    }
    if(test->coins != base->coins + coins){
        printf("Failed test %d. Incorrect number of coins.\n", testNum);
    }
    if(test->numActions != base->numActions + actions){
        printf("Failed test %d. Incorrect number of actions.\n", testNum);
    }
    if(test->handCount[0] != base->handCount[0] + cards - 1){
        printf("Failed test %d. Incorrect number of cards.\n", testNum);
    }
}
void mineAssert(struct gameState *base, struct gameState *test, int choice1, 
int choice2, int k[10], int testNum){
    if(base->hand[0][choice1] == copper || base->hand[0][choice1] == silver || base->hand[0][choice1] == gold){
        if(getCost(base->hand[0][choice1]) < getCost(choice2)){
            if(test->handCount[0] != base->handCount[0] - 1){
                printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
            }
            if(test->discardCount[0] != base->discardCount[0] + 2){
                printf("Failed test %d. Incorrect number of cards in discard.\n", testNum);
            }
            if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]] - 1){
                printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
            }
        }
    }
    else{
        if(test->handCount[0] != base->handCount[0]){
            printf("Failed test %d. Incorrect number of cards in hand.\n", testNum);
        }
        if(test->discardCount[0] != base->discardCount[0]){
            printf("Failed test %d. Incorrect number of cards in discard.\n", testNum);
        }
        if(test->supplyCount[base->hand[0][choice1]] != base->supplyCount[base->hand[0][choice1]]){
            printf("Failed test %d. Incorrect number of cards in supply.\n", testNum);
        }
    }
}
