#include "ltables.h"

const int no_cards_lookup_table[CARD_GROUP_SIZE] = {
  DIAMONDS_STARTING_DECK, GOLD_STARTING_DECK,    SILVER_STARTING_DECK, SPICE_STARTING_DECK,
  CLOTH_STARTING_DECK,    LEATHER_STARTING_DECK, CAMELS_TOTAL
};
const int cards_starting_deck_lookup_table[CARD_GROUP_SIZE] = { DIAMONDS_STARTING_DECK, GOLD_STARTING_DECK,  SILVER_STARTING_DECK,
                                                                SPICE_STARTING_DECK,    CLOTH_STARTING_DECK, LEATHER_STARTING_DECK,
                                                                STARTING_MARKET_CAMELS };

const int char_to_enum_lookup_table[LAST_USEFUL_CHAR + 1] = {
  [0 ... LAST_USEFUL_CHAR] = -1, [DIAMOND_CHAR] = diamonds, [GOLD_CHAR] = golds,       [SILVER_CHAR] = silvers,
  [SPICE_CHAR] = spices,         [CLOTH_CHAR] = cloths,     [LEATHER_CHAR] = leathers, [CAMEL_CHAR] = camels
};
const int enum_to_char_lookup_table[CARD_GROUP_SIZE] = { DIAMOND_CHAR, GOLD_CHAR,    SILVER_CHAR, SPICE_CHAR,
                                                         CLOTH_CHAR,   LEATHER_CHAR, CAMEL_CHAR };

// Token definitions
extern const ResourceTokens resource_tokens[RESOURCE_TYPES] = {
  [diamonds] = { { 7, 7, 5, 5, 5, -1, -1, -1, -1 }, DIAMOND_TOKEN_SIZE },  // Diamond Tokens
  [golds]    = { { 6, 6, 5, 5, 5, -1, -1, -1, -1 }, GOLD_TOKEN_SIZE },     // Gold Tokens
  [silvers]  = { { 5, 5, 5, 5, 5, -1, -1, -1, -1 }, SILVER_TOKEN_SIZE },   // Silver Tokens
  [spices]   = { { 5, 3, 3, 2, 2, 1, 1, -1, -1 }, SPICE_TOKEN_SIZE },      // Spice Tokens
  [cloths]   = { { 5, 3, 3, 2, 2, 1, 1, -1, -1 }, CLOTH_TOKEN_SIZE },      // Cloth Tokens
  [leathers] = { { 4, 3, 2, 1, 1, 1, 1, 1, 1 }, LEATHER_TOKEN_SIZE }       // Leather Tokens
};