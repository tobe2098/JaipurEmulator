#ifndef STATE_EMULATOR_HEADER
#define STATE_EMULATOR_HEADER
#include "game_data.h"
#include "prints.h"

#include <stdlib.h>

int  loadGameData(GameData *game);
void saveGameData(const GameData *game);
void dataPrint(const GameData *game);

int *getActivePlayerHand(GameData *game);

void gameStatePrint(GameData *game);
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB);
void roundOverPrint(GameData *game);

#endif