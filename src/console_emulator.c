#include "console_emulator.h"
void roundOverPrint(GameData *game) {
  printNewRoundMessage(((game->turn_of + 1) & 1));
}
void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN) {
    printWinningTrophy(PLAYER_A_NUM);
  } else if (playerB->seals == SEALS_TO_WIN) {
    printWinningTrophy(PLAYER_B_NUM);
  }
}
int loadGameData(GameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "rb");

  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer       = (char *)malloc(file_size + 1);
    int   counted_size = fread(buffer, 1, file_size, file);
    if (counted_size != file_size) {
      free(buffer);
      return DATA_CORRUPTED_FLAG;
    }
    buffer[file_size] = '\0';
    fclose(file);
    // int itemsRead = 0;

    // printf("Buffer 1 content:\n%s\n", buffer);
    // Parse the JSON-like ure
    int itemsRead =
      sscanf(buffer,
             "{\n"
             "  \"init\": %i,\n"
             "  \"seed\": %i,\n"
             "  \"turn_of\": \"%i\",\n"
             "  \"market\": [%i,%i,%i,%i,%i,%i,%i],\n"
             "  \"hand_plA\": [%i,%i,%i,%i,%i,%i,%i],\n"
             "  \"hand_plB\": [%i,%i,%i,%i,%i,%i,%i],\n"
             "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n"
             "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n"
             "  \"good_tk_ptrs\": [%i,%i,%i,%i,%i,%i],\n"
             "  \"bonus_tk_ptrs\": [%i,%i,%i],\n"
             "  \"deck_ptr\": %i\n"
             "}\n",
             &(game->was_initialized), &(game->seed), &(game->turn_of), &(game->market[diamonds]), &(game->market[golds]),
             &(game->market[silvers]), &(game->market[spices]), &(game->market[cloths]), &(game->market[leathers]), &(game->market[camels]),
             &(game->hand_plA[diamonds]), &(game->hand_plA[golds]), &(game->hand_plA[silvers]), &(game->hand_plA[spices]),
             &(game->hand_plA[cloths]), &(game->hand_plA[leathers]), &(game->hand_plA[camels]), &(game->hand_plB[diamonds]),
             &(game->hand_plB[golds]), &(game->hand_plB[silvers]), &(game->hand_plB[spices]), &(game->hand_plB[cloths]),
             &(game->hand_plB[leathers]), &(game->hand_plB[camels]), &(game->playerA.no_bonus_tokens), &(game->playerA.no_goods_tokens),
             &(game->playerA.points), &(game->playerA.seals), &(game->playerB.no_bonus_tokens), &(game->playerB.no_goods_tokens),
             &(game->playerB.points), &(game->playerB.seals), &(game->good_tk_ptrs[diamonds]), &(game->good_tk_ptrs[golds]),
             &(game->good_tk_ptrs[silvers]), &(game->good_tk_ptrs[spices]), &(game->good_tk_ptrs[cloths]), &(game->good_tk_ptrs[leathers]),
             &(game->bonus_tk_ptrs[0]), &(game->bonus_tk_ptrs[1]), &(game->bonus_tk_ptrs[2]), &(game->deck_ptr));
    printf("Items read: %d\n", itemsRead);
    free(buffer);

    if (itemsRead < JSON_ELEMENTS) {
      dataPrint(game);  // Do something better here
      printf("Only %i elements were read. Seeing the degree of data loss, would you like to continue like this?[y/n]", itemsRead);
      char ans = 0;
      while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
        printf("Would you like to continue like this?[y/n]");
        ans = getchar();
      }
      if (ans == 'n' || ans == 'N') {
        return DATA_CORRUPTED_FLAG;
      } else {
        return 0;
      }
    } else {
      setSeed(game);
    }
  } else {
    // Initialize default game state if no save file exists
    return DATA_NOT_INIT_FLAG;
  }
  return checkDataIntegrity(game);
}
void saveGameData(const GameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "wb");
  if (file == NULL) {
    perror("Unable to save game state: ");
    return;
  }

  // Write the JSON-like format for the game state
  fprintf(file, "{\n");
  fprintf(file, "  \"init\": %i,\n", game->was_initialized);
  fprintf(file, "  \"seed\": %i,\n", game->seed);
  fprintf(file, "  \"turn_of\": \"%i\",\n", game->turn_of);

  fprintf(file, "  \"market\": [%i,%i,%i,%i,%i,%i,%i],\n", game->market[diamonds], game->market[golds], game->market[silvers],
          game->market[spices], game->market[cloths], game->market[leathers], game->market[camels]);
  fprintf(file, "  \"hand_plA\": [%i,%i,%i,%i,%i,%i,%i],\n", game->hand_plA[diamonds], game->hand_plA[golds], game->hand_plA[silvers],
          game->hand_plA[spices], game->hand_plA[cloths], game->hand_plA[leathers], game->hand_plA[camels]);
  fprintf(file, "  \"hand_plB\": [%i,%i,%i,%i,%i,%i,%i],\n", game->hand_plB[diamonds], game->hand_plB[golds], game->hand_plB[silvers],
          game->hand_plB[spices], game->hand_plB[cloths], game->hand_plB[leathers], game->hand_plB[camels]);
  fprintf(file, "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n",
          game->playerA.no_bonus_tokens, game->playerA.no_goods_tokens, game->playerA.points, game->playerA.seals);
  fprintf(file, "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n",
          game->playerB.no_bonus_tokens, game->playerB.no_goods_tokens, game->playerB.points, game->playerB.seals);
  fprintf(file, "  \"good_tk_ptrs\": [%i,%i,%i,%i,%i,%i],\n", game->good_tk_ptrs[diamonds], game->good_tk_ptrs[golds],
          game->good_tk_ptrs[silvers], game->good_tk_ptrs[spices], game->good_tk_ptrs[cloths], game->good_tk_ptrs[leathers]);

  fprintf(file, "  \"bonus_tk_ptrs\": [%i,%i,%i],\n", game->bonus_tk_ptrs[0], game->bonus_tk_ptrs[1], game->bonus_tk_ptrs[2]);
  fprintf(file, "  \"deck_ptr\": %i\n", game->deck_ptr);
  fprintf(file, "}\n");

  fclose(file);
}

void dataPrint(const GameData *game) {
  printf("{\n");
  printf("  \"init\": %i,\n", game->was_initialized);
  printf("  \"seed\": %i,\n", game->seed);
  printf("  \"turn_of\": \"%i\",\n", game->turn_of);

  printf("  \"market\": [%i,%i,%i,%i,%i,%i,%i],\n", game->market[diamonds], game->market[golds], game->market[silvers],
         game->market[spices], game->market[cloths], game->market[leathers], game->market[camels]);
  printf("  \"hand_plA\": [%i,%i,%i,%i,%i,%i,%i],\n", game->hand_plA[diamonds], game->hand_plA[golds], game->hand_plA[silvers],
         game->hand_plA[spices], game->hand_plA[cloths], game->hand_plA[leathers], game->hand_plA[camels]);
  printf("  \"hand_plB\": [%i,%i,%i,%i,%i,%i,%i],\n", game->hand_plB[diamonds], game->hand_plB[golds], game->hand_plB[silvers],
         game->hand_plB[spices], game->hand_plB[cloths], game->hand_plB[leathers], game->hand_plB[camels]);
  printf("  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n", game->playerA.no_bonus_tokens,
         game->playerA.no_goods_tokens, game->playerA.points, game->playerA.seals);
  printf("  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"points\": %i, \"seals\": %i},\n", game->playerB.no_bonus_tokens,
         game->playerB.no_goods_tokens, game->playerB.points, game->playerB.seals);
  printf("  \"good_tk_ptrs\": [%i,%i,%i,%i,%i,%i],\n", game->good_tk_ptrs[diamonds], game->good_tk_ptrs[golds], game->good_tk_ptrs[silvers],
         game->good_tk_ptrs[spices], game->good_tk_ptrs[cloths], game->good_tk_ptrs[leathers]);

  printf("  \"bonus_tk_ptrs\": [%i,%i,%i],\n", game->bonus_tk_ptrs[0], game->bonus_tk_ptrs[1], game->bonus_tk_ptrs[2]);
  printf("  \"deck_ptr\": %i\n", game->deck_ptr);
  printf("}\n");
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
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    printf("<Bonus> %i card bonus tokens: \t%i\n", barr + 3, MAX_BONUS_TOKENS - game->bonus_tk_ptrs[barr]);
  }
  printf("\n");
  for (int card_index = 0; card_index < GOOD_TYPES; card_index++) {
    printGoodsTokenArray(enum_to_char_lookup_table[card_index], good_tokens[card_index].tokens, good_tokens[card_index].size,
                         game->good_tk_ptrs[card_index]);
  }
  // printGoodsTokenArray("diamonds", diamond_tokens, DIAMOND_T_SIZE, game->diamond_ptr);
  // printGoodsTokenArray("gold", gold_tokens, GOLD_T_SIZE, game->gold_ptr);
  // printGoodsTokenArray("silver", silver_tokens, SILVER_T_SIZE, game->silver_ptr);
  // printGoodsTokenArray("spice", spice_tokens, SPICE_T_SIZE, game->spice_ptr);
  // printGoodsTokenArray("cloth", cloth_tokens, CLOTH_T_SIZE, game->cloth_ptr);
  // printGoodsTokenArray("leather", leather_tokens, LEATHER_T_SIZE, game->leather_ptr);
  // printf("\n");

  // printf("<Bonus> Remaining 3 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS - game->bonus_tk_ptrs);
  // printf("<Bonus> Remaining 4 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_4_ptr);
  // printf("<Bonus> Remaining 5 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS-game->bonus_5_ptr);
  // Print market
  printCardGroup(game->market, TRUE);
  // Print camel piles
  printf("\n");
  printf("<Camels> %s has: %i camels\n", PLAYER_A, game->hand_plA[camels]);
  printf("<Camels> %s has: %i camels\n", PLAYER_B, game->hand_plB[camels]);
  printf("\n");
  printf("<Turn> It is %s's turn now <Turn>\n", getPlayerName(game->turn_of));
  printf("<Action> Press Enter to see your hand...\n");
  while (getchar() != '\n');
  printCardGroup(getActivePlayerHand(game), FALSE);
  // Print hand of new player after enter

  // INTRODUCE KEY PRESS FOR HAND SECRECY, maybe a console clearing before state
}
int main(int argc, char *argv[]) {
  if (argc == 2 && (strncmp(argv[1], "--help", strlen("--help")) || strncmp(argv[1], "-h", strlen("-h"))) == 0) {
    printHelp();
    return 0;
  } else if (argc == 2 && (strncmp(argv[1], "--version", strlen("--version")) || strncmp(argv[1], "-v", strlen("-v"))) == 0) {
    printVersion();
    return 0;
  } else if (argc == 2 && (strncmp(argv[1], "--rules", strlen("--rules")) || strncmp(argv[1], "-u", strlen("-u"))) == 0) {
    print_rules();
    return 0;
  }

  GameData game = {};
  // game.was_initialized = 0;

  int flags = 0;
  // Load the previous game state from the JSON file
  flags |= loadGameData(&game);
  // Process command-line arguments (e.g., "take_camel", "sell_goods", "draw_from_deck")
  if (flags & DATA_OKAY_FLAG) {
    // computeFinishedGoods(&game);
    flags |= updateMarket(&game);
    flags |= endingChecks(&game, 0);
    if (!(flags & GAME_OVER || flags & ROUND_OVER)) {
      flags |= processAction(&game, argc, argv);
    }
    if (flags & TURN_HAPPENED_FLAG) {
      game.turn_of = (game.turn_of + 1) & 1;
      flags |= updateMarket(&game);
      flags |= endingChecks(&game, flags);
    }
    if (flags & GAME_OVER) {
      gameOverPrint(&(game.playerA), &(game.playerB));
      printf("<Action> Press Enter to start a new game...\n");
      while (getchar() != '\n');
      startGame(&game, 0);
    } else if (flags & ROUND_OVER) {
      roundOverPrint(&game);
      printf("<Action> Press Enter to start the next round:\n");
      while (getchar() != '\n');
      startRound(&game);
    }
  } else if (flags & DATA_CORRUPTED_FLAG || flags & DATA_NOT_INIT_FLAG) {
#ifdef DEBUG
    dataPrint(&game);
#endif
    while (getchar() != '\n');
    game.was_initialized = 0;
    startGame(&game, 0);
  }
  (void)printErrors(flags);
  if (!(flags & NO_GAME_PRINT_FLAG) && !(flags & ONLY_PRINT_HAND)) {
    gameStatePrint(&game);
  } else if (flags & ONLY_PRINT_HAND) {
    printf("Here is your hand again:\n");
    printCardGroup(getActivePlayerHand(&game), FALSE);
  }
  // All prints have to be handed here, in console
  // Save the updated state back to the JSON file
  saveGameData(&game);
  return 0;
}
