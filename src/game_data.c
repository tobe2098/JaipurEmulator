#include "game_data.h"
void initDeck(GameData *game) {
  int idx = 0;
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    for (int card_no = 0; card_no < cards_starting_deck_lookup_table[(int)card_type]; card_no++) {
      game->deck[idx++] = enum_to_char_lookup_table[(int)card_type];
    }
  }
}
void initDeckCustom(GameData *game, int cards_used[CARD_GROUP_SIZE]) {
  int arr_ptr = 0;

  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    int no_cards = cards_used[(int)card_type];
    while (no_cards) {
      game->deck[arr_ptr++] = enum_to_char_lookup_table[(int)card_type];
      no_cards--;
    }
  }
  game->deck_ptr = arr_ptr;
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    int no_cards = no_cards_lookup_table[(int)card_type] - cards_used[(int)card_type];
    while (no_cards) {
      game->deck[arr_ptr++] = enum_to_char_lookup_table[(int)card_type];
      no_cards--;
    }
  }
}

void setSeed(GameData *game) {
  if (!game->seed) {
    game->seed = (unsigned int)time(NULL);
  }
  srand(game->seed);
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    for (int no_token = 0; no_token < MAX_BONUS_TOKENS; no_token++) {
      game->bonus_tk_arrays[barr][no_token] = (no_token) / 2 + 1 + barr * MAX_BONUS_TOKENS / 2;
    }
    randomizeArrayInt(game->bonus_tk_arrays[barr], 0, MAX_BONUS_TOKENS);
  }
  initDeck(game);
#ifdef DEBUG
  printf("Deck: ");
  for (int i = 0; i < DECK_SIZE; i++) {
    printf("%c,", game->deck[i]);
  }
  printf("\n");
#endif
  randomizeArrayChar(game->deck, 0, DECK_SIZE);
#ifdef DEBUG
  printf("Deck: ");
  for (int i = 0; i < DECK_SIZE; i++) {
    printf("%c,", game->deck[i]);
  }
  printf("\n");
#endif
}

void setSeedCustom(GameData *game, int bonus_tokens_used[BONUS_TOKENS_DATA_ARRAY], int cards_used[CARD_GROUP_SIZE]) {
  if (!game->seed) {
    game->seed = (unsigned int)time(NULL);
  }
  int bonus_tokens[BONUS_TOKENS_DATA_ARRAY] = { [0 ... BONUS_TOKENS_DATA_ARRAY - 1] = BONUS_TOKENS_PER_VALUE };

  for (int idx = 0; idx < BONUS_TOKENS_DATA_ARRAY; idx++) {
    bonus_tokens[idx] -= bonus_tokens_used[idx];
  }

  srand(game->seed);
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    int arr_ptr = 0;
    for (int tk_type = barr * 3; tk_type < (barr + 1) * 3; tk_type++) {
      while (bonus_tokens_used[tk_type]) {
        game->bonus_tk_arrays[barr][arr_ptr++] = tk_type + 1;
        bonus_tokens_used[tk_type]--;
        game->bonus_tk_ptrs[barr]++;
      }
    }
    for (int tk_type = barr * 3; tk_type < (barr + 1) * 3; tk_type++) {
      while (bonus_tokens[tk_type]) {
        game->bonus_tk_arrays[barr][arr_ptr++] = tk_type + 1;
        bonus_tokens[tk_type]--;
      }
    }

    randomizeArrayInt(game->bonus_tk_arrays[barr], game->bonus_tk_ptrs[barr], MAX_BONUS_TOKENS);
  }
  initDeckCustom(game, cards_used);
  randomizeArrayChar(game->deck, game->deck_ptr, DECK_SIZE);
#ifdef DEBUG
  printf("Deck: ");
  for (int i = 0; i < DECK_SIZE; i++) {
    printf("%c,", game->deck[i]);
  }
  printf("\n");
#endif
}

void initGameData(GameData *game, unsigned int seed) {
  if (game->was_initialized == DATA_WAS_INIT) {
    return;
  }
  memset(game, 0, sizeof(GameData));
  game->market[camels] = STARTING_MARKET_CAMELS;
  game->seed           = seed;
  setSeed(game);
  game->turn_of         = (rand() & 1);
  game->was_initialized = DATA_WAS_INIT;
}
int initRoundGameData(GameData *game, int seed) {
  if (game->was_initialized != DATA_WAS_INIT) {
    return DATA_NOT_INIT_FLAG;
  }
  int sealsA = game->playerA.seals, sealsB = game->playerB.seals;
  int turn = game->turn_of;
  memset(game, 0, sizeof(GameData));
  game->was_initialized = DATA_WAS_INIT;
  game->turn_of         = turn;
  game->playerA.seals   = sealsA;
  game->playerB.seals   = sealsB;
  game->seed            = seed;
  setSeed(game);
  game->market[camels] = STARTING_MARKET_CAMELS;  // It is assumed these cards are drawn already in initDeck
  return DATA_OKAY_FLAG;
}
void startRound(GameData *game) {
  // DEAL CARDS TO MARKET
  drawCardsFromDeck(game->market, game, CARDS_IN_MARKET - STARTING_MARKET_CAMELS);
  // DEAL CARDS TO PLAYERS
  drawCardsFromDeck(game->hand_plA, game, INITIAL_HAND_SIZE);
  drawCardsFromDeck(game->hand_plB, game, INITIAL_HAND_SIZE);
}
void startGame(GameData *game, unsigned int seed) {
  game->was_initialized = 0;
  // printWelcomeMessage();
  initGameData(game, seed);
  startRound(game);
  // printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

void startNextRound(GameData *game, int seed) {
  initRoundGameData(game, seed);
  startRound(game);
  // printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

int checkDataIntegrity(GameData *game) {
  // Only to run in case of data loading, review after finishing data loading/saving
  // Probably should check that points and tokens are coherent.
  // Probably should check that seals are coherent.
  int total_tokens = 0, total_btokens = 0;
  if (game->was_initialized != DATA_WAS_INIT) {
#ifdef DEBUG
    printf("1, state:%i\n", game->was_initialized);
#endif
    return DATA_CORRUPTED_FLAG;
  }
  if (game->playerA.seals > SEALS_TO_WIN || game->playerA.seals < 0 || game->playerB.seals > SEALS_TO_WIN || game->playerB.seals < 0) {
#ifdef DEBUG
    printf("2\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  int remaining_cards[CARD_GROUP_SIZE] = { 0 };
  for (int ptr = game->deck_ptr; ptr < DECK_SIZE; ptr++) {
    remaining_cards[(int)char_to_enum_lookup_table[(int)game->deck[ptr]]]++;
  }
  if (game->deck_ptr > DECK_SIZE || game->deck_ptr < 0 || game->playerA.seals > 1 || game->playerB.seals > 2) {
#ifdef DEBUG
    printf("3\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  if (game->hand_plA[camels] + game->hand_plB[camels] + game->market[camels] + remaining_cards[camels] > CAMELS_TOTAL ||
      game->hand_plA[camels] < 0 || game->hand_plB[camels] < 0 || game->market[camels] < 0) {
#ifdef DEBUG
    printf("4\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  for (int tk_type = 0; tk_type < BONUS_TOKEN_TYPES; tk_type++) {
    if (!(game->bonus_tk_ptrs[tk_type] <= MAX_BONUS_TOKENS && game->bonus_tk_ptrs[tk_type] >= 0)) {
#ifdef DEBUG
      printf("5\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    total_btokens += game->bonus_tk_ptrs[tk_type];
  }
  if ((game->turn_of != PLAYER_A_NUM && game->turn_of != PLAYER_B_NUM)) {
#ifdef DEBUG
    printf("6\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  // int not_bound = 0;
  for (int card_type = 0; card_type < GOOD_TYPES; card_type++) {
#ifdef DEBUG
    if (card_type == 8) {
      printf("%i\n", remaining_cards[card_type]);
    }
#endif
    remaining_cards[(int)card_type] +=
      game->market[(int)card_type] + game->hand_plA[(int)card_type] + game->hand_plB[(int)card_type] + game->good_tk_ptrs[(int)card_type];
    if (remaining_cards[(int)card_type] > no_cards_lookup_table[(int)card_type] || game->market[(int)card_type] < 0 ||
        game->hand_plA[(int)card_type] < 0 || game->hand_plB[(int)card_type] < 0) {
#ifdef DEBUG
      printf("6.5, %i\n", card_type);
#endif
      return DATA_CORRUPTED_FLAG;
    }
  }
  for (int card_type = 0; card_type < GOOD_TYPES; card_type++) {
    if (game->good_tk_ptrs[(int)card_type] < 0 || game->good_tk_ptrs[(int)card_type] > good_tokens[(int)card_type].size) {
#ifdef DEBUG
      printf("7\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    total_tokens += game->good_tk_ptrs[(int)card_type];
  }
  if (game->playerA.no_goods_tokens + game->playerB.no_goods_tokens != total_tokens ||
      game->playerA.no_bonus_tokens + game->playerB.no_bonus_tokens != total_btokens) {
#ifdef DEBUG
    printf("8\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  return DATA_OKAY_FLAG;
}
int checkStateIntegrity(GameData *state, int used_cards[CARD_GROUP_SIZE]) {
  // Probably should check that points and tokens are coherent.
  int total_tokens = 0, total_btokens = 0;
  // Points are left undone for now
  // It cannot be calculated whether the players
  if (state->playerA.seals > SEALS_TO_WIN || state->playerA.seals < 0 || state->playerB.seals > SEALS_TO_WIN || state->playerB.seals < 0) {
#ifdef DEBUG
    printf("Seals\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  for (int card_idx = 0; card_idx < GOOD_TYPES; card_idx++) {
    if (state->good_tks[card_idx] > good_tokens[card_idx].size || state->good_tks[card_idx] < 0 ||
        used_cards[card_idx] > no_cards_lookup_table[card_idx] || used_cards[card_idx] < 0) {
#ifdef DEBUG
      printf("Size tokens and cards\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    // if (!((state->good_tks[card_idx] == 0 && used_cards[card_idx] >= good_tokens[card_idx].size) ||
    //       used_cards[card_idx] == good_tokens[card_idx].size - state->good_tks[card_idx])) {
    //   return DATA_CORRUPTED_FLAG;
    // }
    if ((good_tokens[card_idx].size - state->good_tks[card_idx]) + used_cards[card_idx] > no_cards_lookup_table[card_idx]) {
#ifdef DEBUG
      printf("Total cards out of deck exceed the max cards\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    total_tokens += good_tokens[card_idx].size - state->good_tks[card_idx];
  }
  if (total_tokens != state->playerA.no_goods_tokens + state->playerB.no_goods_tokens) {
#ifdef DEBUG
    printf("Total tokens is given is not the sum of the tokens of players.\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    if (state->bonus_tks[barr] > MAX_BONUS_TOKENS || state->bonus_tks[barr] < 0) {
#ifdef DEBUG
      printf("Bonus tokens out of bounds\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    int sum = 0;
    for (int tk = barr * 3; tk < (barr + 1) * 3; tk++) {
      sum += state->bonus_used[tk];
    }
    if (sum != state->bonus_tk_ptrs[barr] || sum > MAX_BONUS_TOKENS || sum < 0) {
#ifdef DEBUG
      printf("Sum of used bonus is not the pointer\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    if (sum != MAX_BONUS_TOKENS - state->bonus_tks[barr]) {
#ifdef DEBUG
      printf("Sum does not coincide with the pile\n");
#endif
      return DATA_CORRUPTED_FLAG;
    }
    total_btokens += sum;
  }
  if (total_btokens != state->playerA.no_bonus_tokens + state->playerB.no_bonus_tokens) {
#ifdef DEBUG
    printf("The total of bonus tokens does not coincide with player tokens\n");
#endif
    return DATA_CORRUPTED_FLAG;
  }
  return DATA_OKAY_FLAG;
}
int computeFinishedGoods(GameData *game) {
  int finished_counter = 0;
  for (int card_type = 0; card_type < GOOD_TYPES; card_type++) {
    finished_counter += (game->good_tk_ptrs[(int)card_type] >= no_cards_lookup_table[(int)card_type] - 1);
    // Should be
  }
  return finished_counter;
}
int sumOfCardsGroup(int group[CARD_GROUP_SIZE], int not_camels_bool) {
  int sum = 0;
  for (int i = 0; i < CARD_GROUP_SIZE; i++) {
    if (i == camels && not_camels_bool) {
      continue;
    }
    sum += group[i];
  }
  return sum;
}
// int getCardTypeIndex(int group[CARD_GROUP_SIZE], int card_index_input){
//   card_index card_type_index=diamonds;
//   int i=0;
//   while(i<card_index_input){
// #ifdef DEBUG
//     if (card_type_index>=CARD_GROUP_SIZE) {
//       printf("Error, out of bounds");
//       return -1;
//     }
// #endif
//     if (group[card_type_index]==0) card_type_index++;
//     else {
//       if (i+group[card_type_index]>=card_type_index) break;
//       else {
//         i+=group[card_type_index++];
//       }
//     }
//   }
//   return card_type_index;
// }

int processAction(GameData *game, int argc, char *argv[]) {
  // Expecting DATA_IS_OKAY
  //  In this function, return 0 is no turn action happened, return 1 is a turn action happened, OTHER NUMBERS ARE ERROR CODES.
  //   Go over the code logic (init, init when corrupt, starting a new game, loading, etc)
  if (argc < 2) {  //| (flags & DATA_CORRUPTED_FLAG) || (flags & DATA_NOT_INIT_FLAG)) { //There are no cases in which these flags make it
    // printf("Addresses A:%p B:%p\n", (void *)playerA, (void *)playerB);
    // gameStatePrint(game);
    return 0;
  }
  int          flags = 0, arg_ptr = FIRST_ARGUMENT_INDEX;
  PlayerScore *curr_player_score;
  int         *curr_player_hand;
  if (game->turn_of == PLAYER_A_NUM) {
    curr_player_score = &(game->playerA);
    curr_player_hand  = game->hand_plA;
  } else {
    curr_player_score = &(game->playerB);
    curr_player_hand  = game->hand_plB;
  }
  // flags |= DATA_OKAY_FLAG;
  // printf("Addresses A:%p B:%p, current:%p\n", (void *)playerA, (void *)playerB, (void *)curr_player);

  if (strncmp(argv[arg_ptr], "--camels", strlen("--camels")) == 0 || strncmp(argv[arg_ptr], "-c", strlen("-c")) == 0) {
    int camels_no = game->market[camels];
    if (camels_no == 0) {
      return NO_CAMELS | NO_GAME_PRINT_FLAG;
    }
    game->market[camels] = 0;
    curr_player_hand[camels] += camels_no;
    flags |= TURN_HAPPENED_FLAG;
    // flags |= drawCardsFromDeck(game->market, game, camels_no);
  } else if (strncmp(argv[arg_ptr], "--sell", strlen("--sell")) == 0 || strncmp(argv[arg_ptr], "-s", strlen("-s")) == 0) {
    // We assume maximum sale? No
    if (argc < 4) {
      return TOO_FEW_ARGS_FLAG | NO_GAME_PRINT_FLAG;
    }
#ifdef DEBUG
    if (arg_ptr > FIRST_ARGUMENT_INDEX) {
      return LOGIC_ERROR_FLAG | NO_GAME_PRINT_FLAG;
    }
#endif
    char *goods    = argv[++arg_ptr];
    int   no_goods = atoi(argv[++arg_ptr]);
    if (no_goods <= 0) {
      return TOO_FEW_CARDS_SALE | NO_GAME_PRINT_FLAG;
    }
    if (*goods == CAMEL_CHAR) {
      return NO_GAME_PRINT_FLAG | CANNOT_SELL_CAMELS;
    }
    flags |= cardSale(game, curr_player_score, curr_player_hand, goods[0], no_goods);
  } else if (strncmp(argv[arg_ptr], "--exchange", strlen("--exchange")) == 0 || strncmp(argv[arg_ptr], "-e", strlen("-e")) == 0) {
    // Here the structure of the arguments has to be "--exchange seq seq" where seq is a sequence of characters
    // Each sequence of characters will be composed of the characters referring to cards
    if (argc < 4) {
      return TOO_FEW_ARGS_FLAG | NO_GAME_PRINT_FLAG;
    }
#ifdef DEBUG
    if (arg_ptr > FIRST_ARGUMENT_INDEX) {
      return LOGIC_ERROR_FLAG | NO_GAME_PRINT_FLAG;
    }
#endif
    char *hand_cards     = argv[++arg_ptr];
    int   hand_cards_len = strlen(hand_cards);
    // int   camels_no              = atoi(argv[3]);
    char *market_goods_positions = argv[++arg_ptr];
    int   market_goods_len       = strlen(market_goods_positions);
    // if (camels_no > curr_player_hand[camels]) {
    //   // printf("Cannot exchange more camels than owned");
    //   return TOO_FEW_C_HAND_FLAG | NO_GAME_PRINT_FLAG;
    // }
    if (hand_cards_len != market_goods_len) {
      // printf("Number of cards from hand and market to be exchanged do not match");
      return ARGS_MISS_MATCH_FLAG | NO_GAME_PRINT_FLAG;
    }
    if (market_goods_len > 5) {
      // printf("The market has only 5 cards, do not input more than 5 positions.");
      return ARG_OVERFLOW_FLAG | NO_GAME_PRINT_FLAG;
    }

    flags |= cardExchange(game->market, curr_player_hand, hand_cards, market_goods_positions, hand_cards_len, market_goods_len);
  } else if (strncmp(argv[arg_ptr], "--take", strlen("--take")) == 0 || strncmp(argv[arg_ptr], "-t", strlen("-t")) == 0) {
    if (sumOfCardsGroup(curr_player_hand, TRUE) >= MAX_CARDS_HAND) {
      // printf("Error, hand is full");
      return TOO_MANY_C_HAND_FLAG | NO_GAME_PRINT_FLAG;
    }
    if (argc < 3) {  // Here in theory it would be "--take char"
      // printf("Too few arguments.\n");
      return TOO_FEW_ARGS_FLAG | NO_GAME_PRINT_FLAG;
    }
#ifdef DEBUG
    if (arg_ptr > FIRST_ARGUMENT_INDEX) {
      return LOGIC_ERROR_FLAG | NO_GAME_PRINT_FLAG;
    }
#endif
    // int idx=(int)(strtol(argv[2],NULL,10)&INT_MAX);
    flags |= takeCardFromMarket(game->market, curr_player_hand, argv[++arg_ptr][0]);
    // if (flags & TURN_HAPPENED_FLAG) {
    //   flags |= drawCardsFromDeck(game->market, game, 1);
    //   // } else { // Redundant
    //   //   return return_code;
    // }
#ifndef LIBRARY
  } else if (strncmp(argv[arg_ptr], "--state", strlen("--state")) == 0 || strncmp(argv[arg_ptr], "-S", strlen("-S")) == 0) {
    // gameStatePrint(game);
    return 0;
  } else if (strncmp(argv[arg_ptr], "--reset", strlen("--reset")) == 0 || strncmp(argv[arg_ptr], "-r", strlen("-r")) == 0) {
    game->was_initialized = 0;
    // startGame(game);
    return RESET_GAME_FLAG;
#endif
  } else {
    printf("Unknown command: %s\n", argv[arg_ptr]);
    return NO_GAME_PRINT_FLAG;
  }
  return flags;
}

int drawCardsFromDeck(int card_group[CARD_GROUP_SIZE], GameData *game, int cards) {
  for (; cards && game->deck_ptr < DECK_SIZE; cards--) {
    char card = game->deck[game->deck_ptr++];
    card_group[(int)char_to_enum_lookup_table[(int)card]]++;
  }
  if (cards) {
    return ROUND_OVER;
  } else {
    return 0;
  }
}

int updateMarket(GameData *game) {
  int total = sumOfCardsGroup(game->market, FALSE);
  return drawCardsFromDeck(game->market, game, CARDS_IN_MARKET - total);
}

int takeCardFromMarket(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char card) {
  int market_cards = sumOfCardsGroup(market, FALSE);
  if (market_cards != CARDS_IN_MARKET) {
    if (market_cards > CARDS_IN_MARKET) {
      return TOO_MANY_C_MARKET_FLAG | NO_GAME_PRINT_FLAG;
    } else {
      return TOO_FEW_C_MARKET_FLAG | NO_GAME_PRINT_FLAG;
    }
  }
  int card_type_index = (int)char_to_enum_lookup_table[(int)card];
  if (card_type_index == -1) {
    return CARD_DOES_NOT_EXIST | NO_GAME_PRINT_FLAG;
  }
  if (card_type_index == camels) {
    // printf("Taking an individual camel is not allowed.\n");
    return NOT_ALLOWED_FLAG | NO_GAME_PRINT_FLAG;
  }
  if (market[card_type_index] == 0) {
    // printf("That card is not in the market.\n");
    return MISSING_CARD_FLAG;
  }
  player_hand[card_type_index]++;
  market[card_type_index]--;
  return TURN_HAPPENED_FLAG;
}

int cardSale(GameData *game, PlayerScore *player_score, int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards) {
  int card_index = (int)char_to_enum_lookup_table[(int)card_type];
  if (player_hand[card_index] < no_cards) {
    return TOO_FEW_C_HAND_FLAG | ONLY_PRINT_HAND;
  }
  if (card_index == -1) {
    return CARD_DOES_NOT_EXIST | NO_GAME_PRINT_FLAG;
  }
  int end = MIN(no_cards + game->good_tk_ptrs[card_index], good_tokens[card_index].size);

  const int *good_array = good_tokens[card_index].tokens;

  for (int token_idx = game->good_tk_ptrs[card_index]; token_idx < end; token_idx++) {
    player_score->points += good_array[token_idx];
  }

  player_score->no_goods_tokens += end - game->good_tk_ptrs[card_index];
  game->good_tk_ptrs[card_index] = end;
  player_hand[char_to_enum_lookup_table[(int)card_type]] -= no_cards;
  if (no_cards <= 2) {
    return TURN_HAPPENED_FLAG;
  }
  no_cards = MIN(2, no_cards - 3);
  if (game->bonus_tk_ptrs[no_cards] < MAX_BONUS_TOKENS) {
    player_score->points += game->bonus_tk_arrays[no_cards][game->bonus_tk_ptrs[no_cards]];
    game->bonus_used[game->bonus_tk_arrays[no_cards][game->bonus_tk_ptrs[no_cards]] - 1]++;
    game->bonus_tk_ptrs[no_cards]++;
    player_score->no_bonus_tokens++;
  }
#ifdef DEBUG
  printf("Should be done.\n");
#endif
  return TURN_HAPPENED_FLAG;
}

int cardExchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char *hand_cards, char *market_idx, int hand_cards_len,
                 int market_goods_len) {
  // Read args
  int cards_from_hand[CARD_GROUP_SIZE] = { 0 };
  for (int idx = 0; idx < hand_cards_len; idx++) {
    int card_index = (int)char_to_enum_lookup_table[(int)hand_cards[idx]];
    if (card_index == -1) {
      return CARD_DOES_NOT_EXIST | NO_GAME_PRINT_FLAG;
    }
    cards_from_hand[card_index]++;
  }
  int cards_from_market[CARD_GROUP_SIZE] = { 0 };
  for (int idx = 0; idx < market_goods_len; idx++) {
    int card_index = (int)char_to_enum_lookup_table[(int)market_idx[idx]];
    if (card_index == -1) {
      return CARD_DOES_NOT_EXIST | NO_GAME_PRINT_FLAG;
    }
    cards_from_market[card_index]++;
  }
  // Check args
  // Check if the exchange from market includes camels
  if (cards_from_market[camels]) {
    return MIXING_GOODS_CAMELS | NO_GAME_PRINT_FLAG;
  }
  // Check if the exchange will overflow the hand
  if (sumOfCardsGroup(player_hand, TRUE) + cards_from_hand[camels] > MAX_CARDS_HAND) {
    return TOO_MANY_C_HAND_FLAG | ONLY_PRINT_HAND;
  }
  // Check if there are enough cards in each card group
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    if (market[card_type] < cards_from_market[card_type]) {
      return TOO_FEW_C_MARKET_FLAG | ONLY_PRINT_MARKET;
    }
    if (player_hand[card_type] < cards_from_hand[card_type]) {
      return TOO_FEW_C_HAND_FLAG | ONLY_PRINT_HAND;
    }
  }
  // Perform the exchange
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    market[(int)card_type] += cards_from_hand[(int)card_type] - cards_from_market[(int)card_type];
    player_hand[(int)card_type] += cards_from_market[(int)card_type] - cards_from_hand[(int)card_type];
  }
  return TURN_HAPPENED_FLAG;
}

int isGameOver(PlayerScore *playerA, PlayerScore *playerB) {
  return playerA->seals == SEALS_TO_WIN || playerB->seals == SEALS_TO_WIN;
}

int isRoundOver(GameData *game) {
  return computeFinishedGoods(game) == FINISHED_GOODS_LIMIT;  // || game->deck_ptr == DECK_SIZE;//Only on drawing
}

int endingChecks(GameData *game, int flags) {
  if (isRoundOver(game) || flags & ROUND_OVER) {
    flags |= compRoundWinningPlayer(game);
    if (flags & DRAW_FLAG) {
      return flags | ROUND_OVER;
    }
    if (isGameOver(&(game->playerA), &(game->playerB))) {
      return flags | GAME_OVER;
    } else {
      return flags | ROUND_OVER;
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

int compRoundWinningPlayer(GameData *game) {
  PlayerScore *playerA = &(game->playerA), *playerB = &(game->playerB);
  if (game->hand_plA[camels] > game->hand_plB[camels]) {
    playerA->points += CAMEL_TOKEN_VAL;
  } else if (game->hand_plA[camels] < game->hand_plB[camels]) {
    playerB->points += CAMEL_TOKEN_VAL;
  }
  if (playerA->points > playerB->points) {
    // playerA->seals++;
    // game->turn_of = PLAYER_B_NUM;
    return PLAYER_A_WINS;
  } else if (playerA->points < playerB->points) {
    // playerB->seals++;
    // game->turn_of = PLAYER_A_NUM;
    return 0;
  }
  if (playerA->no_bonus_tokens > playerB->no_bonus_tokens) {
    // playerA->seals++;
    // game->turn_of = PLAYER_B_NUM;
    return PLAYER_A_WINS;
  } else if (playerA->no_bonus_tokens < playerB->no_bonus_tokens) {
    // playerB->seals++;
    // game->turn_of = PLAYER_A_NUM;
    return 0;
  }
  if (playerA->no_goods_tokens > playerB->no_goods_tokens) {
    // playerA->seals++;
    // game->turn_of = PLAYER_B_NUM;
    return PLAYER_A_WINS;
  } else if (playerA->no_goods_tokens < playerB->no_goods_tokens) {
    // playerB->seals++;
    // game->turn_of = PLAYER_A_NUM;
    return 0;
  } else {
    return DRAW_FLAG;
  }
  // printf("ERROR: IT WAS A DRAW! CONGRATULATIONS! THIS IS NORMALLY IMPOSSIBLE\n");
}

void giveRewards(GameData *game, int flags) {
  if (flags & PLAYER_A_WINS) {
    game->turn_of = PLAYER_B_NUM;
    game->playerA.seals++;
  } else {
    game->turn_of = PLAYER_A_NUM;
    game->playerB.seals++;
  }
}

// int getMemoryForGames(PagePool *arena, int number_games) {
//   if (number_games <= 0) {
//     return -1;
//   }
//   size_mt block_size;
//   if (sizeof(GameData) % sizeof(void *) == 0) {
//     // Already aligned, no extra space needed
//     block_size = sizeof(GameData);
//   } else {
//     // Round up to next alignment boundary
//     block_size = (sizeof(GameData) + sizeof(void *) - 1) & ~(sizeof(void *) - 1);
//   }
//   if (number_games > SIZE_MT_MAX / block_size) {
//     return -1;
//   }
//   // We have to compute alignment needs. How much more than sizeof do we need to get alignment?
//   return initMemoryPool(arena, (number_games)*block_size + sizeof(void *));
// }

GameData *initLibGameDataCustom(GameData *game_state, unsigned int seed) {
  // Options are null state or default state? And then the custom one, but how to distinguish?
  //  ANOTHER VERSION ACCEPTING A STATE AS AN INPUT I SUPPOSE FOR INITIALIZATION;
  // Be very clear on how to use this (create struct to set the game state)
  if (game_state == NULL) {
    return NULL;
  }
  // Replace with linear allocator for cache locality
  GameData *game_data = (GameData *)malloc(sizeof(GameData));
  // GameData *game_data = (GameData *)mpalloc(arena, sizeof(GameData));
  if (game_data == NULL) {
    return NULL;
  }
  memcpy(game_data, game_state, sizeof(GameData));
  int used_cards[CARD_GROUP_SIZE];
  for (int c_type = 0; c_type < CARD_GROUP_SIZE; c_type++) {
    used_cards[c_type] = game_data->hand_plA[c_type] + game_data->hand_plB[c_type] + game_data->market[c_type];
  }
  int integrity = checkStateIntegrity(game_state, used_cards);
  if (!(integrity == DATA_OKAY_FLAG)) {
    return NULL;
  }
  game_data->was_initialized = 0;
  // initGameData(game_data);
  initGameDataFromState(game_data, seed, used_cards);
  // If the round is finished by the last action, do not reset the state
  setGameDataLib(game_data);
  return game_data;
}

GameData *initLibGameDataScratch(unsigned int seed) {
  // Replace with linear allocator for cache locality
  GameData *game_data = (GameData *)malloc(sizeof(GameData));
  // GameData *game_data = (GameData *)mpalloc(arena, sizeof(GameData));
  startGame(game_data, seed);
  setGameDataLib(game_data);
  return game_data;
}

GameData *cloneLibGameData(GameData *game_data_src) {
  if (game_data_src == NULL) {
    return NULL;
  }
  GameData *game_data_out = (GameData *)malloc(sizeof(GameData));
  if (game_data_out == NULL) {
    return NULL;
  }
  memcpy(game_data_out, game_data_src, sizeof(GameData));
  return game_data_out;
}

GameData *freeLibGameData(GameData *game_data) {
  if (game_data == NULL) {
    return NULL;
  }
  free(game_data);
  return NULL;
}

int processLibAction(GameData *game, int argc, char *argv[], int flags) {
  int error_print = flags & ERROR_PRINTING_FLAG;
  // int round_end   = flags & ROUND_OVER;
  flags = checkDataIntegrity(game);  // Flags are reset after input is accepted
  if (flags & DATA_OKAY_FLAG) {
    flags |= updateMarket(game);
    flags |= endingChecks(game, 0);
    if (!(flags & GAME_OVER || flags & ROUND_OVER)) {
      flags |= processAction(game, argc, argv);
    }
    if (flags & TURN_HAPPENED_FLAG) {
      game->turn_of = (game->turn_of + 1) & 1;
      flags |= updateMarket(game);
      flags |= endingChecks(game, flags);
    }
    // flags |= processAction(game, argc, argv, flags);
  }
  if (error_print) {
    printErrors(flags);
  }
  // Print error messages
  setGameDataLib(game);
  return flags;
}

void setGameDataLib(GameData *game_data) {
  for (int c_type = 0; c_type < GOOD_TYPES; c_type++) {
    game_data->good_tks[c_type] = good_tokens[c_type].size - game_data->good_tk_ptrs[c_type];
  }
  for (int b_type = 0; b_type < BONUS_TOKEN_TYPES; b_type++) {
    game_data->bonus_tks[b_type] = MAX_BONUS_TOKENS - game_data->bonus_tk_ptrs[b_type];
  }
  game_data->cards_in_deck = DECK_SIZE - game_data->deck_ptr;
}

void initGameDataFromState(GameData *game_data, unsigned int seed, int used_cards[CARD_GROUP_SIZE]) {
  game_data->seed            = seed;
  game_data->was_initialized = DATA_WAS_INIT;

  setSeedCustom(game_data, game_data->bonus_used, used_cards);
}

// void set_GameState_from_GameData(GameData *game_data, GameState *game_state) {
//   memcpy(&(game_data->turn_of), &(game_state->turn_of), sizeof(int) + sizeof(int[CARD_GROUP_SIZE]) * 3 + sizeof(PlayerScore) * 2);

//   for (int good = 0; good < GOOD_TYPES; good++) {
//     game_state->good_tks[good] = good_tokens[good].size - game_data->good_tk_ptrs[good];
//   }
//   for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
//     game_state->bonus_tks[barr] = MAX_BONUS_TOKENS - game_data->bonus_tk_ptrs[barr];
//   }
//   game_state->cards_in_deck = DECK_SIZE - game_data->deck_ptr;
// }
