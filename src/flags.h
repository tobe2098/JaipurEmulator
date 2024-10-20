#ifndef JAIPUR_ERRORS_HEADER
#define JAIPUR_ERRORS_HEADER
#include "game_constants.h"

#define NO_TURN_HAPPENED_FLAG  0  // No need to put it in the flag if there are other numbers
#define TURN_HAPPENED_FLAG     1 << 0

#define DATA_NOT_INIT_FLAG     1 << 1
#define TOO_FEW_ARGS_FLAG      1 << 2
#define ERROR_PRINTING_FLAG    1 << 3
#define TOO_MANY_C_MARKET_FLAG 1 << 4
#define TOO_MANY_C_HAND_FLAG   1 << 5

// Because the first 4 bits are free you can use them to point to the lacking resource, and then EXOR to check

#define TOO_FEW_C_MARKET_FLAG 1 << 6  // There are not enough cards in the market
#define TOO_FEW_C_HAND_FLAG   1 << 7  // There are not enough cards in the market
#define ARGS_MISS_MATCH_FLAG  1 << 8  // You do not own enough cards
#define ARG_OVERFLOW_FLAG     1 << 9  // You do not own enough cards

#define NOT_ALLOWED_FLAG      1 << 10
#define MISSING_CARD_FLAG     1 << 11
#define MIXING_GOODS_CAMELS   1 << 12
#define DATA_CORRUPTED_FLAG   1 << 13
#define DATA_OKAY_FLAG        1 << 14
#define DRAW_FLAG             1 << 15

#define NO_CAMELS             1 << 16
// #define UNWRITTEN_ERROR     1 << 15
#endif