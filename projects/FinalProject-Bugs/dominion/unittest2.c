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

  printf("\n***** Unit Test - Bug 2: *****\n");

  // Setup: initialize game state, player and cards
  memset(&G1, 23, sizeof(struct gameState));
  memset(&G2, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &G1);

  int bonus;
  int copperCountBefore = G1.supplyCount[copper];
  int goldCountBefore = G1.supplyCount[gold];
  G1.handCount[player] = 2;
  G1.hand[player][0] = mine;
  G1.hand[player][1] = copper;

  myAssert("Costs are correct", (getCost(copper) == 0 && getCost(silver) == 3 && getCost(gold) == 6));

  cardEffect(mine, 1, gold, 0, &G1, 0, &bonus);

  myAssert("Cannot trade copper for gold", (copperCountBefore == G1.supplyCount[copper] && goldCountBefore == G1.supplyCount[gold]));

  memset(&G1, 23, sizeof(struct gameState));
  initializeGame(numPlayers, k, seed, &G1);

  copperCountBefore = G1.supplyCount[copper];
  int silverCountBefore = G1.supplyCount[silver];
  G1.handCount[player] = 2;
  G1.hand[player][0] = mine;
  G1.hand[player][1] = silver;

  cardEffect(mine, 1, copper, 0, &G1, 0, &bonus);

  myAssert("Can trade copper for silver", (copperCountBefore - 1 == G1.supplyCount[copper] && silverCountBefore + 1 == G1.supplyCount[silver]));

  printf("\n\n");
  
  return 0;
}