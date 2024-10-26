#ifndef JAIPUR_PRINTS_HEADER
#define JAIPUR_PRINTS_HEADER
#include "config.h"
#include "flags.h"
#include "ltables.h"

#include <stdio.h>

void printGoodsTokenArray(char name, const int* array, int size, int cutoff);
void printWinningTrophy(int player);
void printWelcomeMessage();
void printVersion();
void print_new_round_message(int player);
void printWinner(int player);
void print_help();
void print_rules();

void printCardGroup(int* card_group, int bool_camel);

#endif