#include "game_data.h"
void set_seed(gameData *game) {
  srand(game->seed);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens_state.bonus_3_arr[i] = i;
  }
  randomize_index_array(game->tokens_state.bonus_3_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens_state.bonus_4_arr[i] = i;
  }
  randomize_index_array(game->tokens_state.bonus_4_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens_state.bonus_5_arr[i] = i;
  }
  randomize_index_array(game->tokens_state.bonus_5_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < DECK_SIZE; i++) {
    game->deck[i] = i;
  }
  randomize_index_array(game->deck,DECK_SIZE);
}
void initialize_gameData(gameData *game){
  if (game->was_initialized==1) return;
  card_group template={0,0,0,0,0,0,0};
  game->hand_plA=template;
  game->hand_plB=template;
  game->market=template;
  game->market.camels=3;
  player_score template2={0,0,0,0};
  game->playerA=template2;
  game->playerB=template2;
  game->seed=(unsigned int)time(NULL);
  set_seed(game);
  game->tokens_state.diamond_ptr = 0;
  game->tokens_state.gold_ptr = 0;
  game->tokens_state.silver_ptr = 0;
  game->tokens_state.spice_ptr = 0;
  game->tokens_state.cloth_ptr = 0;
  game->tokens_state.leather_ptr = 0;
  game->tokens_state.bonus_3_ptr = 0;
  game->tokens_state.bonus_4_ptr = 0;
  game->tokens_state.bonus_5_ptr = 0;
  game->tokens_state.finished_counter = 0;
  game->deck_ptr=0;

}
void initialize_game(gameData *game) {
  // Optionally set the random seed in the system
  print_welcome_message();
  playerA->no_bonus_tokens = 0;
  playerA->no_goods_tokens = 0;
  playerA->camels          = 0;
  playerA->points          = 0;
  playerA->seals           = 0;

  playerB->no_bonus_tokens = 0;
  playerB->no_goods_tokens = 0;
  playerB->camels          = 0;
  playerB->points          = 0;
  playerB->seals           = 0;

  game->diamond_ptr = 0;
  game->gold_ptr    = 0;
  game->silver_ptr  = 0;
  game->spice_ptr   = 0;
  game->cloth_ptr   = 0;
  game->leather_ptr = 0;
  game->tokens_state.bonus_3_ptr = 0;
  game->tokens_state.bonus_4_ptr = 0;
  game->tokens_state.bonus_5_ptr = 0;

  printf("<Seed> Enter a random seed for the next round: ");

  char input[20];
  if (fgets(input, sizeof(input), stdin) != NULL) {
    if (input[0] == '\n') {
      game->seed = 42;  // Default seed
    } else {
      char *endptr;
      game->seed = (int)(strtol(input, &endptr, 10) & INT_MAX);
      // printf("The following input was ignored: %s\n", endptr);
    }
    printf("<Seed> Seed set to: %i\n", game->seed);
  } else {
    game->seed = 42;  // Default seed if no input
  }
  set_seed(game);
  game->turn_of = 'A' + (rand() & 1);
  printf("<Turn> Player %c starts this round <Turn>\n", game->turn_of);
}

void initialize_round(gameData *game)
{
    initialize_gameData(game);

    printf("<Seed> Enter a random seed for the next round: ");

    char input[20];
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        if (input[0] == '\n')
        {
            game->seed = 42; // Default seed
        }
        else
        {
            char *endptr;
            game->seed = (int)(strtol(input, &endptr, 10) & INT_MAX);
            // printf("The following input was ignored: %s\n", endptr);
        }
        printf("<Seed> Seed set to: %i\n", game->seed);
    } else {
    game->seed = 42;  // Default seed if no input
  }
  set_seed(game);
  printf("<Turn> Player %c starts this round <Turn>\n", (game->turn_of));
}
void print_game_state(gameData *game) {
  printf("\n");
  printf("<Scores>\n");
  printf("<Player A> Points:%i, Camels:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", playerA->points, playerA->camels,
         playerA->seals, playerA->no_bonus_tokens, playerA->no_goods_tokens);
  printf("<Player B> Points:%i, Camels:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", playerB->points, playerB->camels,
         playerB->seals, playerB->no_bonus_tokens, playerB->no_goods_tokens);
  printf("\n");
  print_array_goods("diamonds", diamond_tokens, diamond_t_size, game->diamond_ptr);
  print_array_goods("gold", gold_tokens, gold_t_size, game->gold_ptr);
  print_array_goods("silver", silver_tokens, silver_t_size, game->silver_ptr);
  print_array_goods("spice", spice_tokens, spice_t_size, game->spice_ptr);
  print_array_goods("cloth", cloth_tokens, cloth_t_size, game->cloth_ptr);
  print_array_goods("leather", leather_tokens, leather_t_size, game->leather_ptr);
  printf("\n");
  printf("<Bonus> Remaining 3 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS - game->tokens_state.bonus_3_ptr);
  printf("<Bonus> Remaining 4 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS - game->tokens_state.bonus_4_ptr);
  printf("<Bonus> Remaining 5 card bonus tokens: \t%i\n", MAX_BONUS_TOKENS - game->tokens_state.bonus_5_ptr);
  printf("\n");
  printf("<Round> Finished goods token piles: \t%i \n", game->finished_counter);
  printf("\n");
  printf("<Turn> It is player %c's turn now <Turn>\n", game->turn_of);
  printf("\n");
}
int check_data_integrity(gameData *game) {
  if (playerA->camels + playerB->camels > camels_total || playerA->camels < 0 || playerB->camels < 0) {
    return -1;
  }
  if (game->tokens_state.bonus_3_ptr > MAX_BONUS_TOKENS || game->tokens_state.bonus_3_ptr < 0 || game->tokens_state.bonus_4_ptr > MAX_BONUS_TOKENS || game->tokens_state.bonus_5_ptr < 0 ||
      game->tokens_state.bonus_5_ptr > MAX_BONUS_TOKENS || game->tokens_state.bonus_5_ptr < 0) {
    return -1;
  }
  if (game->cloth_ptr > cloth_t_size || game->cloth_ptr < 0 || game->spice_ptr > spice_t_size || game->spice_ptr < 0 ||
      game->leather_ptr > leather_t_size || game->leather_ptr < 0 || game->silver_ptr > silver_t_size || game->silver_ptr < 0 ||
      game->gold_ptr > gold_t_size || game->gold_ptr < 0 || game->diamond_ptr > diamond_t_size || game->diamond_ptr < 0) {
    return -1;
  }
  if ((game->turn_of != 'A' && game->turn_of != 'B')) {
    return -1;
  }
  if (game->finished_counter > finished_goods_limit || game->finished_counter < 0) {
    return -1;
  }
  return 0;
}
void set_finished_resources(gameData *game) {
  game->finished_counter = 0;
  if (game->leather_ptr == leather_t_size) {
    game->finished_counter++;
  }
  if (game->cloth_ptr == cloth_t_size) {
    game->finished_counter++;
  }
  if (game->spice_ptr == spice_t_size) {
    game->finished_counter++;
  }
  if (game->silver_ptr == silver_t_size) {
    game->finished_counter++;
  }
  if (game->gold_ptr == gold_t_size) {
    game->finished_counter++;
  }
  if (game->diamond_ptr == diamond_t_size) {
    game->finished_counter++;
  }
}
int load_game_state(gameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "r");

  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    int counted_size=fread(buffer, 1, file_size, file);
    if(counted_size!=file_size){
      free(buffer);
      return -1;
    }
    buffer[file_size] = '\0';
    fclose(file);
    // printf("Buffer 1 content:\n%s\n", buffer);
    // Parse the JSON-like ure
    int itemsRead = sscanf(buffer,
                           "{\n"
                           "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n"
                           "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n"
                           "  \"turn_of\": \"%c\",\n"
                           "  \"diamond_ptr\": %i,\n"
                           "  \"gold_ptr\": %i,\n"
                           "  \"silver_ptr\": %i,\n"
                           "  \"spice_ptr\": %i,\n"
                           "  \"cloth_ptr\": %i,\n"
                           "  \"leather_ptr\": %i,\n"
                           "  \"seed\": %i,\n"
                           "  \"bonus_3_ptr\": %i,\n"
                           "  \"bonus_4_ptr\": %i,\n"
                           "  \"bonus_5_ptr\": %i\n"
                           "}\n",
                           &(playerA->no_bonus_tokens), &playerA->no_goods_tokens, &playerA->camels, &playerA->points, &playerA->seals,
                           &playerB->no_bonus_tokens, &playerB->no_goods_tokens, &playerB->camels, &playerB->points, &playerB->seals,
                           &game->turn_of, &game->diamond_ptr, &game->gold_ptr, &game->silver_ptr, &game->spice_ptr, &game->cloth_ptr,
                           &game->leather_ptr, &game->seed, &game->tokens_state.bonus_3_ptr, &game->tokens_state.bonus_4_ptr, &game->tokens_state.bonus_5_ptr);
    // printf("Items read: %d\n", itemsRead);
    free(buffer);
    set_seed(game);
    if (is_round_over(game)) {
      round_over(playerA, playerB, game);
      if (is_game_over(playerA, playerB)) {
        game_over(playerA, playerB);
        initialize_game(playerA, playerB, game);
        game->was_initialized = 1;
      } else {
        initialize_round(playerA, playerB, game);
      }
    }
    if (is_game_over(playerA, playerB)) {
      game_over(playerA, playerB);
      initialize_game(playerA, playerB, game);
      game->was_initialized = 1;
    }
    if (itemsRead < 21) {
      printf("Data was partially corrupted, use `--reset` to restart the game or manually correct the json.\n");
      printf("Input into the template json file your data manually as an alternative.\n");
      return -1;
    }
  } else {
    // Initialize default game state if no save file exists
    initialize_game(playerA, playerB, game);
    game->was_initialized = 1;
  }
  set_finished_resources(game);
  if (check_data_integrity(playerA, playerB, game) == -1) {
    return -1;
  } else {
    return 0;
  }
}
void save_game_state(const player_score *playerA, const player_score *playerB, const gameData *game) {
  char save_file[MAX_PATH];
  find_data_path(save_file);
  FILE *file = fopen(save_file, "w");
  if (file == NULL) {
    perror("Unable to save game state");
    return;
  }

  // Write the JSON-like format for the game state
  fprintf(file, "{\n");
  fprintf(file, "  \"playerA\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n",
          playerA->no_bonus_tokens, playerA->no_goods_tokens, playerA->camels, playerA->points, playerA->seals);
  fprintf(file, "  \"playerB\": {\"bonus tokens\": %i,\"goods tokens\": %i, \"camels\": %i, \"points\": %i, \"seals\": %i},\n",
          playerB->no_bonus_tokens, playerB->no_goods_tokens, playerB->camels, playerB->points, playerB->seals);
  fprintf(file, "  \"turn_of\": \"%c\",\n", game->turn_of);
  fprintf(file, "  \"diamond_ptr\": %i,\n", game->diamond_ptr);
  fprintf(file, "  \"gold_ptr\": %i,\n", game->gold_ptr);
  fprintf(file, "  \"silver_ptr\": %i,\n", game->silver_ptr);
  fprintf(file, "  \"spice_ptr\": %i,\n", game->spice_ptr);
  fprintf(file, "  \"cloth_ptr\": %i,\n", game->cloth_ptr);
  fprintf(file, "  \"leather_ptr\": %i,\n", game->leather_ptr);
  fprintf(file, "  \"seed\": %i,\n", game->seed);
  fprintf(file, "  \"bonus_3_ptr\": %i,\n", game->tokens_state.bonus_3_ptr);
  fprintf(file, "  \"bonus_4_ptr\": %i,\n", game->tokens_state.bonus_4_ptr);
  fprintf(file, "  \"bonus_5_ptr\": %i\n", game->tokens_state.bonus_5_ptr);
  fprintf(file, "}\n");

  fclose(file);
}
void print_help() {
  printf("Usage: ./program [options]\n");
  printf("Options:\n");
  printf("  --help                        Show this help message\n");
  printf("  --reset                       Restart the game\n");
  printf("  --round                       End the current round due to the draw pile running out.\n");
  printf("  --state                       Print the current state of the game. Default argument.\n");
  printf("  --market                      Take a non-camel market action, passing the turn\n");
  printf("  --camels <value>              Add a positive or negative number of camels to your herd\n");
  printf("                                Example: --camels 3\n");
  printf("  --sell <type> <value>         Sell a number of goods of the specified type\n");
  printf("                                Example: --sell diamonds 3\n");
  printf("Notes on rules:\n");
  printf("1. The game ends when there are no cards left in the draw pile or the tokens of three resources are finished\n");
  printf("2. Cards from hand and from the herd can be traded with the market\n");
}
void process_arguments(gameData *game, int argc, char *argv[]) {
  if (argc < 2) {
    // printf("Addresses A:%p B:%p\n", (void *)playerA, (void *)playerB);
    print_game_state(playerA, playerB, game);
    return;
  }
  int          turn_happened   = 0;
  int          round_over_bool = 0;
  player_score *curr_player;
  if (game->turn_of == 'A') {
    curr_player = playerA;
  } else if (game->turn_of == 'B') {
    curr_player = playerB;
  } else {
    printf("Data is corrupted: player %c\n", game->turn_of);
    if (game->was_initialized == 0) {
      initialize_game(playerA, playerB, game);
      game->was_initialized = 1;
    }
    return;
  }
  // printf("Addresses A:%p B:%p, current:%p\n", (void *)playerA, (void *)playerB, (void *)curr_player);

  if (strncmp(argv[1], "--camels", 8) == 0) {
    if (argc < 3) {
      printf("Lacking a number of camels.\n");
      return;
    }
    int camels = atoi(argv[2]);
    if (camels * -1 > curr_player->camels || (playerA->camels + playerB->camels + camels > 11)) {
      printf("Invalid number of camels.\n");
      return;
    }
    curr_player->camels += camels;
    turn_happened += 1;
  } else if (strncmp(argv[1], "--sell", 6) == 0) {
    if (argc < 4) {
      printf("Too few arguments.\n");
      return;
    }
    char *goods    = argv[2];
    int   no_goods = atoi(argv[3]);
    card_sale(curr_player, game, goods, no_goods);
    turn_happened += 1;
  } else if (strncmp(argv[1], "--market", 8) == 0) {
    turn_happened += 1;
  } else if (strncmp(argv[1], "--state", 7) == 0) {
    print_game_state(playerA, playerB, game);
  } else if (strncmp(argv[1], "--reset", 7) == 0 && game->was_initialized == 0) {
    initialize_game(playerA, playerB, game);
    game->was_initialized = 1;
  } else if (strncmp(argv[1], "--round", 7) == 0) {
    round_over_bool = 1;
  } else if (strncmp(argv[1], "--help", 6) == 0) {
    print_help();
  } else {
    printf("Unknown command: %s\n", argv[1]);
  }
  if (turn_happened) {
    game->turn_of = (((game->turn_of - 'A') + 1) & 1) + 'A';
  }
  if (round_over_bool || is_round_over(game)) {
    round_over(playerA, playerB, game);
    initialize_round(playerA, playerB, game);
  } else {
    print_game_state(playerA, playerB, game);
  }
  if (is_game_over(playerA, playerB)) {
    game_over(playerA, playerB);
    initialize_game(playerA, playerB, game);
    game->was_initialized = 1;
  }
}

void card_sale(player_score *player, gameData *game, char card_type[], int no_cards) {
  if (strncmp(card_type, "diamonds", 8) == 0) {
    int end = min(no_cards + game->diamond_ptr, diamond_t_size);
    for (int i = game->diamond_ptr; i < end; i++) {
      player->points += diamond_tokens[i];
    }
    player->no_goods_tokens += end - game->diamond_ptr;
    game->diamond_ptr = end;
  } else if (strncmp(card_type, "gold", 4) == 0) {
    int end = min(no_cards + game->gold_ptr, gold_t_size);
    for (int i = game->gold_ptr; i < end; i++) {
      player->points += gold_tokens[i];
    }
    player->no_goods_tokens += end - game->gold_ptr;
    game->gold_ptr = end;
  } else if (strncmp(card_type, "silver", 6) == 0) {
    int end = min(no_cards + game->silver_ptr, silver_t_size);
    for (int i = game->silver_ptr; i < end; i++) {
      player->points += silver_tokens[i];
    }
    player->no_goods_tokens += end - game->silver_ptr;
    game->silver_ptr = end;
  } else if (strncmp(card_type, "spice", 5) == 0) {
    int end = min(no_cards + game->spice_ptr, spice_t_size);
    for (int i = game->spice_ptr; i < end; i++) {
      player->points += spice_tokens[i];
    }
    player->no_goods_tokens += end - game->spice_ptr;
    game->spice_ptr = end;
  } else if (strncmp(card_type, "cloth", 5) == 0) {
    int end = min(no_cards + game->cloth_ptr, cloth_t_size);
    for (int i = game->cloth_ptr; i < end; i++) {
      player->points += cloth_tokens[i];
    }
    player->no_goods_tokens += end - game->cloth_ptr;
    game->cloth_ptr = end;
  } else if (strncmp(card_type, "leather", 7) == 0) {
    int end = min(no_cards + game->leather_ptr, leather_t_size);
    for (int i = game->leather_ptr; i < end; i++) {
      player->points += leather_tokens[i];
    }
    player->no_goods_tokens += end - game->leather_ptr;
    game->leather_ptr = end;
  }
  if (no_cards == 3 && game->tokens_state.bonus_3_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens_state.bonus_3_arr[game->tokens_state.bonus_3_ptr];
    game->tokens_state.bonus_3_ptr++;
  } else if (no_cards == 4 && game->tokens_state.bonus_4_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens_state.bonus_4_arr[game->tokens_state.bonus_4_ptr];
    game->tokens_state.bonus_4_ptr++;
  } else if (no_cards >= 5 && game->tokens_state.bonus_5_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens_state.bonus_5_arr[game->tokens_state.bonus_5_ptr];
    game->tokens_state.bonus_5_ptr++;
  }
}

int is_game_over(player_score *playerA, player_score *playerB) {
  if (playerA->seals == winning_seals || playerB->seals == winning_seals) {
    return 1;
  } else {
    return 0;
  }
}

int is_round_over(gameData *game) {
  set_finished_resources(game);
  if (game->finished_counter == finished_goods_limit) {
    return 1;
  } else {
    return 0;
  }
}

void game_over(player_score *playerA, player_score *playerB) {
  if (playerA->seals == winning_seals) {
    print_winning_trophy('A');
  } else if (playerB->seals == winning_seals) {
    print_winning_trophy('B');
  }
}

void round_over(gameData *game) {
  if (playerA->camels > playerB->camels) {
    playerA->points += camel_token;
  } else if (playerB->camels > playerA->camels) {
    playerB->camels += camel_token;
  }
  if (playerA->points > playerB->points) {
    playerA->seals++;
    game->turn_of = 'B';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('A');
    }
    return;
  } else if (playerA->points < playerB->points) {
    playerB->seals++;
    game->turn_of = 'A';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('B');
    }
    return;
  }
  if (playerA->no_bonus_tokens > playerB->no_bonus_tokens) {
    playerA->seals++;
    game->turn_of = 'B';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('A');
    }
    return;
  } else if (playerA->no_bonus_tokens < playerB->no_bonus_tokens) {
    playerB->seals++;
    game->turn_of = 'A';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('B');
    }
    return;
  }
  if (playerA->no_goods_tokens > playerB->no_goods_tokens) {
    playerA->seals++;
    game->turn_of = 'B';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('A');
    }
    return;
  } else if (playerA->no_goods_tokens < playerB->no_goods_tokens) {
    playerB->seals++;
    game->turn_of = 'A';
    if (is_game_over(playerA, playerB) == 0) {
      print_new_round_message('B');
    }
    return;
  }
  printf("ERROR: IT WAS A DRAW! CONGRATULATIONS! THIS IS NORMALLY IMPOSSIBLE\n");
}
