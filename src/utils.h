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
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#include <unistd.h>
#define MAX_PATH PATH_MAX
#endif

void randomize_int_array(int arr[], int size);
void randomize_char_array(char arr[], int size);
void randomize_void_array(void* arr, int arr_size, int type_size);
void print_array_goods(char* name, const int* array, int size, int cutoff);
void print_winning_trophy(char player);
void print_welcome_message();
void print_version();
void print_new_round_message(char player);
void print_player_wins(char player);
void print_help();
void print_rules();
void printCardGroup(int* card_group, int bool_camel);
void find_data_path(char* data_path);

const char* getPlayerName(char player);

#endif