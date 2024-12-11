#ifndef PLAYER_INFO_HEADER_JAIPUR
#define PLAYER_INFO_HEADER_JAIPUR
#include "flags.h"
#include "game_constants.h"
// #include "lalloc.h"
#include "ltables.h"
#include "utils.h"

#include <stdalign.h>
#include <stddef.h>
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

#define CACHE_LINE_SIZE 64
// #define GAME_DATA_MEMORY_TO_COPY sizeof(GameData) - CACHE_LINE_SIZE

typedef struct PlayerScore {
    int points;
    int no_bonus_tokens;
    int no_goods_tokens;
    int seals;
} PlayerScore;

// #pragma pack(push, 1)  // Disable padding
typedef struct GameData {
    int          was_initialized;
    unsigned int seed;

    int turn_of;

    int market[CARD_GROUP_SIZE];
    int hand_plA[CARD_GROUP_SIZE];
    int hand_plB[CARD_GROUP_SIZE];

    PlayerScore playerA;
    PlayerScore playerB;

    int good_tk_ptrs[GOOD_TYPES];

    int bonus_tk_ptrs[BONUS_TOKEN_TYPES];
    int bonus_tk_arrays[BONUS_TOKEN_TYPES][MAX_BONUS_TOKENS];

    int  deck_ptr;
    char deck[DECK_SIZE];
    // Input-output variables only, here is where data is written by user in library, not in the executable
    // What is considered the game state, together with the cardgroups and the player scores.
    int cards_in_deck;
    int good_tks[GOOD_TYPES];
    int bonus_tks[BONUS_TOKEN_TYPES];
    // alignas(CACHE_LINE_SIZE) int bonus_used[BONUS_TOKENS_DATA_ARRAY];
    int bonus_used[BONUS_TOKENS_DATA_ARRAY];

} GameData;  // Possibly 8 byte aligned
// #pragma pack(pop)

void initDeck(GameData *restrict game);
void initDeckCustom(GameData *restrict game, int *restrict cards_used);
void setSeed(GameData *restrict game);
void setSeedCustom(GameData *restrict game, int bonus_tokens_used[BONUS_TOKENS_DATA_ARRAY], int *restrict cards_used);

void initGameData(GameData *restrict game, unsigned int seed);
int  initRoundGameData(GameData *restrict game, unsigned int seed);
void startRound(GameData *restrict game);
void startGame(GameData *restrict game, unsigned int seed);
void startNextRound(GameData *restrict game, unsigned int seed);

int checkDataIntegrity(GameData *restrict game);
int checkStateIntegrity(GameData *restrict state, int *restrict used_cards);

int computeFinishedGoods(GameData *restrict game);
int sumOfCardsGroup(int *restrict group, int not_camels_bool);
// int getCardTypeIndex(int group[CARD_GROUP_SIZE],int card_index_input);

// Expecting DATA_IS_OKAY
int processAction(GameData *restrict game, int argc, char *restrict argv[]);
int drawCardsFromDeck(int group[CARD_GROUP_SIZE], GameData *restrict game, int cards);
int updateMarket(GameData *restrict game);
int takeCardFromMarket(int *restrict market, int *restrict player_hand, char card);
int cardSale(GameData *restrict game, PlayerScore *player_score, int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards);
int cardExchange(int *restrict market, int *restrict player_hand, char *restrict hand_idx, char *restrict market_idx, int hand_idx_len,
                 int market_goods_positions_len);

// Also have to be in the Julia lib interface
int  isGameOver(PlayerScore *restrict playerA, PlayerScore *restrict playerB);
int  isRoundOver(GameData *restrict game);
int  endingChecks(GameData *restrict game, int flags);
int  compRoundWinningPlayer(GameData *restrict game);
void giveRewards(GameData *restrict game, int flags);

// int getMemoryForGames(int number_games);

GameData *initLibGameDataCustom(GameData *restrict game_state, unsigned int seed);
GameData *initLibGameDataScratch(unsigned int seed);
GameData *cloneLibGameData(GameData *restrict game_state_src);
GameData *freeLibGameData(GameData *restrict game_data);
int       processLibAction(GameData *restrict game, int argc, char *restrict argv[], int flags);

void setGameDataLib(GameData *restrict game_data);
void initGameDataFromState(GameData *restrict game_data_out, unsigned int seed, int *restrict used_cards);

#endif