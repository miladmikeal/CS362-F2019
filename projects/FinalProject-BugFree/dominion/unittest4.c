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

  printf("\n***** Unit Test - Bug 4: *****\n");

  // Setup: initialize game state, player and cards
  memset(&G1, 23, sizeof(struct gameState));
  memset(&G2, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &G1);

  int bonus;
  
  int isGameOverBefore = isGameOver(&G1);

  G1.supplyCount[treasure_map] = 0;
  G1.supplyCount[sea_hag] = 0;
  G1.supplyCount[mine] = 0;

  int isGameOverAfter = isGameOver(&G1);

  myAssert("Game is over", (isGameOverBefore == 0 && isGameOverAfter == 1));

  printf("\n\n");
  
  return 0;
}