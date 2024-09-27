#ifndef STATE_EMULATOR_API_HEADER
#define STATE_EMULATOR_API_HEADER

#include "game_data.h"

typedef struct gameState{
    char turn_of;
    
    card_group market;
    card_group hand_plA;
    card_group hand_plB;
    player_score playerA;
    player_score playerB;
    struct{
        int diamond;
        int gold;
        int silver;
        int spice;
        int cloth;
        int leather;

        int bonus_3;
        int bonus_4;
        int bonus_5;

    } remaining_tokens;

    int cards_in_deck;

} gameState;

void set_gameState_from_gameData(gameData* game_data, gameState* game_state);


#endif