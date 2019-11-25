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
    int i, j;
    int testNum = 0;
    int choice1;
    int choice2;
    int playersNum;
    int cardTotal = 0;

    struct gameState G1;
    struct gameState G2;

    // Kingdom card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

    printf("Random Test 2: Minion\n");

    while (testNum < 200)
    {
        // Initialize total cards at 0
        cardTotal = 0;

        playersNum = 2 + rand() % 3;
        choice1 = rand() % 2;
        choice2 = rand() % 2;

        memset(&G1, 23, sizeof(struct gameState));
        memset(&G2, 23, sizeof(struct gameState));

        int r = initializeGame(playersNum, k, seed, &G1);

        // Initialize hands
        G1.handCount[0] = 1 + rand() % 10;
        G1.hand[0][0] = minion;

        // fill random hand counts with random cards
        for (j = 1; j < playersNum; j++){
            G1.handCount[j] = 1 + rand() % 10;
            for (i = 1; i < G1.handCount[j]; i++){
                G1.hand[j][i] = 1 + rand() % 16;
            }
        }

        memcpy(&G2, &G1, sizeof(struct gameState));

        minionEffect(choice1, choice2, 0, &G1, 0);

        testNum++;
        printf("Test Number: %d \nChoice Number 1 = %d \nChoice Number 2 = %d\n", testNum, choice1, choice2);

        myAssert("Number of action cards increased", G1.numActions == G2.numActions + 1);
        myAssert("Minion card played", G1.playedCards[0] == minion);
        cardTotal++;


        if (choice2 == 1){
            myAssert("Player has 4 cards", G1.handCount[0] == 4);
            cardTotal += G2.handCount[0];


            for (i = 1; i < playersNum; i++){
                // other players have +5 cards
                if (G2.handCount[i] >= 5){
                    myAssert("Other players discard hand and redraw 4 cards", G1.handCount[i] == 4);
                    cardTotal += G2.handCount[i];
                }
                else{
                    myAssert("Other players did not have 4 cards and no change", G1.handCount[i] == G2.handCount[i]);
                }
            }

            myAssert("Number of cards played", G1.playedCardCount == cardTotal);
        }

        // Player choose to gain 2 coins
        if (choice1 == 1 && choice2 == 0){
            myAssert("Number of coins increased by 2", G1.coins == G2.coins + 2);
            myAssert("Minion card no longer in hand", G1.hand[0][G2.handCount[0]] == -1);
            myAssert("Hand count decremented", G1.handCount[0] == G2.handCount[0] - 1);
            myAssert("Card is played", G1.playedCardCount == G2.playedCardCount + 1);
        }

        printf("\n\n");
    }

    return 0;
}