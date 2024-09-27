#include "state_emulator_api.h"

gameState func(){
    static gameData g_data={.was_initialized=0};
    init(g_data); //Initialize only if the was_initialized is zero, or if the round is over?

    //If the round is finished by the last action, do not reset the state
    gameState g_state;
    set_gameState_from_gameData(&g_data, &g_state);
    return g_state;
}

void set_gameState_from_gameData(gameData *game_data, gameState *game_state){

    game_state->turn_of=game_data->turn_of;
    game_state->market=game_data->market;
    game_state->hand_plA=game_data->hand_plA;
    game_state->hand_plB=game_data->hand_plB;
    game_state->playerA=game_data->playerA;
    game_state->playerB=game_data->playerB;
    game_state->remaining_tokens.bonus_3=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_3_ptr;
    game_state->remaining_tokens.bonus_4=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_4_ptr;
    game_state->remaining_tokens.bonus_5=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_5_ptr;
    game_state->remaining_tokens.diamond;
    game_state->remaining_tokens.gold;
    game_state->remaining_tokens.silver;
    game_state->remaining_tokens.spice;
    game_state->remaining_tokens.cloth;
    game_state->remaining_tokens.leather;
    game_state->cards_in_deck=DECK_SIZE-game_data->deck_ptr;

typedef struct gameState{
    
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

}
