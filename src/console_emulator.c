#include "console_emulator.h"
int load_game_data(GameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "r");

  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer       = (char *)malloc(file_size + 1);
    int   counted_size = fread(buffer, 1, file_size, file);
    if (counted_size != file_size) {
      free(buffer);
      return -1;
    }
    buffer[file_size] = '\0';
    fclose(file);
    int itemsRead = 0;
    // printf("Buffer 1 content:\n%s\n", buffer);
    // Parse the JSON-like ure
    // int itemsRead = sscanf(buffer,
    //                        "{\n"
    //                        "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n"
    //                        "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n"
    //                        "  \"turn_of\": \"%c\",\n"
    //                        "  \"diamond_ptr\": %i,\n"
    //                        "  \"gold_ptr\": %i,\n"
    //                        "  \"silver_ptr\": %i,\n"
    //                        "  \"spice_ptr\": %i,\n"
    //                        "  \"cloth_ptr\": %i,\n"
    //                        "  \"leather_ptr\": %i,\n"
    //                        "  \"seed\": %i,\n"
    //                        "  \"bonus_tk_ptrs\": %i,\n"
    //                        "  \"bonus_4_ptr\": %i,\n"
    //                        "  \"bonus_5_ptr\": %i\n"
    //                        "}\n",
    //                        &(playerA->no_bonus_tokens), &playerA->no_goods_tokens, &playerA->camels, &playerA->points, &playerA->seals,
    //                        &playerB->no_bonus_tokens, &playerB->no_goods_tokens, &playerB->camels, &playerB->points, &playerB->seals,
    //                        &game->turn_of, &game->diamond_ptr, &game->gold_ptr, &game->silver_ptr, &game->spice_ptr, &game->cloth_ptr,
    //                        &game->leather_ptr, &game->seed, &game->bonus_tk_ptrs, &game->bonus_4_ptr, &game->bonus_5_ptr);
    // printf("Items read: %d\n", itemsRead);
    free(buffer);
    setSeed(game);
    if (isRoundOver(game)) {
      compRoundWinningPlayer(game);
      if (isGameOver(&(game->playerA), &(game->playerB))) {
        gameOverPrint(&(game->playerA), &(game->playerB));
        initGame(game);
      } else {
        initRound(game);
      }
    }
    if (isGameOver(&(game->playerA), &(game->playerB))) {
      gameOverPrint(&(game->playerA), &(game->playerB));
      initGame(game);
    }
    if (itemsRead < 21) {
      printf("Data was partially corrupted, use `--reset` to restart the game or manually correct the json.\n");
      printf("Input into the template json file your data manually as an alternative.\n");
      perror("Data could not be read:");
      return -1;
    }
  } else {
    // Initialize default game state if no save file exists
    initGame(game);
  }
  computeFinishedResources(game);
  return checkDataIntegrity(game);
}
void save_game_data(const GameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "w");
  if (file == NULL) {
    perror("Unable to save game state");
    return;
  }

  // Write the JSON-like format for the game state
  // fprintf(file, "{\n");
  // fprintf(file, "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n",
  //         playerA->no_bonus_tokens, playerA->no_goods_tokens, playerA->camels, playerA->points, playerA->seals);
  // fprintf(file, "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n",
  //         playerB->no_bonus_tokens, playerB->no_goods_tokens, playerB->camels, playerB->points, playerB->seals);
  // fprintf(file, "  \"turn_of\": \"%c\",\n", game->turn_of);
  // fprintf(file, "  \"diamond_ptr\": %i,\n", game->diamond_ptr);
  // fprintf(file, "  \"gold_ptr\": %i,\n", game->gold_ptr);
  // fprintf(file, "  \"silver_ptr\": %i,\n", game->silver_ptr);
  // fprintf(file, "  \"spice_ptr\": %i,\n", game->spice_ptr);
  // fprintf(file, "  \"cloth_ptr\": %i,\n", game->cloth_ptr);
  // fprintf(file, "  \"leather_ptr\": %i,\n", game->leather_ptr);
  // fprintf(file, "  \"seed\": %i,\n", game->seed);
  // fprintf(file, "  \"bonus_tk_ptrs\": %i,\n", game->bonus_tk_ptrs);
  // fprintf(file, "  \"bonus_4_ptr\": %i,\n", game->bonus_4_ptr);
  // fprintf(file, "  \"bonus_5_ptr\": %i\n", game->bonus_5_ptr);
  // fprintf(file, "}\n");

  fclose(file);
}
void roundOverPrint(GameData *game) {
  print_new_round_message(((game->turn_of - PLAYER_A_CHAR + 1) & 1) + PLAYER_A_CHAR);
}
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN) {
    print_winning_trophy(PLAYER_A_CHAR);
  } else if (playerB->seals == SEALS_TO_WIN) {
    print_winning_trophy(PLAYER_B_CHAR);
  }
}
void printGameState(GameData *game) {
  printf("\n");
  printf("<Scores>\n");
  printf("<Player A> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game->playerA.points, game->playerA.seals,
         game->playerA.no_bonus_tokens, game->playerA.no_goods_tokens);
  printf("<Player B> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game->playerB.points, game->playerB.seals,
         game->playerB.no_bonus_tokens, game->playerB.no_goods_tokens);
  printf("\n");
  // print_array_goods("diamonds", diamond_tokens, DIAMOND_T_SIZE, game->diamond_ptr);
  // print_array_goods("gold", gold_tokens, GOLD_T_SIZE, game->gold_ptr);
  // print_array_goods("silver", silver_tokens, SILVER_T_SIZE, game->silver_ptr);
  // print_array_goods("spice", spice_tokens, SPICE_T_SIZE, game->spice_ptr);
  // print_array_goods("cloth", cloth_tokens, CLOTH_T_SIZE, game->cloth_ptr);
  // print_array_goods("leather", leather_tokens, LEATHER_T_SIZE, game->leather_ptr);
  // printf("\n");
  // printf("<Bonus> Remaining 3 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_tk_ptrs);
  // printf("<Bonus> Remaining 4 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_4_ptr);
  // printf("<Bonus> Remaining 5 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_5_ptr);
  printf("\n");
  printf("<Turn> It is %s's turn now <Turn>\n", getPlayerName(game->turn_of));
  printf("\n");
  // INTRODUCE KEY PRESS FOR HAND SECRECY, maybe a console clearing before state
}
int main(int argc, char *argv[]) {
  if (argc == 2 && strncmp(argv[1], "--help", 6) == 0) {
    print_help();
    return 0;
  } else if (argc == 2 && strncmp(argv[1], "--version", 9) == 0) {
    print_version();
    return 0;
  }

  PlayerScore playerA, playerB;
  GameData    game;
  game.was_initialized = 0;
  // Load the previous game state from the JSON file
  if (load_game_data(&playerA, &playerB, &game) == -1) {
    return -1;
  }
  // Process command-line arguments (e.g., "take_camel", "sell_goods", "draw_from_deck")
  processAction(&playerA, &playerB, &game, argc, argv);
  if (processAction) {
    game->turn_of = (((game->turn_of - PLAYER_A_CHAR) + 1) & 1) + PLAYER_A_CHAR;
  }
  // All prints have to be handed here, in console

  if isRoundOver (game) {) {
      compRoundWinningPlayer(game);
      initRound(game);
    }
  } else {
    printGameState(game);
  }
  if (isGameOver(&(game->playerA), &(game->playerB))) {
    gameOverPrint(&(game->playerA), &(game->playerB));
    initGame(game);
  }
  // Save the updated state back to the JSON file
  save_game_data(&playerA, &playerB, &game);

  return 0;
}