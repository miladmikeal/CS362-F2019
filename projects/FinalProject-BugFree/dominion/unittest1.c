#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

void myAssert(char *msg, int x)
{
  printf("Case: %s\n", msg);
  if (x != 1)
  {
    printf("---> Error: Condition Failed!\n");
  }
  else
  {
    printf("---> Success: Condition Passed!\n");
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  int seed = time(NULL);
  int numPlayers = 2;
  int player = 0;

  struct gameState G1, G2;

  // Kingdom card array
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

  printf("\n***** Unit Test - Bug 1: *****\n");

  // Setup: initialize game state, player and cards
  memset(&G1, 23, sizeof(struct gameState));
  memset(&G2, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &G1);

  int deckCountBefore = G1.deckCount[player];
  int handCountBefore = G1.handCount[player];
  int discardCountBefore = G1.discardCount[player];
  int bonus;

  cardEffect(mine, 1, copper, 0, &G1, 1, &bonus);

  myAssert("Deck count the same", (deckCountBefore == G1.deckCount[player]));
  myAssert("Hand count has one less", (handCountBefore != G1.handCount[player]));

  printf("\n\n");

  return 0;
}