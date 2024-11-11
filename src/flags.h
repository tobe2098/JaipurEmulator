#ifndef JAIPUR_ERRORS_HEADER
#define JAIPUR_ERRORS_HEADER
#include "game_constants.h"

#define DATA_WAS_INIT          1 << 0  // No need to put it in the flag if there are other numbers
#define TURN_HAPPENED_FLAG     1 << 1

#define DATA_NOT_INIT_FLAG     1 << 2
#define TOO_FEW_ARGS_FLAG      1 << 3
#define ERROR_PRINTING_FLAG    1 << 4
#define TOO_MANY_C_MARKET_FLAG 1 << 5
#define TOO_MANY_C_HAND_FLAG   1 << 6

// Because the first 4 bits are free you can use them to point to the lacking good, and then EXOR to check

#define TOO_FEW_C_MARKET_FLAG 1 << 7   // There are not enough cards in the market
#define TOO_FEW_C_HAND_FLAG   1 << 8   // There are not enough cards in the market
#define ARGS_MISS_MATCH_FLAG  1 << 9   // You do not own enough cards
#define ARG_OVERFLOW_FLAG     1 << 10  // You do not own enough cards

#define NOT_ALLOWED_FLAG      1 << 11
#define MISSING_CARD_FLAG     1 << 12
#define MIXING_GOODS_CAMELS   1 << 13
#define DATA_CORRUPTED_FLAG   1 << 14
#define DATA_OKAY_FLAG        1 << 15
#define DRAW_FLAG             1 << 16

#define NO_CAMELS             1 << 17
#define GAME_OVER             1 << 18
#define ROUND_OVER            1 << 19
#define NO_GAME_PRINT_FLAG    1 << 20
#define TOO_FEW_CARDS_SALE    1 << 21

#define CANNOT_SELL_CAMELS    1 << 22
#define ONLY_PRINT_HAND       1 << 23
#define CARD_DOES_NOT_EXIST   1 << 24
#define LOGIC_ERROR_FLAG      1 << 25
// #define UNWRITTEN_ERROR     1 << 15
#endif