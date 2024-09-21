#include "game_data.h"


gameData func(){
    static gameData gdata={.was_initialized=0};
    init(gdata); //Initialize only if the was_initialized is zero, or if the round is over?

    //If the round is finished by the last action, do not reset the state
    return gdata;
}


