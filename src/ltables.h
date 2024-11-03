#ifndef JAIPUR_LOOKUP_TABLES_HEADER
#define JAIPUR_LOOKUP_TABLES_HEADER

#include "game_constants.h"

typedef struct {
    int tokens[LARGEST_TOKEN_SIZE];  // Static array instead of a pointer
    int size;                        // Current size of the token array
} GoodTokens;

extern const GoodTokens good_tokens[GOOD_TYPES];

extern const int enum_to_char_lookup_table[CARD_GROUP_SIZE];
extern const int no_cards_lookup_table[CARD_GROUP_SIZE];
extern const int cards_starting_deck_lookup_table[CARD_GROUP_SIZE];
extern const int char_to_enum_lookup_table[LAST_USEFUL_CHAR + 1];

#endif