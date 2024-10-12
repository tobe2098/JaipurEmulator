#include "game_constants.h"

const int no_cards_lookup_table[CARD_GROUP_SIZE]={DIAMONDS_STARTING_DECK,GOLD_STARTING_DECK,SILVER_STARTING_DECK,SPICE_STARTING_DECK,CLOTH_STARTING_DECK,LEATHER_STARTING_DECK,CAMELS_TOTAL};
const int cards_starting_deck_lookup_table[CARD_GROUP_SIZE]={DIAMONDS_STARTING_DECK,GOLD_STARTING_DECK,SILVER_STARTING_DECK,SPICE_STARTING_DECK,CLOTH_STARTING_DECK,LEATHER_STARTING_DECK,STARTING_MARKET_CAMELS};

const int char_to_enum_lookup_table[LAST_USEFUL_CHAR+1]={[0 ... LAST_USEFUL_CHAR]=-1,[DIAMOND_CHAR]=diamonds,[GOLD_CHAR]=golds,[SILVER_CHAR]=silvers,[SPICE_CHAR]=spices,[CLOTH_CHAR]=cloths,[LEATHER_CHAR]=leathers,[CAMEL_CHAR]=camels};
const int enum_to_char_lookup_table[CARD_GROUP_SIZE]={DIAMOND_CHAR,GOLD_CHAR,SILVER_CHAR,SPICE_CHAR,CLOTH_CHAR,LEATHER_CHAR,CAMEL_CHAR};

const int diamond_tokens[DIAMOND_TOKEN_SIZE] = { 7, 7, 5, 5, 5 };
const int gold_tokens[GOLD_TOKEN_SIZE]    = { 6, 6, 5, 5, 5 };
const int silver_tokens[SILVER_TOKEN_SIZE]  = { 5, 5, 5, 5, 5 };

const int spice_tokens[SPICE_TOKEN_SIZE]   = { 5, 3, 3, 2, 2, 1, 1 };
const int cloth_tokens[CLOTH_TOKEN_SIZE]   = { 5, 3, 3, 2, 2, 1, 1 };
const int leather_tokens[LEATHER_TOKEN_SIZE] = { 4, 3, 2, 1, 1, 1, 1, 1, 1 };


const int bonus_template_3[MAX_BONUS_TOKENS] = { 3, 3, 2, 2, 1, 1 };
const int bonus_template_4[MAX_BONUS_TOKENS] = { 6, 6, 5, 5, 4, 4 };
const int bonus_template_5[MAX_BONUS_TOKENS] = { 9, 9, 8, 8, 7, 7 };

const char deck[DECK_SIZE+1]="ddddddggggggsssssspppppppphhhhhhhhllllllllllcccccccc\0";
//Three camels are in the market at the start of all games
//d = diamonds, g = gold, s = silver, p = spice, h = cloth, l = leather, c = camel
