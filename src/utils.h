#ifndef GAME_UTILS_JAIPUR
#define GAME_UTILS_JAIPUR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "game_constants.h"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <linux/limits.h>
#include <unistd.h>
#define MAX_PATH PATH_MAX
#elif defined(__APPLE__)
#include <sys/syslimits.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#define MAX_PATH PATH_MAX
#endif

void randomize_index_array(int arr[], int size);
void print_array_goods(char* name, const int* array, int size, int cutoff);
void print_winning_trophy(char player);
void print_welcome_message();
void print_version();
void print_new_round_message(char player);
void print_player_wins(char player);
void printCardGroup(int* card_group,int bool_camel);
void find_data_path(char* data_path);
#endif