#ifndef JAIPUR_PRINTS_HEADER
#define JAIPUR_PRINTS_HEADER
#include "config.h"
#include "flags.h"
#include "ltables.h"

#include <stdio.h>

void print_array_goods(char* name, const int* array, int size, int cutoff);
void print_winning_trophy(int player);
void print_welcome_message();
void print_version();
void print_new_round_message(int player);
void print_player_wins(int player);
void print_help();
void print_rules();

void printCardGroup(int* card_group, int bool_camel);

#endif