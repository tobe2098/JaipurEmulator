#ifndef STATE_EMULATOR_API_HEADER
#define STATE_EMULATOR_API_HEADER

#include "game_data.h"

typedef struct GameState{
    char turn_of;
    
    CardGroup market;
    CardGroup hand_plA;
    CardGroup hand_plB;
    PlayerScore playerA;
    PlayerScore playerB;
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

} GameState;

void set_GameState_from_GameData(GameData* game_data, GameState* game_state);
GameState interfaceJaipurEmulator();

#endif