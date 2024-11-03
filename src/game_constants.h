#ifndef GAME_CONSTANTS_JAIPUR
#define GAME_CONSTANTS_JAIPUR

#include <stdint.h>

#define TRUE      1
#define FALSE     0
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Rules macros
#define JSON_ELEMENTS           41
#define GOOD_TYPES              6
#define BONUS_TOKEN_TYPES       3
#define MAX_BONUS_TOKENS        6
#define BONUS_TOKENS_DATA_ARRAY 9
#define BONUS_TOKENS_PER_VALUE  2
#define DECK_SIZE               52  // 53 would include the string termination character

#define FINISHED_GOODS_LIMIT    3
#define CAMEL_TOKEN_VAL         5
#define CAMELS_TOTAL            11
#define SEALS_TO_WIN            2

#define INITIAL_HAND_SIZE       5
#define STARTING_MARKET_CAMELS  3
#define CARDS_IN_MARKET         5

#define DIAMONDS_STARTING_DECK  6
#define GOLD_STARTING_DECK      6
#define SILVER_STARTING_DECK    6
#define SPICE_STARTING_DECK     8
#define CLOTH_STARTING_DECK     8
#define LEATHER_STARTING_DECK   10
#define CAMELS_STARTING_DECK    (CAMELS_TOTAL - STARTING_MARKET_CAMELS)

#define DIAMOND_TOKEN_SIZE      DIAMONDS_STARTING_DECK - 1
#define GOLD_TOKEN_SIZE         GOLD_STARTING_DECK - 1
#define SILVER_TOKEN_SIZE       SILVER_STARTING_DECK - 1
#define SPICE_TOKEN_SIZE        SPICE_STARTING_DECK - 1
#define CLOTH_TOKEN_SIZE        CLOTH_STARTING_DECK - 1
#define LEATHER_TOKEN_SIZE      LEATHER_STARTING_DECK - 1

#define LARGEST_TOKEN_SIZE \
  MAX(LEATHER_TOKEN_SIZE, MAX(CLOTH_TOKEN_SIZE, MAX(SPICE_TOKEN_SIZE, MAX(SILVER_TOKEN_SIZE, MAX(GOLD_TOKEN_SIZE, DIAMOND_TOKEN_SIZE)))))

// Data macros
// d = diamonds, g = gold, s = silver, p = spice, h = cloth, l = leather, c = camel
#define DIAMOND_CHAR 'd'
#define GOLD_CHAR    'g'
#define SILVER_CHAR  's'
#define SPICE_CHAR   'p'
#define CLOTH_CHAR   'h'
#define LEATHER_CHAR 'l'
#define CAMEL_CHAR   'c'

#define LAST_USEFUL_CHAR \
  MAX(DIAMOND_CHAR, MAX(GOLD_CHAR, MAX(SILVER_CHAR, MAX(SPICE_CHAR, MAX(CLOTH_CHAR, MAX(LEATHER_CHAR, CAMEL_CHAR))))))

// Custom names macros
#define PLAYER_A     "Lizzard-Tron"
#define PLAYER_B     "Croc-Terminator"

#define PLAYER_A_NUM 0
#define PLAYER_B_NUM 1

#if defined(__x86_64__) || defined(__ppc64__) || defined(_WIN64) || defined(__aarch64__)
// 64-bit architecture
typedef uint64_t size_mt;
#define SIZE_MT_MAX UINT64_MAX
#else
// 32-bit architecture
typedef uint32_t size_mt;
#define SIZE_MT_MAX UINT32_MAX
#endif

// #define PLAYER_A_STRLEN strlen(PLAYER_A)
// #define PLAYER_B_STRLEN strlen(PLAYER_B)

// Card type index
typedef enum card_index {
  diamonds = 0,
  golds    = 1,
  silvers  = 2,
  spices   = 3,
  cloths   = 4,
  leathers = 5,
  camels   = 6,
  CARD_GROUP_SIZE,
} card_index;

// extern const int bonus_template_3[MAX_BONUS_TOKENS];
// extern const int bonus_template_4[MAX_BONUS_TOKENS];
// extern const int bonus_template_5[MAX_BONUS_TOKENS];

#endif