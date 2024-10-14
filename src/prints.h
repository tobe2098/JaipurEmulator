#ifndef JAIPUR_PRINTS_HEADER
#define JAIPUR_PRINTS_HEADER
#include "config.h"
#include "ltables.h"

void print_array_goods(char* name, const int* array, int size, int cutoff);
void print_winning_trophy(char player);
void print_welcome_message();
void print_version();
void print_new_round_message(char player);
void print_player_wins(char player);
void print_help();
void print_rules();
void printCardGroup(int* card_group, int bool_camel);

#endif