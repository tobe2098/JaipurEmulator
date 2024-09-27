#include "game_state.h"

GameState interfaceJaipurEmulator(){
    static GameData g_data={.was_initialized=0};
    init(g_data); //Initialize only if the was_initialized is zero, or if the round is over?

    //If the round is finished by the last action, do not reset the state
    GameState g_state;
    set_GameState_from_GameData(&g_data, &g_state);
    return g_state;
}

void set_GameState_from_GameData(GameData *game_data, GameState *game_state){
    game_state->turn_of=game_data->turn_of;
    game_state->market=game_data->market;
    game_state->hand_plA=game_data->hand_plA;
    game_state->hand_plB=game_data->hand_plB;
    game_state->playerA=game_data->playerA;
    game_state->playerB=game_data->playerB;
    game_state->remaining_tokens.bonus_3=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_3_ptr;
    game_state->remaining_tokens.bonus_4=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_4_ptr;
    game_state->remaining_tokens.bonus_5=MAX_BONUS_TOKENS-game_data->tokens_state.bonus_5_ptr;
    game_state->remaining_tokens.diamond=DIAMOND_T_SIZE-game_data->tokens_state.diamond_ptr;
    game_state->remaining_tokens.gold=GOLD_T_SIZE-game_data->tokens_state.gold_ptr;
    game_state->remaining_tokens.silver=SILVER_T_SIZE-game_data->tokens_state.silver_ptr;
    game_state->remaining_tokens.spice=SPICE_T_SIZE-game_data->tokens_state.spice_ptr;
    game_state->remaining_tokens.cloth=CLOTH_T_SIZE-game_data->tokens_state.cloth_ptr;
    game_state->remaining_tokens.leather=LEATHER_T_SIZE-game_data->tokens_state.leather_ptr;
    game_state->cards_in_deck=DECK_SIZE-game_data->deck_ptr;
}
