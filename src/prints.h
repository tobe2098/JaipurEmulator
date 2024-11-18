#ifndef JAIPUR_PRINTS_HEADER
#define JAIPUR_PRINTS_HEADER
#include "config.h"
#include "flags.h"
#include "ltables.h"
#include "utils.h"

#include <stdio.h>

void printGoodsTokenArray(char name, const int* array, int size, int cutoff);
void printWinningTrophy(int player);
void printWelcomeMessage();
void printVersion();
void printNewRoundMessage(int player);
void printWinner(int player);
void printHelp();
void printRules();

void printCardGroup(int* card_group, int bool_camel);

#endif