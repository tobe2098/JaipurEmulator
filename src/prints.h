#ifndef JAIPUR_PRINTS_HEADER
#define JAIPUR_PRINTS_HEADER
#include "config.h"
#include "flags.h"
#include "ltables.h"
#include "utils.h"

#include <stdio.h>

void printGoodsTokenArray(char name, const int* restrict array, int size, int cutoff);
void printWinningTrophy(int player);
void printWelcomeMessage(void);
void printVersion(void);
void printNewRoundMessage(int player);
void printWinner(int player);
void printHelp(void);
void printRules(void);

void printCardGroup(int* restrict card_group, int bool_camel);

#endif