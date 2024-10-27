#ifndef STATE_EMULATOR_HEADER
#define STATE_EMULATOR_HEADER
#include "game_data.h"
#include "prints.h"

int  load_game_data(GameData *game);
void save_game_data(const GameData *game);

int  endingChecks(GameData *game);
int *getActivePlayerHand(GameData *game);

void gameStatePrint(GameData *game);
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB);
void roundOverPrint(GameData *game);

#endif