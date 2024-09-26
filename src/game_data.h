#ifndef PLAYER_INFO_HEADER_JAIPUR
#define PLAYER_INFO_HEADER_JAIPUR
#include "game_constants.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#define MAX_PATH PATH_MAX
#include <limits.h>
#include <unistd.h>
#elif defined(__APPLE__)
#define MAX_PATH PATH_MAX
#include <limits.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#endif

typedef struct player_score{
    int points;
    int no_bonus_tokens;
    int no_goods_tokens;
    int seals;
} player_score;

typedef struct card_group{
    int diamonds;
    int golds;
    int silvers;
    int spices;
    int cloths;
    int leathers;
    int camels; //Not in enforced hand-size

} card_group;

typedef struct gameData{
    int was_initialized;
    int seed;

    char turn_of;

    
    card_group market;
    card_group hand_plA;
    card_group hand_plB;
    player_score playerA;
    player_score playerB;
    struct{
        int diamond_ptr;
        int gold_ptr;
        int silver_ptr;
        int spice_ptr;
        int cloth_ptr;
        int leather_ptr;

        int bonus_3_ptr;
        int bonus_4_ptr;
        int bonus_5_ptr;

        int bonus_3_arr[MAX_BONUS_TOKENS];
        int bonus_4_arr[MAX_BONUS_TOKENS];
        int bonus_5_arr[MAX_BONUS_TOKENS];

        int finished_counter;
    } tokens_state;

    int deck[DECK_SIZE];
    int deck_ptr;

} gameData;
typedef struct gameState{
    char turn_of;
    
    card_group market;
    card_group hand_plA;
    card_group hand_plB;
    player_score playerA;
    player_score playerB;
    struct{
        int diamond;
        int gold;
        int silver;
        int spice;
        int cloth;
        int leather;

        int bonus_3;
        int bonus_4;
        int bonus_5;

    } remaining_tokens;

    int cards_in_deck;

} gameState;

void set_seed(gameData *game);
void initialize_gameData(gameData* game);
void set_gameState_from_gameData(gameData* game_data, gameState* game_state);
void initialize_game(gameData *game);
void initialize_round(gameData *game);
void print_game_state(gameData *game);
int  check_data_integrity(gameData *game);
void set_finished_resources(gameData *game);
int  load_game_state(gameData *game);
void save_game_state(const gameData *game);
void print_help();
void process_arguments(gameData *game, int argc, char *argv[]);
void card_sale(player_score *player, gameData *game, char card_type[], int no_cards);
int  is_game_over(player_score *playerA, player_score *playerB);
int  is_round_over(gameData *game);
void game_over(player_score *playerA, player_score *playerB);
void round_over(gameData *game);

#endif