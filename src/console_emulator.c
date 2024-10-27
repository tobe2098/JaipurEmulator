#include "console_emulator.h"
void roundOverPrint(GameData *game) {
  print_new_round_message(((game->turn_of + 1) & 1));
}
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN) {
    printWinningTrophy(PLAYER_A_NUM);
  } else if (playerB->seals == SEALS_TO_WIN) {
    printWinningTrophy(PLAYER_B_NUM);
  }
}
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
    printf("Items read: %d\n", itemsRead);
    free(buffer);

    if (itemsRead < JSON_ELEMENTS) {
      gameStatePrint(game);
      printf("Only %i elements were read. Knowing the state of the game, would you like to continue like this?[y/n]", itemsRead);
      char ans = 0;
      while (ans != 'y' || ans != 'Y' || ans != 'n' || ans != 'N') {
        printf("Would you like to continue like this?[y/n]");
        ans = getchar();
      }
      if (ans == 'n') {
        return DATA_CORRUPTED_FLAG;
      }
    }
  } else {
    // Initialize default game state if no save file exists
    return DATA_NOT_INIT_FLAG;
  }
  setSeed(game);
  return checkDataIntegrity(game);
}
void save_game_data(const GameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "w");
  if (file == NULL) {
    perror("Unable to save game state: ");
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

int endingChecks(GameData *game) {
  if (isRoundOver(&game)) {
    if (compRoundWinningPlayer(&game) & DRAW_FLAG) {
      return DRAW_FLAG | ROUND_OVER;
    }
    if (isGameOver(&(game->playerA), &(game->playerB))) {
      gameOverPrint(&(game->playerA), &(game->playerB));
      return GAME_OVER;
    } else {
      roundOverPrint(game);
      return ROUND_OVER;
    }
    // } else {
    // if (isGameOver(&(game->playerA), &(game->playerB))) {
    //   gameOverPrint(&(game->playerA), &(game->playerB));
    //   return GAME_OVER;
    // }
    // gameStatePrint(game);
  }
  return 0;
}

int *getActivePlayerHand(GameData *game) {
  if (game->turn_of == PLAYER_A_NUM) {
    return game->hand_plA;
  } else {
    return game->hand_plB;
  }
}

void gameStatePrint(GameData *game) {
  printf("\n");
  printf("<Scores>\n");
  printf("<%s> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", PLAYER_A, game->playerA.points, game->playerA.seals,
         game->playerA.no_bonus_tokens, game->playerA.no_goods_tokens);
  printf("<%s> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", PLAYER_B, game->playerB.points, game->playerB.seals,
         game->playerB.no_bonus_tokens, game->playerB.no_goods_tokens);
  printf("\n");
  for (int card_index = 0; card_index < RESOURCE_TYPES; card_index++) {
    printGoodsTokenArray(enum_to_char_lookup_table[card_index], resource_tokens[card_index].tokens, resource_tokens[card_index].size,
                         game->resource_tk_ptrs[card_index]);
  }
  // printGoodsTokenArray("diamonds", diamond_tokens, DIAMOND_T_SIZE, game->diamond_ptr);
  // printGoodsTokenArray("gold", gold_tokens, GOLD_T_SIZE, game->gold_ptr);
  // printGoodsTokenArray("silver", silver_tokens, SILVER_T_SIZE, game->silver_ptr);
  // printGoodsTokenArray("spice", spice_tokens, SPICE_T_SIZE, game->spice_ptr);
  // printGoodsTokenArray("cloth", cloth_tokens, CLOTH_T_SIZE, game->cloth_ptr);
  // printGoodsTokenArray("leather", leather_tokens, LEATHER_T_SIZE, game->leather_ptr);
  // printf("\n");
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    printf("<Bonus> Remaining %i card bonus tokens: \t%i\n", barr + 3, MAX_BONUS_TOKENS - game->bonus_tk_ptrs[barr]);
  }
  // printf("<Bonus> Remaining 3 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS - game->bonus_tk_ptrs);
  // printf("<Bonus> Remaining 4 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_4_ptr);
  // printf("<Bonus> Remaining 5 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_5_ptr);
  // Print market
  printCardGroup(game->market, TRUE);
  while (getchar() != '\n');
  printCardGroup(getActivePlayerHand(game), FALSE);
  // Print hand of new player after enter
  printf("\n");
  printf("<Turn> It is %s's turn now <Turn>\n", getPlayerName(game->turn_of));
  printf("\n");
  // INTRODUCE KEY PRESS FOR HAND SECRECY, maybe a console clearing before state
}
int main(int argc, char *argv[]) {
  if (argc == 2 && (strncmp(argv[1], "--help", strlen("--help")) || strncmp(argv[1], "-h", strlen("-h"))) == 0) {
    print_help();
    return 0;
  } else if (argc == 2 && (strncmp(argv[1], "--version", strlen("--version")) || strncmp(argv[1], "-v", strlen("-v"))) == 0) {
    printVersion();
    return 0;
  }

  GameData game;
  game.was_initialized = 0;

  int flags = 0;
  // Load the previous game state from the JSON file
  flags |= load_game_data(&game);
  // Process command-line arguments (e.g., "take_camel", "sell_goods", "draw_from_deck")
  if (flags & DATA_OKAY_FLAG) {
    // computeFinishedResources(&game);
    flags |= endingChecks(&game);
    if (!(flags & GAME_OVER || flags & ROUND_OVER)) {
      flags |= processAction(&game, argc, argv, flags);
    }
    if (flags & TURN_HAPPENED_FLAG) {
      game.turn_of = (game.turn_of + 1) & 1;
      flags |= endingChecks(&game);
    }
    if (flags & GAME_OVER) {
      printf("Press Enter to start a new game:\n");
      while (getchar() != '\n');
      startGame(&game, 0);
    } else if (flags & ROUND_OVER) {
      printf("Press Enter to start the next round:\n");
      while (getchar() != '\n');
      startRound(&game);
    }
  }
  if (!(flags & NO_GAME_PRINT_FLAG)) {
    gameStatePrint(&game);
  }
  // All prints have to be handed here, in console
  // Save the updated state back to the JSON file
  save_game_data(&game);
  (void)printErrors(flags);
  return 0;
}
