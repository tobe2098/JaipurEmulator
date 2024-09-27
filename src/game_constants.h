#ifndef GAME_CONSTANTS_JAIPUR
#define GAME_CONSTANTS_JAIPUR

#define MAX_BONUS_TOKENS 6
#define DECK_SIZE 52 //53 would include the string termination character

#define DIAMOND_T_SIZE 5
#define GOLD_T_SIZE 5
#define SILVER_T_SIZE 5
#define SPICE_T_SIZE 7
#define CLOTH_T_SIZE 7
#define LEATHER_T_SIZE 9
#define FINISHED_GOODS_LIMIT 3
#define CAMEL_TOKEN_VAL 5
#define CAMELS_TOTAL 11
#define SEALS_TO_WIN 2

extern const int diamond_tokens[];
extern const int gold_tokens[];
extern const int silver_tokens[];

extern const int spice_tokens[];
extern const int cloth_tokens[];
extern const int leather_tokens[];

extern const int bonus_template_3[];
extern const int bonus_template_4[];
extern const int bonus_template_5[];

extern const char deck[];
#endif