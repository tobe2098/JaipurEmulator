# JaipurEmulator
Emulates the game (by default the screen is cleared after every action is run, so that the other player does not see your hand).
## Installation
- Run `make` or `mingw32-make` in the root folder of the repository.


## Rules of the game Jaipur

1. The game starts with three camels and two other cards in the market.

2. On your turn, you can either trade with the market or sell goods in your hand.  
   - **Trade**:  
     - Cards from hand and from the camel herd (your camels) can be traded with the market's goods cards.  
     - Take a single goods card from the market. The market draws a card from the deck.  
     - Take all the camels. The market draws as many cards from the deck.  
   - **Sell**:  
     - Sell a non-zero number of cards from your hand. Receive points depending on the highest-value tokens remaining.  
     - If you sell 3 or more cards, you receive a random bonus token according to that number (if any remain).  

   *Bonus tokens details:*  
   - Selling 3 cards gives a bonus of **1, 2, or 3 points**.  
   - Selling 4 cards gives a bonus of **4, 5, or 6 points**.  
   - Selling 5 cards gives a bonus of **7, 8, or 9 points**.  

3. The game ends when:  
   - There are no cards left in the draw pile when attempting to draw.  
   - The tokens for three goods are finished. 

### Footnotes

- Goods cards are non-camel cards.  
- A player cannot have more than 7 goods cards in hand.  
- Each player starts with five cards. The face-down deck starts with 40 cards.  

# Use instructions
## CLI executable
Only accepts one action per call.
- The windows executable assumes that msys2 is installed. More concretely, it assumes that reset.exe (from Unix) is found in the PATH. If it is not, it might not be possible to run the executable.

```bash
./program [options]
```

### Options

- `--help` or `-h`  
  Show this help message.

- `--version` or `-v`  
  Show the version of the executable.

- `--rules` or `-u`  
  Show the game's rules.

- `--reset` or `-r`  
  Restart the game from scratch.

- `--take` or `-t <market-card>`  
  Example: `-t g`  
  Take a card from the market. The market draws a card from the deck. Camels are not allowed.

- `--camels` or `-c`  
  Example: `-c 3`  
  Take all camels from the market. The market draws as many cards.

- `--sell <card-type> <value>`  
  Example: `--sell d 3`  
  Sell a number of goods of the specified type. Earn points from them.

- `--exchange` or `-e <hand-cards> <camels> <market-cards>`  
  Example: `-e dg 1 ppp`  
  Change cards in hand and camels for cards in the market. The numbers must match.

### Card types and their characters

- Diamonds: `d`  
- Golds: `g`  
- Silvers: `s`  
- Spice: `p`  
- Cloth: `h`  
- Leather: `l`  
- Camels: `c`

## Julia

### Using the library
To see how to use the Julia library, see `example.jl`. There are a series of functions to:

1. Create, duplicate and clone games (includes allocation).
2. Perform game actions.
3. Check if the round or game is over and check which player won, and give the proper seal to the winning player. Also, functions to reset the round or game.
4. As above but done automatically using the flag system.
5. Free the allocated games.

If the player tries an action that is not possible at the moment, if the data is somehow invalidated or more, there are multiple options in how to deal with it. The `process_game_action` function takes a boolean to automatically print errors, and the function itself returns an `Int32`, of which each set bit has a meaning, which can also be printed in the Julia function `flag_identifiers` or `flag_set_bit_spositions`.

Because of how the seed is used only in initialization or data read, and the library does not do the data reads (only the executable does it), you can initiate a game state manually using `duplicate_game_data`. You only need to set the cards in hand, market and the sold cards (in form of tokens). The library will not check if the points add up, but it will check that everything you put makes sense in terms of cards and tokens. You only need to fill the fields marked with `#State` in `jaipur.jl`. This has not been fully tested as of yet.


### Running library tests

You can run the library tests by running `tests.jl`. Not every single functionality of the library is tested currently in these tests, only the library-only functions of the `/src/` folder. If something does not seem to work, post an issue. In the future there will be a full Julia module.

## To do
### v1.0.1 of emulator
(Ship library before this)
- Change paradigm so that you can just call the exe once and loop over the turns. Will need loading, new game and saving game. 
- File names will need a bigger buffer probably, and fixed max length.

### v2.0.0: GUI
- The title says it.