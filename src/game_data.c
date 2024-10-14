#include "game_data.h"
void initDeck(GameData *game) {
  int idx = 0;
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    for (int card_no = 0; card_no < cards_starting_deck_lookup_table[card_type]; card_no++) {
      game->deck[idx++] = enum_to_char_lookup_table[card_type];
    }
  }
}
void setSeed(GameData *game) {
  srand(game->seed);
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    for (int no_token = 0; no_token < MAX_BONUS_TOKENS; no_token++) {
      game->bonus_tk_arrays[barr][no_token] = (no_token) / 2 + 1 + barr * MAX_BONUS_TOKENS / 2;
    }
    randomize_int_array(game->bonus_tk_arrays[barr], MAX_BONUS_TOKENS);
  }
  initDeck(game);
  randomize_char_array(game->deck, DECK_SIZE);
#ifndef DEBUG
  printf("Deck: ");
  for (int i = 0; i < DECK_SIZE; i++) {
    printf("%c,", game->deck[i]);
  }
  printf("\n");
#endif
}

void initGameData(GameData *game) {
  if (game->was_initialized == 1) {
    return;
  }
  memset(game, 0, sizeof(GameData));
  game->market[camels] = STARTING_MARKET_CAMELS;
  game->seed           = (unsigned int)time(NULL);
  setSeed(game);
  game->turn_of         = PLAYER_A_CHAR + (rand() & 1);
  game->was_initialized = 1;
}
int resetGameData(GameData *game) {
  if (game->was_initialized == 0) {
    return DATA_IS_CORRUPTED;
  }
  memset(game->hand_plA, 0, CARD_GROUP_SIZE);
  memset(game->hand_plB, 0, CARD_GROUP_SIZE);
  memset(game->market, 0, CARD_GROUP_SIZE);
  memset((game->resource_tk_ptrs), 0, sizeof(game->resource_tk_ptrs));
  memset((game->bonus_tk_arrays), 0, sizeof(game->bonus_tk_arrays));
  memset((game->bonus_tk_ptrs), 0, sizeof(game->bonus_tk_ptrs));
  game->seed = (unsigned int)time(NULL);
  setSeed(game);
  game->market[camels] = STARTING_MARKET_CAMELS;
  game->deck_ptr       = 0;
  return DATA_IS_OKAY;
}
void startRound(GameData *game) {
  // DEAL CARDS TO MARKET
  drawCardsFromDeck(game->market, game, CARDS_IN_MARKET - STARTING_MARKET_CAMELS);
  // DEAL CARDS TO PLAYERS
  drawCardsFromDeck(game->hand_plA, game, INITIAL_HAND_SIZE);
  drawCardsFromDeck(game->hand_plB, game, INITIAL_HAND_SIZE);
}
void initGame(GameData *game) {
  game->was_initialized = 0;
  // print_welcome_message();
  initGameData(game);
  startRound(game);
  // printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

void initRound(GameData *game) {
  resetGameData(game);
  // printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

int isHandSizeCorrect(int *card_group, int max) {
  int sum = 0;
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    sum += card_group[card_type];
  }
  return sum <= max;
}
int checkDataIntegrity(GameData *game) {
  // Only to run in case of data loading, review after finishing data loading/saving
  int remaining_cards[CARD_GROUP_SIZE] = { 0 };
  for (int ptr = game->deck_ptr; ptr < DECK_SIZE; ptr++) {
    remaining_cards[char_to_enum_lookup_table[game->deck[ptr]]]++;
  }
  if (game->deck_ptr >= DECK_SIZE || game->deck_ptr < 0 || game->playerA.seals > 1 || game->playerB.seals > 2) {
    return DATA_IS_CORRUPTED;
  }
  if (game->hand_plA[camels] + game->hand_plB[camels] + game->market[camels] + remaining_cards[camels] > CAMELS_TOTAL ||
      game->hand_plA[camels] < 0 || game->hand_plB[camels] < 0 || game->market[camels] < 0) {
    return DATA_IS_CORRUPTED;
  }
  int tokens_bound = 1;
  for (int tk_type = 0; tk_type < BONUS_TOKEN_TYPES; tk_type++) {
    tokens_bound &= (game->bonus_tk_ptrs[tk_type] <= MAX_BONUS_TOKENS && game->bonus_tk_ptrs[tk_type] >= 0);
  }
  if (!tokens_bound) {
    return DATA_IS_CORRUPTED;
  }
  if ((game->turn_of != PLAYER_A_CHAR && game->turn_of != PLAYER_B_CHAR)) {
    return DATA_IS_CORRUPTED;
  }
  int not_bound = 0;
  for (int card_type = 0; card_type < RESOURCE_TYPES; card_type++) {
    remaining_cards[card_type] +=
      game->market[card_type] + game->hand_plA[card_type] + game->hand_plB[card_type] + game->resource_tk_ptrs[card_type];
    not_bound |= (remaining_cards[card_type] > no_cards_lookup_table[card_type]);
  }
  if (not_bound) {
    return DATA_IS_CORRUPTED;
  }
  for (int card_type = 0; card_type < RESOURCE_TYPES; card_type++) {
    if (game->resource_tk_ptrs[card_type] < 0) {
      return DATA_IS_CORRUPTED;
    }
  }
  return DATA_IS_OKAY;
}
int computeFinishedResources(GameData *game) {
  int finished_counter = 0;
  for (int card_type = 0; card_type < RESOURCE_TYPES; card_type++) {
    finished_counter += (game->resource_tk_ptrs[card_type] >= no_cards_lookup_table[card_type] - 1);
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
// #ifndef DEBUG
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
  // In this function, return 0 is no turn action happened, return 1 is a turn action happened, OTHER NUMBERS ARE ERROR CODES.
  //  Go over the code logic (init, init when corrupt, starting a new game, loading, etc)
  int return_code = DATA_IS_OKAY;
  if (argc < 2) {
    // printf("Addresses A:%p B:%p\n", (void *)playerA, (void *)playerB);
    printGameState(game);
    return NO_TURN_HAPPENED;
  }
  PlayerScore *curr_player_score;
  int         *curr_player_hand;
  if (game->turn_of == PLAYER_A_CHAR) {
    curr_player_score = &(game->playerA);
    curr_player_hand  = game->hand_plA;
  } else if (game->turn_of == PLAYER_B_CHAR) {
    curr_player_score = &(game->playerB);
    curr_player_hand  = game->hand_plB;
  } else {
    if (game->was_initialized == 0) {
      initGame(game);
      return DATA_NOT_INIT;
    } else {
      // #ifndef DEBUG
      // printf("Data is corrupted: player turn of %c\n", game->turn_of);
      // #endif
      return DATA_IS_CORRUPTED;
    }
  }
  // printf("Addresses A:%p B:%p, current:%p\n", (void *)playerA, (void *)playerB, (void *)curr_player);

  if (strncmp(argv[1], "--camels", 8) == 0) {
    int camels_no = game->market[camels];
    if (camels_no == 0) {
      return (TOO_FEW_CARDS | MARKET | camels);
    }
    game->market[camels] = 0;
    curr_player_hand[camels] += camels_no;
    return_code |= drawCardsFromDeck(game->market, game, camels_no);
  } else if (strncmp(argv[1], "--sell", 6) == 0) {
    // We assume maximum sale? No
    if (argc < 4) {
      return TOO_FEW_ARGS;
    }
    char *goods    = argv[2];
    int   no_goods = atoi(argv[3]);
    return_code |= cardSale(game, curr_player_score, curr_player_hand, goods, no_goods);
  } else if (strncmp(argv[1], "--exchange", 10) == 0) {
    // Here the structure of the arguments has to be "--exchange seq num seq" where seq is a sequence of characters
    // Each sequence of characters will be composed of the characters referring to cards
    if (argc < 5) {
      return TOO_FEW_ARGS;
    }
    char *hand_idx                   = argv[2];
    int   hand_idx_len               = strlen(hand_idx);
    int   camels_no                  = atoi(argv[3]);
    char *market_goods_positions     = argv[4];
    int   market_goods_positions_len = strlen(market_goods_positions);
    if (camels_no > curr_player_hand[camels]) {
      // printf("Cannot exchange more camels than owned");
      return TOO_FEW_CARDS | HAND | camels;
    }
    if (hand_idx_len + camels_no != market_goods_positions_len) {
      // printf("Number of cards from hand and market to be exchanged do not match");
      if (hand_idx_len + camels_no > market_goods_positions_len) {
        return ARGS_DO_NOT_MATCH | TOO_FEW_CARDS | MARKET;
      } else {
        return ARGS_DO_NOT_MATCH | TOO_FEW_CARDS | HAND;
      }
    }
    if (market_goods_positions_len > 5) {
      // printf("The market has only 5 cards, do not input more than 5 positions.");
      return ARG_OVERFLOW | MARKET;
    }
    return_code |=
      cardExchange(game->market, curr_player_hand, hand_idx, market_goods_positions, camels_no, hand_idx_len, market_goods_positions_len);
  } else if (strncmp(argv[1], "--take", 6) == 0) {
    if (sumOfCardsGroup(curr_player_hand, 1) >= 7) {
      // printf("Error, hand is full");
      return TOO_MANY_CARDS | HAND;
    }
    if (argc < 3) {  // Here in theory it would be "--take char"
      // printf("Too few arguments.\n");
      return TOO_FEW_ARGS;
    }
    // int idx=(int)(strtol(argv[2],NULL,10)&INT_MAX);
    return_code |= takeCardFromMarket(game->market, curr_player_hand, argv[2][0]);
    if (return_code & TURN_HAPPENED) {
      return_code |= drawCardsFromDeck(game->market, game, 1);
      // } else { // Redundant
      //   return return_code;
    }
  } else if (strncmp(argv[1], "--state", 7) == 0) {
    printGameState(game);
    return NO_TURN_HAPPENED;
  } else if (strncmp(argv[1], "--reset", 7) == 0) {
    game->was_initialized = 0;
    initGame(game);
    return NO_TURN_HAPPENED;
  } else if (strncmp(argv[1], "--help", 6) == 0) {
    print_help();
    return NO_TURN_HAPPENED;
  } else {
    printf("Unknown command: %s\n", argv[1]);
    return NO_TURN_HAPPENED;
  }
  return return_code;
}

int drawCardsFromDeck(int card_group[CARD_GROUP_SIZE], GameData *game, int cards) {
  for (int card = 0; card < cards && game->deck_ptr < DECK_SIZE; card++) {
    char card = game->deck[game->deck_ptr++];
    card_group[char_to_enum_lookup_table[card]]++;
  }
  return TURN_HAPPENED;
}

int takeCardFromMarket(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char card) {
  int market_cards = sum_cards_market(market);
  if (market_cards != CARDS_IN_MARKET) {
    if (market_cards > CARDS_IN_MARKET) {
      return TOO_MANY_CARDS | MARKET;
    } else {
      return TOO_FEW_CARDS | MARKET;
    }
  }
  card_index card_type_index = char_to_enum_lookup_table[card];
  if (card_type_index == camels) {
    // printf("Taking an individual camel is not allowed.\n");
    return NOT_ALLOWED_ACTION | camels;
  }
  if (market[card_type_index] == 0) {
    // printf("That card is not in the market.\n");
    return MISSING_CARD | MARKET | card_type_index;
  }
  player_hand[card_type_index]++;
  market[card_type_index]--;
  return TURN_HAPPENED;
}

int cardSale(GameData *game, PlayerScore *player_score, int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards) {
  int card_index = char_to_enum_lookup_table[card_type];
  if (player_hand[card_index] < no_cards) {
    return TOO_FEW_CARDS | HAND | card_index;
  }

  int end = min(no_cards + game->resource_tk_ptrs[card_index], resource_tokens[card_index].size);

  int *resource_array = resource_tokens[card_index].tokens;

  for (int token_idx = game->resource_tk_ptrs[card_index]; token_idx < end; token_idx++) {
    player_score->points += resource_array[token_idx];
  }

  player_score->no_goods_tokens += end - game->resource_tk_ptrs[card_index];
  game->resource_tk_ptrs[card_index] = end;

  if (no_cards <= 2) {
    return TURN_HAPPENED;
  }
  no_cards = min(2, no_cards - 3);
  if (game->bonus_tk_ptrs[no_cards] < MAX_BONUS_TOKENS) {
    player_score->points += game->bonus_tk_arrays[no_cards][game->bonus_tk_ptrs[no_cards]];
    game->bonus_tk_ptrs[no_cards]++;
    player_score->no_bonus_tokens++;
  }
  return TURN_HAPPENED;
}

int cardExchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char *hand_idx, char *market_idx, int camels_no,
                 int hand_idx_len, int market_goods_positions_len) {
  // From the process_args function where this is called we know the strlens of the two char*s are valid (<6)
  int cards_from_hand[CARD_GROUP_SIZE] = { 0 };
  for (int idx = 0; idx < hand_idx_len; idx++) {
    cards_from_hand[char_to_enum_lookup_table[hand_idx[idx]]]++;
  }
  cards_from_hand[camels]                = camels_no;
  int cards_from_market[CARD_GROUP_SIZE] = { 0 };
  for (int idx = 0; idx < market_goods_positions_len; idx++) {
    cards_from_market[char_to_enum_lookup_table[market_idx[idx]]]++;
  }

  // Check if the exchange from market includes both goods and camels
  if (cards_from_market[camels]) {
    for (int card_type = 0; card_type < RESOURCE_TYPES; card_type++) {
      if (cards_from_market[card_type] != 0) {
        return MIXING_GOODS_CAMELS;
      }
    }
  }
  for (int card_type = 0; card_type < CARD_GROUP_SIZE; card_type++) {
    market[card_type] += cards_from_hand[card_type] - cards_from_market[card_type];
    player_hand[card_type] += cards_from_market[card_type] - cards_from_hand[card_type];
  }
  return TURN_HAPPENED;
}

int isGameOver(PlayerScore *playerA, PlayerScore *playerB) {
  return playerA->seals == SEALS_TO_WIN || playerB->seals == SEALS_TO_WIN;
}

int isRoundOver(GameData *game) {
  return computeFinishedResources(game) == FINISHED_GOODS_LIMIT || game->deck_ptr == DECK_SIZE;
}

int compRoundWinningPlayer(GameData *game) {
  PlayerScore *playerA = &(game->playerA), *playerB = &(game->playerB);
  if (game->hand_plA[camels] > game->hand_plB[camels]) {
    playerA->points += CAMEL_TOKEN_VAL;
  } else if (game->hand_plA[camels] < game->hand_plB[camels]) {
    playerB->points += CAMEL_TOKEN_VAL;
  }
  if (playerA->points > playerB->points) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
  } else if (playerA->points < playerB->points) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
  }
  return 0;
  if (playerA->no_bonus_tokens > playerB->no_bonus_tokens) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
  } else if (playerA->no_bonus_tokens < playerB->no_bonus_tokens) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
  }
  return 0;
  if (playerA->no_goods_tokens > playerB->no_goods_tokens) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
  } else if (playerA->no_goods_tokens < playerB->no_goods_tokens) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
  } else {
    return DRAW;
  }
  return 0;
  // printf("ERROR: IT WAS A DRAW! CONGRATULATIONS! THIS IS NORMALLY IMPOSSIBLE\n");
}

GameState interfaceJaipurEmulator() {
  ANOTHER VERSION ACCEPTING A STATE AS AN INPUT I SUPPOSE FOR INITIALIZATION;
  static GameData                                             g_data = { .was_initialized = 0 };
  init(g_data);  // Initialize only if the was_initialized is zero, or if the round is over?

  // If the round is finished by the last action, do not reset the state
  GameState g_state;
  set_GameState_from_GameData(&g_data, &g_state);
  return g_state;
}

void set_GameState_from_GameData(GameData *game_data, GameState *game_state) {
  game_state->turn_of = game_data->turn_of;

  memcpy(&(game_data->market), &(game_state->market), sizeof(int[CARD_GROUP_SIZE]) * 3 * sizeof(PlayerScore) * 2);

  for (int resource = 0; resource < RESOURCE_TYPES; resource++) {
    game_state->resource_tks[resource] = resource_tokens[resource].size - game_data->resource_tk_ptrs[resource];
  }
  for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++) {
    game_state->bonus_tks[barr] = MAX_BONUS_TOKENS - game_data->bonus_tk_ptrs[barr];
  }
  game_state->cards_in_deck = DECK_SIZE - game_data->deck_ptr;
}
