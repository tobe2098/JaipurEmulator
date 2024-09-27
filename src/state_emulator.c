#include "state_emulator.h"

int main(int argc, char *argv[]) {
  if (argc == 2 && strncmp(argv[1], "--help", 6) == 0) {
    print_help();
    return 0;
  } else if (argc == 2 && strncmp(argv[1], "--version", 9) == 0) {
    print_version();
    return 0;
  }

  PlayerScore playerA, playerB;
  GameData   game;
  game.was_initialized = 0;
  // Load the previous game state from the JSON file
  if (load_game_state(&playerA, &playerB, &game) == -1) {
    return -1;
  }
  // Process command-line arguments (e.g., "take_camel", "sell_goods", "draw_from_deck")
  process_arguments(&playerA, &playerB, &game, argc, argv);

  // Save the updated state back to the JSON file
  save_game_state(&playerA, &playerB, &game);

  return 0;
}