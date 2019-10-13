#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);

//Refactored card effects
int baronEffect(int choice1, struct gameState *state, int currentPlayer, int handPos);
int minionEffect(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
int ambassadorEffect(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);
int tributeEffect(struct gameState *state, int currentPlayer, int nextPlayer, int tributeRevealedCards[], int handPos);
int mineEffect(int choice1, int choice2, struct gameState *state, int currentPlayer, int handPos);

//Helper functions for the refactored cardeffects
int discardHand(struct gameState *state, int player);
int drawX(struct gameState *state, int numDraws, int player);

#endif
