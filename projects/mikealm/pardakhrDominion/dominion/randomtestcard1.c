#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


void myAssert(char* msg, int x) {
    printf("Case: %s\n", msg);
    if (x != 1) {
        printf("---> Error: Condition Failed!\n");
    } else {
        printf("---> Success: Condition Passed!\n");
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int seed = time(NULL);

    // Initialize game state, player and cards
    int testNum = 0;
    int handCount;
    int haveEstate;
    int choice;
    int estateCount;

    struct gameState G1;
    struct gameState G2;

    // Kingdom card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    printf("Random Test 1: Baron \n\n");

    while (testNum < 200){
        handCount = 1 + rand() % 10;
        choice = rand() % 2;
        estateCount = rand() % 2;
        haveEstate = 0;

        memset(&G1, 23, sizeof(struct gameState));
        memset(&G2, 23, sizeof(struct gameState));

        int r = initializeGame(2, k, seed, &G1);

        // Initialize hand
        G1.handCount[0] = handCount;
        G1.hand[0][0] = baron;

        // Fill hand with random card
        for (int i = 1; i < G1.handCount[0]; i++){
            G1.hand[0][i] = 1 + rand() % 16;
            if (G1.hand[0][i] == estate) {
                haveEstate = 1;
            }
        }

        // Random estate supply of 1 or 0
        G1.supplyCount[estate] = estateCount;

        memcpy(&G2, &G1, sizeof(struct gameState));

        baronEffect(&G1, choice, 0);

        testNum++;
        printf("Test Number: %d \nHand Count = %d \nEstate Supply Count = %d \nPlayer has estate: %d \nChoice Number: %d\n", testNum, handCount, estateCount, haveEstate, choice);

        myAssert("Number of buys increased", G1.numBuys == G2.numBuys + 1);

        // If player has estate card and chooses not to discard
        if (choice == 0 && estateCount == 1){
            myAssert("Estate in discard pile", G1.discard[0][0] == estate);
            myAssert("Estate decremented from supply", G1.supplyCount[estate] == G2.supplyCount[estate] - 1);
        }

        //  If player has estate and chooses not to discard
        if (choice == 1 && haveEstate == 1){
            myAssert("Number of coins increased by 4", G1.coins == G2.coins + 4);
            myAssert("Estate in discard pile", G1.discard[0][0] == estate);
            myAssert("Discard pile count increased", G1.discardCount == G2.discardCount + 1);
            myAssert("Estate no longer in hand", G1.hand[0][handCount] == -1);
            myAssert("Hand count decremented by 1", G1.handCount[0] == G2.handCount[0] - 1);
        }

        // If player has no estate and chooses to discard
        if (choice == 1 && haveEstate == 0 && estateCount > 0){
            myAssert("Estate in discard pile", G1.discard[0][0] == estate);
            myAssert("Estate decremented from supply", G1.supplyCount[estate] == G2.supplyCount[estate] - 1);
        }

        printf("\n\n");
    }
    return 0;
}