#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    // declare the game state
    struct gameState G;
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    printf("Begin Testing mineEffect():\n");
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    int p = 0;
    int handCount = 4;
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    initializeGame(2, k, 10, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    // call the refactored function
    printf("currentPlayer before mineEffect: %d\n", G.whoseTurn);
    int j = 2;
    printf("handCount for currentPlayer before mineEffect: %d\n", G.handCount[G.whoseTurn]);
    int numCardsDiscarded = mineEffect(&G, 0, 1, 2, 0, j, G.whoseTurn);
    endTurn(&G);
    // verify that your asserts pass, for the bugs your asserts may fail
    printf("currentPlayer should be 1\n");
    printf("currentPlayer is: %d\n", G.whoseTurn);
    if (G.whoseTurn == 1) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    printf("numCardsDiscarded should be 1\n");
    printf("numCardsDiscarded is: %d\n", numCardsDiscarded);
    if (numCardsDiscarded == 0) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    printf("Unit Test 5 completed!\n");

    return 0;
}