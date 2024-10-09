#include "game_constants.h"

const int enum_to_char_lookup_table[]={DIAMOND_CHAR,GOLD_CHAR,SILVER_CHAR,SPICE_CHAR,CLOTH_CHAR,LEATHER_CHAR,CAMEL_CHAR};
const int max_lookup_table[]={DIAMOND_T_SIZE+1,GOLD_T_SIZE+1,SILVER_T_SIZE+1,SPICE_T_SIZE+1,CLOTH_T_SIZE+1,LEATHER_T_SIZE+1,CAMELS_TOTAL};

const int char_to_enum_lookup_table[CHAR_LOOKUP_TABLE_SIZE]={[0 ... CHAR_LOOKUP_TABLE_SIZE-1]=-1,[(int)DIAMOND_CHAR]=diamonds,[(int)GOLD_CHAR]=golds,[(int)SILVER_CHAR]=silvers,[(int)SPICE_CHAR]=spices,[(int)CLOTH_CHAR]=cloths,[(int)LEATHER_CHAR]=leathers,[(int)CAMEL_CHAR]=camels};

const int diamond_tokens[] = { 7, 7, 5, 5, 5 };
const int gold_tokens[]    = { 6, 6, 5, 5, 5 };
const int silver_tokens[]  = { 5, 5, 5, 5, 5 };

const int spice_tokens[]   = { 5, 3, 3, 2, 2, 1, 1 };
const int cloth_tokens[]   = { 5, 3, 3, 2, 2, 1, 1 };
const int leather_tokens[] = { 4, 3, 2, 1, 1, 1, 1, 1, 1 };


const int bonus_template_3[] = { 3, 3, 2, 2, 1, 1 };
const int bonus_template_4[] = { 6, 6, 5, 5, 4, 4 };
const int bonus_template_5[] = { 9, 9, 8, 8, 7, 7 };

const char deck[]="ddddddggggggsssssspppppppphhhhhhhhllllllllllcccccccc\0";
//Three camels are in the market at the start of all games
//d = diamonds, g = gold, s = silver, p = spice, h = cloth, l = leather, c = camel
