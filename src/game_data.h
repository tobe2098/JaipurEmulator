#ifndef PLAYER_INFO_HEADER_JAIPUR
#define PLAYER_INFO_HEADER_JAIPUR
#include "cache.h"
#include "flags.h"
#include "game_constants.h"
// #include "lalloc.h"
#include "ltables.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <limits.h>
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

// #define GAME_DATA_MEMORY_TO_COPY sizeof(GameData) - CACHE_LINE_SIZE

typedef struct PlayerScore {
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

typedef struct GameData {
    int          was_initialized;
    unsigned int seed;

    int turn_of;

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
    // Input-output variables only, here is where data is written by user in library, not in the executable
    // What is considered the game state, together with the cardgroups and the player scores.
    int cards_in_deck;
    int resource_tks[RESOURCE_TYPES];
    int bonus_tks[BONUS_TOKEN_TYPES];
    int bonus_used[BONUS_TOKENS_DATA_ARRAY];

} GameData;

// typedef struct GameState {
//     // Input-only data-type
//     int turn_of;

//     int market[CARD_GROUP_SIZE];
//     int hand_plA[CARD_GROUP_SIZE];
//     int hand_plB[CARD_GROUP_SIZE];

//     PlayerScore playerA;
//     PlayerScore playerB;

//     int resource_tks[RESOURCE_TYPES];
//     int bonus_tks[BONUS_TOKEN_TYPES];

//     int cards_in_deck;
//     // GameData *game_data;

// } GameState;

void initDeck(GameData *game);
void initDeckCustom(GameData *game, int cards_used[CARD_GROUP_SIZE]);
void setSeed(GameData *game);
void setSeedCustom(GameData *game, int bonus_tokens_used[BONUS_TOKENS_DATA_ARRAY], int cards_used[CARD_GROUP_SIZE]);

void initGameData(GameData *game, unsigned int seed);
int  roundSetGameData(GameData *game);
void startRound(GameData *game);
void startGame(GameData *game, unsigned int seed);
void initRound(GameData *game);

int isHandSizeCorrect(int *card_group, int max);
int checkDataIntegrity(GameData *game);
int checkStateIntegrity(GameData *state, int used_cards[CARD_GROUP_SIZE]);

int computeFinishedResources(GameData *game);
int sumOfCardsGroup(int group[CARD_GROUP_SIZE], int not_camels_bool);
// int getCardTypeIndex(int group[CARD_GROUP_SIZE],int card_index_input);

// Expecting DATA_IS_OKAY
int processAction(GameData *game, int argc, char *argv[]);
int drawCardsFromDeck(int group[CARD_GROUP_SIZE], GameData *game, int cards);
int takeCardFromMarket(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char card);
int cardSale(GameData *game, PlayerScore *player_score, int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards);
int cardExchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char *hand_idx, char *market_idx, int camels_no,
                 int hand_idx_len, int market_goods_positions_len);

// Also have to be in the Julia lib interface
int isGameOver(PlayerScore *playerA, PlayerScore *playerB);
int isRoundOver(GameData *game);
int endingChecks(GameData *game, int flags);
int compRoundWinningPlayer(GameData *game);

int getMemoryForGames(int number_games);

GameData *initLibGameStateCustom(GameData *game_state, unsigned int seed);
GameData *initLibGameStateScratch(unsigned int seed);
void      cloneLibGameState(GameData *game_state_out, GameData *game_state_in);
void      freeLibGameData(GameData *game_data);
int       processLibAction(GameData *game, int argc, char *argv[], int flags);

void setGameDataLib(GameData *game_data);
void initGameDataFromState(GameData *game_data_out, unsigned int seed, int used_cards[CARD_GROUP_SIZE]);

#endif