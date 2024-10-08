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


typedef struct PlayerScore{
    int points;
    int no_bonus_tokens;
    int no_goods_tokens;
    int seals;
} PlayerScore;

// typedef struct CardGroup{
//     int diamonds;
//     int golds;
//     int silvers;
//     int spices;
//     int cloths;
//     int leathers;
//     int camels; //Not in enforced hand-size
// CHANGE THIS TO ARRAY INDEXED BY ENUM
// } CardGroup;

typedef struct GameData{
    int was_initialized;
    unsigned int seed;

    char turn_of;

    
    int market[CARD_GROUP_SIZE];
    int hand_plA[CARD_GROUP_SIZE];
    int hand_plB[CARD_GROUP_SIZE];
    PlayerScore playerA;
    PlayerScore playerB;
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
    } tokens;

    int deck[DECK_SIZE];
    int deck_ptr;

} GameData;

typedef struct GameState{
    char turn_of;
    
    int market[CARD_GROUP_SIZE];
    int hand_plA[CARD_GROUP_SIZE];
    int hand_plB[CARD_GROUP_SIZE];

    PlayerScore playerA;
    PlayerScore playerB;
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

    } tokens;

    int cards_in_deck;

} GameState;


void setSeed(GameData *game);

void initGameData(GameData* game);
int resetGameData(GameData* game);
void startGame(GameData* game);
void initializeGame(GameData *game);
void initializeRound(GameData *game);
void set_GameState_from_GameData(GameData* game_data, GameState* game_state);

int isHandSizeCorrect(int* card_group,int max);
int  checkDataIntegrity(GameData *game);

void set_finished_resources(GameData *game);
int sum_cards_player(int group[CARD_GROUP_SIZE]);
int sum_cards_market(int group[CARD_GROUP_SIZE]);
int  load_game_state(GameData *game);
void save_game_state(const GameData *game);

void process_arguments(GameData *game, int argc, char *argv[]);
void drawCardsFromDeck(int group[CARD_GROUP_SIZE],GameData* game,int cards);
int take_card_from_market(int market[CARD_GROUP_SIZE],int player_hand[CARD_GROUP_SIZE],int index);
void card_sale(GameData *game,PlayerScore* player_score,int player_hand[CARD_GROUP_SIZE], char card_type[], int no_cards);
void card_exchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char* hand_idx, char* market_idx, int camels);

int  is_game_over(PlayerScore *playerA, PlayerScore *playerB);
int  is_round_over(GameData *game);
void game_over(PlayerScore *playerA, PlayerScore *playerB);
void round_over(GameData *game);


void printGameState(GameData *game);
void print_help();


GameState interfaceJaipurEmulator();

#endif