#include "game_data.h"
void setSeed(GameData *game) {
  srand(game->seed);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens.bonus_3_arr[i] = i;
  }
  randomize_index_array(game->tokens.bonus_3_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens.bonus_4_arr[i] = i;
  }
  randomize_index_array(game->tokens.bonus_4_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < MAX_BONUS_TOKENS; i++) {
    game->tokens.bonus_5_arr[i] = i;
  }
  randomize_index_array(game->tokens.bonus_5_arr, MAX_BONUS_TOKENS);

  for (int i = 0; i < DECK_SIZE; i++) {
    game->deck[i] = i;
  }
  randomize_index_array(game->deck,DECK_SIZE);
}

void initCardGroup(CardGroup *group){
   group->camels=0;
   group->diamonds=0;
   group->silvers=0;
   group->golds=0;
   group->leathers=0;
   group->cloths=0;
   group->spices=0;
}

void initPlayerScore(PlayerScore *score){
  score->points=0;
  score->no_bonus_tokens=0;
  score->no_goods_tokens=0;
  score->seals=0;
}

void initGameData(GameData *game){
    if (game->was_initialized == 1)
        return;
    CardGroup template = {0, 0, 0, 0, 0, 0, 0};
    game->hand_plA = template;
    game->hand_plB = template;
    game->market = template;
    game->market.camels = 3;
    PlayerScore template2 = {0, 0, 0, 0};
    game->playerA = template2;
    game->playerB = template2;
    game->seed = (unsigned int)time(NULL);
    setSeed(game);
    game->tokens.diamond_ptr = 0;
    game->tokens.gold_ptr = 0;
    game->tokens.silver_ptr = 0;
    game->tokens.spice_ptr = 0;
    game->tokens.cloth_ptr = 0;
    game->tokens.leather_ptr = 0;
    game->tokens.bonus_3_ptr = 0;
    game->tokens.bonus_4_ptr = 0;
    game->tokens.bonus_5_ptr = 0;
    game->tokens.finished_counter = 0;
    game->deck_ptr = 0;
    game->turn_of = 'A' + (rand() & 1);
    game->was_initialized=1;
}
void resetGameData(GameData *game){
    CardGroup template = {0, 0, 0, 0, 0, 0, 0};
    game->hand_plA = template;
    game->hand_plB = template;
    game->market = template;
    game->market.camels = 3;
    game->seed = (unsigned int)time(NULL);
    setSeed(game);
    game->tokens.diamond_ptr = 0;
    game->tokens.gold_ptr = 0;
    game->tokens.silver_ptr = 0;
    game->tokens.spice_ptr = 0;
    game->tokens.cloth_ptr = 0;
    game->tokens.leather_ptr = 0;
    game->tokens.bonus_3_ptr = 0;
    game->tokens.bonus_4_ptr = 0;
    game->tokens.bonus_5_ptr = 0;
    game->tokens.finished_counter = 0;
    game->deck_ptr = 0;
}
void initializeGame(GameData *game){
    game->was_initialized=0;
    print_welcome_message();
    initGameData(game);
    printf("<Turn> Player %c starts this round <Turn>\n", game->turn_of);
}

void initializeRound(GameData *game){
    resetGameData(game);
    printf("<Turn> Player %c starts this round <Turn>\n", (game->turn_of));
}

void printGameState(GameData *game) {
  GameState game_state;
  set_GameState_from_GameData(game,&game_state);
  printf("\n");
  printf("<Scores>\n");
  printf("<Player A> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game_state.playerA.points,
         game_state.playerA.seals, game_state.playerA.no_bonus_tokens, game_state.playerA.no_goods_tokens);
  printf("<Player B> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game_state.playerB.points,
         game_state.playerB.seals, game_state.playerB.no_bonus_tokens, game_state.playerB.no_goods_tokens);
  printf("\n");
  print_array_goods("diamonds", diamond_tokens, DIAMOND_T_SIZE, game_state.remaining_tokens.diamond);
  print_array_goods("gold", gold_tokens, GOLD_T_SIZE, game_state.remaining_tokens.gold);
  print_array_goods("silver", silver_tokens, SILVER_T_SIZE, game_state.remaining_tokens.silver);
  print_array_goods("spice", spice_tokens, SPICE_T_SIZE, game_state.remaining_tokens.spice);
  print_array_goods("cloth", cloth_tokens, CLOTH_T_SIZE, game_state.remaining_tokens.cloth);
  print_array_goods("leather", leather_tokens, LEATHER_T_SIZE, game_state.remaining_tokens.leather);
  printf("\n");
  printf("<Bonus> Remaining 3 card bonus tokens: \t%i\n", game_state.remaining_tokens.bonus_3);
  printf("<Bonus> Remaining 4 card bonus tokens: \t%i\n", game_state.remaining_tokens.bonus_4);
  printf("<Bonus> Remaining 5 card bonus tokens: \t%i\n", game_state.remaining_tokens.bonus_5);
  printf("\n");
  printf("<Turn> It is player %c's turn now <Turn>\n", game_state.turn_of);
  printf("\n");
}
int checkDataIntegrity(GameData *game) {
  if (game->hand_plA.camels + game->hand_plA.camels > CAMELS_TOTAL || game->hand_plA.camels < 0 || game->hand_plA.camels < 0) {
    return -1;
  }
  if (game->tokens.bonus_3_ptr > MAX_BONUS_TOKENS || game->tokens.bonus_3_ptr < 0 || game->tokens.bonus_4_ptr > MAX_BONUS_TOKENS || game->tokens.bonus_5_ptr < 0 ||
      game->tokens.bonus_5_ptr > MAX_BONUS_TOKENS || game->tokens.bonus_5_ptr < 0) {
    return -1;
  }
  if (game->hand_plA.cloths > CLOTH_T_SIZE || game->hand_plA.cloths < 0 || game->hand_plA.spices > SPICE_T_SIZE || game->hand_plA.spices < 0 ||
      game->hand_plA.leathers > LEATHER_T_SIZE || game->hand_plA.leathers < 0 ||game->hand_plA.silvers > SILVER_T_SIZE || game->hand_plA.silvers < 0 ||
      game->hand_plA.golds > GOLD_T_SIZE || game->hand_plA.golds < 0 || game->hand_plA.diamonds > DIAMOND_T_SIZE || game->hand_plA.diamonds < 0) {
    return -1;
  }
  if ((game->turn_of != 'A' && game->turn_of != 'B')) {
    return -1;
  }
  if (game->tokens.finished_counter > FINISHED_GOODS_LIMIT || game->tokens.finished_counter < 0) {
    return -1;
  }
  return 0;
}
void set_finished_resources(GameData *game) {
  game->tokens.finished_counter = 0;
  if (game->tokens.leather_ptr == LEATHER_T_SIZE) {
    game->tokens.finished_counter++;
  }
  if (game->tokens.cloth_ptr == CLOTH_T_SIZE) {
    game->tokens.finished_counter++;
  }
  if (game->tokens.spice_ptr == SPICE_T_SIZE) {
    game->tokens.finished_counter++;
  }
  if (game->tokens.silver_ptr == SILVER_T_SIZE) {
    game->tokens.finished_counter++;
  }
  if (game->tokens.gold_ptr == GOLD_T_SIZE) {
    game->tokens.finished_counter++;
  }
  if (game->tokens.diamond_ptr == DIAMOND_T_SIZE) {
    game->tokens.finished_counter++;
  }
}
int sum_cards_player(CardGroup *group){
    return group->diamonds+group->golds+group->silvers+group->spices+group->cloths+group->leathers;
}
int sum_cards_market(CardGroup *group){
    return group->camels+group->diamonds+group->golds+group->silvers+group->spices+group->cloths+group->leathers;
}
int load_game_state(GameData *game)
{
    char save_file[MAX_PATH];
    find_data_path(save_file);
    FILE *file = fopen(save_file, "r");

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char *buffer = (char *)malloc(file_size + 1);
        int counted_size = fread(buffer, 1, file_size, file);
        if (counted_size != file_size)
        {
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
                               &game->leather_ptr, &game->seed, &game->tokens.bonus_3_ptr, &game->tokens.bonus_4_ptr, &game->tokens.bonus_5_ptr);
        // printf("Items read: %d\n", itemsRead);
        free(buffer);
        setSeed(game);
        if (is_round_over(game))
        {
            round_over(game);
            if (is_game_over(&(game->playerA), &(game->playerB)))
            {
                game_over(&(game->playerA), &(game->playerB));
                initializeGame(game);
            }
            else
            {
                initializeRound(game);
            }
        }
        if (is_game_over(&(game->playerA), &(game->playerB)))
        {
            game_over(&(game->playerA), &(game->playerB));
            initializeGame(game);
        }
        if (itemsRead < 21)
        {
            printf("Data was partially corrupted, use `--reset` to restart the game or manually correct the json.\n");
            printf("Input into the template json file your data manually as an alternative.\n");
            return -1;
        }
    } else {
    // Initialize default game state if no save file exists
    initializeGame(game);
  }
  set_finished_resources(game);
  if (checkDataIntegrity(game) == -1) {
    return -1;
  } else {
    return 0;
  }
}
void save_game_state(const GameData *game) {
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
  fprintf(file, "  \"bonus_3_ptr\": %i,\n", game->tokens.bonus_3_ptr);
  fprintf(file, "  \"bonus_4_ptr\": %i,\n", game->tokens.bonus_4_ptr);
  fprintf(file, "  \"bonus_5_ptr\": %i\n", game->tokens.bonus_5_ptr);
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
void process_arguments(GameData *game, int argc, char *argv[]) {
  if (argc < 2) {
    // printf("Addresses A:%p B:%p\n", (void *)playerA, (void *)playerB);
    printGameState(game);
    return;
  }
  int          turn_happened   = 0;
  int          round_over_bool = 0;
  PlayerScore *curr_player;
  CardGroup *curr_player_hand;
  if (game->turn_of == 'A') {
    curr_player = &(game->playerA);
    curr_player_hand = &(game->hand_plA);
  } else if (game->turn_of == 'B') {
    curr_player = &(game->playerB);
    curr_player_hand = &(game->hand_plB);
  } else {
    if (game->was_initialized == 0) {
      initializeGame(game);
    } else 
    printf("Data is corrupted: player turn of %c\n", game->turn_of);
    return;
  }
  // printf("Addresses A:%p B:%p, current:%p\n", (void *)playerA, (void *)playerB, (void *)curr_player);

  if (strncmp(argv[1], "--camels", 8) == 0) {
    int camels = game->market.camels;
    if (camels==0){
      printf("Error, no camels  in the market");
      return;
    }
    game->market.camels=0;
    curr_player_hand->camels+=camels;
    draw_cards_from_deck(&(game->market),game,camels);
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
  } else if (strncmp(argv[1], "--draw", 8) == 0) {
    if (sum_cards_player(curr_player_hand)>=7){
      printf("Error, hand is full");
      return;
    }
    draw_cards_from_deck(&(game->market),game,1);
    turn_happened += 1;
  } else if (strncmp(argv[1], "--state", 7) == 0) {
    printGameState(game);
  } else if (strncmp(argv[1], "--reset", 7) == 0) {
    initializeGame(game);
  } else if (strncmp(argv[1], "--help", 6) == 0) {
    print_help();
  } else {
    printf("Unknown command: %s\n", argv[1]);
  }
  if (turn_happened) {
    game->turn_of = (((game->turn_of - 'A') + 1) & 1) + 'A';
  }
  if (round_over_bool || is_round_over(game)) {
    round_over(game);
    initializeRound(game);
  } else {
    printGameState(game);
  }
  if (is_game_over(&(game->playerA), &(game->playerB))) {
    game_over(&(game->playerA), &(game->playerB));
    initializeGame(game);
  }
}

void draw_cards_from_deck(CardGroup *group, GameData *game, int cards){
  for (int i=0;i<cards;i++){
    char card=deck[game->deck[game->deck_ptr++]];

  }
}

void card_sale(GameData *game, char card_type[], int no_cards) {
  if (strncmp(card_type, "diamonds", 8) == 0) {
    int end = min(no_cards + game->diamond_ptr, DIAMOND_T_SIZE);
    for (int i = game->diamond_ptr; i < end; i++) {
      player->points += diamond_tokens[i];
    }
    player->no_goods_tokens += end - game->diamond_ptr;
    game->diamond_ptr = end;
  } else if (strncmp(card_type, "gold", 4) == 0) {
    int end = min(no_cards + game->gold_ptr, GOLD_T_SIZE);
    for (int i = game->gold_ptr; i < end; i++) {
      player->points += gold_tokens[i];
    }
    player->no_goods_tokens += end - game->gold_ptr;
    game->gold_ptr = end;
  } else if (strncmp(card_type, "silver", 6) == 0) {
    int end = min(no_cards + game->silver_ptr, SILVER_T_SIZE);
    for (int i = game->silver_ptr; i < end; i++) {
      player->points += silver_tokens[i];
    }
    player->no_goods_tokens += end - game->silver_ptr;
    game->silver_ptr = end;
  } else if (strncmp(card_type, "spice", 5) == 0) {
    int end = min(no_cards + game->spice_ptr, SPICE_T_SIZE);
    for (int i = game->spice_ptr; i < end; i++) {
      player->points += spice_tokens[i];
    }
    player->no_goods_tokens += end - game->spice_ptr;
    game->spice_ptr = end;
  } else if (strncmp(card_type, "cloth", 5) == 0) {
    int end = min(no_cards + game->cloth_ptr, CLOTH_T_SIZE);
    for (int i = game->cloth_ptr; i < end; i++) {
      player->points += cloth_tokens[i];
    }
    player->no_goods_tokens += end - game->cloth_ptr;
    game->cloth_ptr = end;
  } else if (strncmp(card_type, "leather", 7) == 0) {
    int end = min(no_cards + game->leather_ptr, LEATHER_T_SIZE);
    for (int i = game->leather_ptr; i < end; i++) {
      player->points += leather_tokens[i];
    }
    player->no_goods_tokens += end - game->leather_ptr;
    game->leather_ptr = end;
  }
  if (no_cards == 3 && game->tokens.bonus_3_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens.bonus_3_arr[game->tokens.bonus_3_ptr];
    game->tokens.bonus_3_ptr++;
  } else if (no_cards == 4 && game->tokens.bonus_4_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens.bonus_4_arr[game->tokens.bonus_4_ptr];
    game->tokens.bonus_4_ptr++;
  } else if (no_cards >= 5 && game->tokens.bonus_5_ptr < MAX_BONUS_TOKENS) {
    player->no_bonus_tokens++;
    player->points += game->tokens.bonus_5_arr[game->tokens.bonus_5_ptr];
    game->tokens.bonus_5_ptr++;
  }
}

int is_game_over(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN || playerB->seals == SEALS_TO_WIN) {
    return 1;
  } else {
    return 0;
  }
}

int is_round_over(GameData *game) {
  set_finished_resources(game);
  if (game->tokens.finished_counter == FINISHED_GOODS_LIMIT) {
    return 1;
  } else {
    return 0;
  }
}

void game_over(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN) {
    print_winning_trophy('A');
  } else if (playerB->seals == SEALS_TO_WIN) {
    print_winning_trophy('B');
  }
}

void round_over(GameData *game) {
  if (playerA->camels > playerB->camels) {
    playerA->points += CAMEL_TOKEN_VAL;
  } else if (playerB->camels > playerA->camels) {
    playerB->camels += CAMEL_TOKEN_VAL;
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
    game_state->remaining_tokens.bonus_3=MAX_BONUS_TOKENS-game_data->tokens.bonus_3_ptr;
    game_state->remaining_tokens.bonus_4=MAX_BONUS_TOKENS-game_data->tokens.bonus_4_ptr;
    game_state->remaining_tokens.bonus_5=MAX_BONUS_TOKENS-game_data->tokens.bonus_5_ptr;
    game_state->remaining_tokens.diamond=DIAMOND_T_SIZE-game_data->tokens.diamond_ptr;
    game_state->remaining_tokens.gold=GOLD_T_SIZE-game_data->tokens.gold_ptr;
    game_state->remaining_tokens.silver=SILVER_T_SIZE-game_data->tokens.silver_ptr;
    game_state->remaining_tokens.spice=SPICE_T_SIZE-game_data->tokens.spice_ptr;
    game_state->remaining_tokens.cloth=CLOTH_T_SIZE-game_data->tokens.cloth_ptr;
    game_state->remaining_tokens.leather=LEATHER_T_SIZE-game_data->tokens.leather_ptr;
    game_state->cards_in_deck=DECK_SIZE-game_data->deck_ptr;
}
