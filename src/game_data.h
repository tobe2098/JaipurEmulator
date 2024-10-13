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

    
    int resource_tk_ptrs[RESOURCE_TYPES];
    
    int bonus_tk_ptrs[BONUS_TOKEN_TYPES];
    int bonus_tk_arrays[BONUS_TOKEN_TYPES][MAX_BONUS_TOKENS];

    int deck_ptr;
    int deck[DECK_SIZE];

} GameData;

typedef struct GameState{
    char turn_of;
    
    int market[CARD_GROUP_SIZE];
    int hand_plA[CARD_GROUP_SIZE];
    int hand_plB[CARD_GROUP_SIZE];

    PlayerScore playerA;
    PlayerScore playerB;

    int resource_tks[RESOURCE_TYPES];
    int bonus_tks[BONUS_TOKEN_TYPES];

    int cards_in_deck;

} GameState;

void initDeck(GameData *game);
void setSeed(GameData *game);

void initGameData(GameData* game);
int resetGameData(GameData* game);
void startRound(GameData* game);
void initGame(GameData *game);
void initRound(GameData *game);
void set_GameState_from_GameData(GameData* game_data, GameState* game_state);

int isHandSizeCorrect(int* card_group,int max);
int  checkDataIntegrity(GameData *game);

int computeFinishedResources(GameData *game);
int sumOfCardsGroup(int group[CARD_GROUP_SIZE],int not_camels_bool);
int getCardTypeIndex(int group[CARD_GROUP_SIZE],int card_index_input);
int  load_game_state(GameData *game);
void save_game_state(const GameData *game);

void processAction(GameData *game, int argc, char *argv[]);
int drawCardsFromDeck(int group[CARD_GROUP_SIZE],GameData* game,int cards);
int takeCardFromMarket(int market[CARD_GROUP_SIZE],int player_hand[CARD_GROUP_SIZE],int index);
void cardSale(GameData *game,PlayerScore* player_score,int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards);
int cardExchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char* hand_idx, char* market_idx, int camels_no,int hand_idx_len,int market_goods_positions_len);

int  isGameOver(PlayerScore *playerA, PlayerScore *playerB);
int  isRoundOver(GameData *game);
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB);
int roundOverWinningPlayer(GameData *game);
void roundOverPrint(GameData *game);


void printGameState(GameData *game);


GameState interfaceJaipurEmulator();

#endif