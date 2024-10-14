#ifndef JAIPUR_ERRORS_HEADER
#define JAIPUR_ERRORS_HEADER
#include "game_constants.h"

#define NO_TURN_HAPPENED 0  // No need to put it in the flag if there are other numbers
#define TURN_HAPPENED    1 << 0

#define DATA_NOT_INIT    1 << 1
#define TOO_FEW_ARGS     1 << 2
#define TOO_MANY_CARDS   1 << 4
// Because the first 4 bits are free you can use them to point to the lacking resource, and then EXOR to check
#define TOO_FEW_CARDS       1 << 5  // There are not enough cards in the market
#define MARKET              1 << 6
#define HAND                1 << 7  // You do not own enough cards
#define ARGS_DO_NOT_MATCH   1 << 8  // You do not own enough cards
#define ARG_OVERFLOW        1 << 9  // You do not own enough cards

#define NOT_ALLOWED_ACTION  1 << 10
#define MISSING_CARD        1 << 11
#define MIXING_GOODS_CAMELS 1 << 12
#define DATA_IS_CORRUPTED   1 << 13
#define DATA_IS_OKAY        1 << 14
#define DRAW                1 << 15
// #define UNWRITTEN_ERROR     1 << 15
#endif