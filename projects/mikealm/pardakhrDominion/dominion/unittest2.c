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
    printf("Begin Testing minionEffect():\n");
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
    printf("currentPlayer before minionEffect: %d\n", G.whoseTurn);
    printf("handCount for currentPlayer before minionEffect: %d\n", G.handCount[G.whoseTurn]);
    int drawnCards = minionEffect(1, 0, 0, &G, 0);
    endTurn(&G);
    // verify that your asserts pass, for the bugs your asserts may fail
    printf("currentPlayer should be 1\n");
    printf("currentPlayer is: %d\n", G.whoseTurn);
    if (G.whoseTurn == 1) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    printf("drawnCards should be 4\n");
    printf("drawnCards is: %d\n", drawnCards);
    if (drawnCards == 4) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    printf("handCount for currentPlayer should be 4\n");
    printf("handCount for currentPlayer is: %d\n", G.handCount[G.whoseTurn]);
    if (G.handCount[G.whoseTurn] == 4) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    printf("Unit Test 2 completed!\n");

    return 0;
}