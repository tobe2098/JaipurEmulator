# JaipurEmulator
Emulates the game (by default the screen is cleared after every action is run, so that the other player does not see your hand).



## Rules of the game Jaipur
1.

# Use instructions
## CLI exec
Only accepts one action per call
- The windows executable assumes that msys2 is installed. More concretely, it assumes that reset.exe (from Unix) is found in the PATH. If it is not, it might not be possible to run the executable.

## Julia

### Using the library
To see how to use the Julia library, see `example.jl`. There are a series of functions to:

1. Create, duplicate and clone games (includes allocation).
2. Perform game actions.
3. Check if the round or game is over and check which player won, and give the proper seal to the winning player.
4. As above but done automatically using the flag system.
5. Free the allocated games.

If the player tries an action that is not possible at the moment, if the data is somehow invalidated or more, there are multiple options in how to deal with it. The `process_game_action` function takes a boolean to automatically print errors, and the function itself returns an `Int32`, of which each set bit has a meaning, which can also be printed in the Julia function `flag_identifiers` or `flag_set_bit_spositions`.

Because of how the seed is used only in initialization or data read, and the library does not do the data reads (only the executable does it), you can initiate a game state manually using ``

### Running library tests

You can run the library tests by running `tests.jl`. Not every single functionality of the library is tested currently in these tests, only the library-only functions of the `/src/` folder. If something does not seem to work, post an issue. In the future there will be a full Julia module.

## To do
### v1.0.1 of emulator
(Ship library before this)
- Change paradigm so that you can just call the exe once and loop over the turns. Will need loading, new game and saving game. 
- File names will need a bigger buffer probably, and fixed max length.