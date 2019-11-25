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
    int i;
    int testNum = 0;
    int treasures, victory, actions;
    int cards[2] = { -1, -1 };

    struct gameState G1;
    struct gameState G2;

    // Kingdom card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    printf("Random Test 3: Tribute\n");

    while (testNum < 200)
    {
        // Initialize variables
        treasures = victory = actions = 0;
        cards[0] = -1;
        cards[1] = -1;

        memset(&G1, 23, sizeof(struct gameState));
        memset(&G2, 23, sizeof(struct gameState));

        int r = initializeGame(2, k, seed, &G1);

        // Initialize hand variables of player 0
        G1.handCount[0] = 1 + rand() % 10;
        G1.hand[0][0] = tribute;

        //Initialize deck of player 1
        G1.deckCount[1] = rand() % 11;

        // Fill hand with random cards
        for (int i = 0; i < G1.deckCount[1]; i++){
            G1.deck[1][i] = 1 + rand() % 16;
        }

        G1.discardCount[1] = rand() % 11;

        // Fill discard pile with random cards
        for (int j = 0; j < G1.discardCount[1]; j++){
            G1.discard[1][j] = 1 + rand() % 16;
        }

        memcpy(&G2, &G1, sizeof(struct gameState));

        tributeEffect(0, 1, &G1);

        testNum++;
        printf("Test Number: %d\n", testNum);

        if (G2.deckCount[1] == 0 && G2.discardCount[1] == 1){
            myAssert("Discard pile is decremented", G1.discardCount[1] == G2.discardCount[1] - 1);
            cards[0] = G2.discard[1][0];
        } else if (G2.deckCount[1] == 0 && G2.discardCount[1] == 2){
            myAssert("Deck is empty", G1.deckCount[1] == 0);
            myAssert("2 cards in the discard pile", G1.discardCount[1] == 2);
            cards[0] = G2.discard[1][0];
            cards[1] = G2.discard[1][1];
        } else if (G2.deckCount[1] == 1 && G2.discardCount[1] == 0) {
            myAssert("Deck count is decremented", G1.deckCount[1] == G2.deckCount[1] - 1);
            cards[0] = G2.deck[1][0];
        } else if (G2.deckCount[1] > 1){
            myAssert("Deck is decremented by 2", G1.deckCount[1] == G2.deckCount[1] - 2);
            myAssert("Discard count incremented by 2", G1.discardCount[1] == G2.discardCount[1] + 2);
            cards[0] = G2.deck[1][0];
            cards[1] = G2.deck[1][1];
        }

        // track player 0 gains
        for (i = 0; i < 2; i++){
            if (cards[i] == copper || cards[i] == silver || cards[i] == gold){
                treasures += 2;
            }
            else if (cards[i] == estate || cards[i] == duchy || cards[i] == province || cards[i] == gardens || cards[i] == great_hall){
                victory += 2;
            }
            else{
                actions += 2;
            }
        }

        myAssert("Coins added", G1.coins == G2.coins + treasures);
        myAssert("Victory cards added", G1.handCount[0] == G2.handCount[0] + victory);
        myAssert("Action cards added", G1.numActions == G2.numActions + actions);

        printf("\n\n");
    }
    return 0;
}