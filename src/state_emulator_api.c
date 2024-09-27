#include "game_data.h"
#include "state_emulator_api.h"

void initialize_static_gameData(gameData *game){
    if (game->was_initialized) return;
    game->
}

gameState func(){
    static gameData g_data={.was_initialized=0};
    init(g_data); //Initialize only if the was_initialized is zero, or if the round is over?

    //If the round is finished by the last action, do not reset the state
    gameState g_state;
    set_gameState_from_gameData(&g_data, &g_state);
    return g_state;
}
