#include "game_data.h"
void initDeck(char deck[DECK_SIZE+1]){
  int idx=0;
  for (int card_type=0;card_type<CARD_GROUP_SIZE;card_type++){
    for (int card_no=0;card_no<cards_starting_deck_lookup_table[card_type];card_no++){
      deck[idx++]=enum_to_char_lookup_table[card_type];
    }
  }
}
void setSeed(GameData *game){
    srand(game->seed);
    for (int barr = 0; barr < BONUS_TOKEN_TYPES; barr++)
    {
        for (int no_token = 0; no_token < MAX_BONUS_TOKENS; no_token++)
        {
            game->bonus_tk_arrays[barr][no_token] = no_token;
        }
        randomize_int_array(game->bonus_tk_arrays[barr], MAX_BONUS_TOKENS);
    }
    for (int i = 0; i < DECK_SIZE; i++)
    {
        game->deck[i] = i;
    }
    randomize_int_array(game->deck, DECK_SIZE);
    printf("Deck: ");
    for (int i = 0; i < DECK_SIZE; i++)
    {
        printf("%c,", game->deck[i]);
    }
    printf("\n");
}

void initGameData(GameData *game){
    if (game->was_initialized == 1)
        return;
    memset(game->hand_plA,0,CARD_GROUP_SIZE);
    memset(game->hand_plB,0,CARD_GROUP_SIZE);
    memset(game->market,0,CARD_GROUP_SIZE);
    game->market[camels] = 3;
    memset(&(game->playerA),0,sizeof(PlayerScore));
    memset(&(game->playerB),0,sizeof(PlayerScore));
    game->seed = (unsigned int)time(NULL);
    setSeed(game);
    memset(&(game->resource_tk_ptrs),0,sizeof(game->resource_tk_ptrs));
    memset(&(game->bonus_tk_arrays),0,sizeof(game->bonus_tk_arrays));
    memset(&(game->bonus_tk_ptrs),0,sizeof(game->bonus_tk_ptrs));
    game->deck_ptr = 0;
    game->turn_of = PLAYER_A_CHAR + (rand() & 1);
    game->was_initialized=1;
}
int resetGameData(GameData *game){
    if (game->was_initialized==0){
      return -1;
    }
    memset(game->hand_plA,0,CARD_GROUP_SIZE);
    memset(game->hand_plB,0,CARD_GROUP_SIZE);
    memset(game->market,0,CARD_GROUP_SIZE);
    game->market[camels] = 3;
    game->seed = (unsigned int)time(NULL);
    setSeed(game);
    memset(&(game->resource_tk_ptrs),0,sizeof(game->resource_tk_ptrs));
    memset(&(game->bonus_tk_arrays),0,sizeof(game->bonus_tk_arrays));
    memset(&(game->bonus_tk_ptrs),0,sizeof(game->bonus_tk_ptrs));
    game->deck_ptr = 0;
    return 0;
}
void startGame(GameData *game){
    //DEAL CARDS TO MARKET
    drawCardsFromDeck(&(game->market),game,2);
    //DEAL CARDS TO PLAYERS
    drawCardsFromDeck(&(game->hand_plA),game,INITIAL_HAND_SIZE);
    drawCardsFromDeck(&(game->hand_plB),game,INITIAL_HAND_SIZE);
}
void initGame(GameData *game){
    game->was_initialized=0;
    print_welcome_message();
    initGameData(game);
    startGame(game);
    printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

void initRound(GameData *game){
    resetGameData(game);
    printf("<Turn> %s starts this round <Turn>\n", getPlayerName(game->turn_of));
}

void printGameState(GameData *game) {
  printf("\n");
  printf("<Scores>\n");
  printf("<Player A> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game->playerA.points,
         game->playerA.seals, game->playerA.no_bonus_tokens, game->playerA.no_goods_tokens);
  printf("<Player B> Points:%i, Seals of excellence:%i, Bonus tokens:%i, Goods tokens:%i\n", game->playerB.points,
         game->playerB.seals, game->playerB.no_bonus_tokens, game->playerB.no_goods_tokens);
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
  //INTRODUCE KEY PRESS FOR HAND SECRECY, maybe a console clearing before state
}
int isHandSizeCorrect(int *card_group, int max){
  int sum=0;
  for (int card_type=0;card_type<CARD_GROUP_SIZE;card_type++){
    sum+=card_group[card_type];
  }
  return sum<=max;
}
int checkDataIntegrity(GameData *game)
{
  //Only to run in case of data loading, review after finishing data loading/saving
  int remaining_cards[CARD_GROUP_SIZE]={0};
  for (int ptr=game->deck_ptr;ptr<DECK_SIZE;ptr++){
    remaining_cards[char_to_enum_lookup_table[game->deck[ptr]]]++;
  }
  if (game->deck_ptr>=DECK_SIZE || game->deck_ptr<0||game->playerA.seals>1||game->playerB.seals>2){
    return -1;
  }
  if (game->hand_plA[camels] + game->hand_plB[camels]+game->market[camels]+remaining_cards[camels] > CAMELS_TOTAL || game->hand_plA[camels] < 0 || game->hand_plB[camels] < 0||game->market[camels]<0){
      return -1;
  }
  int tokens_bound=1;
  for (int tk_type=0;tk_type<BONUS_TOKEN_TYPES;tk_type++){
    tokens_bound&=(game->bonus_tk_ptrs[tk_type]<=MAX_BONUS_TOKENS && game->bonus_tk_ptrs[tk_type]>=0);
  }
  if (!tokens_bound) return -1;
  if ((game->turn_of != PLAYER_A_CHAR && game->turn_of != PLAYER_B_CHAR)){
      return -1;
  }
  int not_bound=0;
  for (int card_type=0;card_type<RESOURCE_TYPES;card_type++){
    remaining_cards[card_type]+=game->market[card_type]+game->hand_plA[card_type]+game->hand_plB[card_type]+game->resource_tk_ptrs[card_type];
    not_bound|=(remaining_cards[card_type]>no_cards_lookup_table[card_type]);
  }
  if (not_bound){
      return -1;
  }
  for (int card_type=0;card_type<RESOURCE_TYPES;card_type++){
    if (game->resource_tk_ptrs[card_type]<0) return -1;
  }
  return 0;
}
int computeFinishedResources(GameData *game) {
  int finished_counter = 0;
  for (int card_type=0;card_type<RESOURCE_TYPES;card_type++){
    finished_counter+=(game->resource_tk_ptrs[card_type]>=no_cards_lookup_table[card_type]-1);
    //Should be
  }
  return finished_counter;
}
int sumOfCardsGroup(int group[CARD_GROUP_SIZE],int not_camels_bool){
  int sum=0;
  for (int i=0;i<CARD_GROUP_SIZE;i++){
    if (i==camels&&not_camels_bool) continue;
    sum+=group[i];
  }
  return sum;
}
int getCardTypeIndex(int group[CARD_GROUP_SIZE], int card_index_input){
  card_index card_type_index=diamonds;
  int i=0;
  while(i<card_index_input){
#ifndef DEBUG
    if (card_type_index>=CARD_GROUP_SIZE) {
      printf("Error, out of bounds");
      return -1;
    }
#endif
    if (group[card_type_index]==0) card_type_index++;
    else {
      if (i+group[card_type_index]>=card_type_index) break;
      else {
        i+=group[card_type_index++];
      }
    }
  }
  return card_type_index;
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
        int itemsRead=0;
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
        if (isRoundOver(game))
        {
            roundOverWinningPlayer(game);
            if (isGameOver(&(game->playerA), &(game->playerB)))
            {
                gameOverPrint(&(game->playerA), &(game->playerB));
                initGame(game);
            }
            else
            {
                initRound(game);
            }
        }
        if (isGameOver(&(game->playerA), &(game->playerB)))
        {
            gameOverPrint(&(game->playerA), &(game->playerB));
            initGame(game);
        }
        if (itemsRead < 21)
        {
            printf("Data was partially corrupted, use `--reset` to restart the game or manually correct the json.\n");
            printf("Input into the template json file your data manually as an alternative.\n");
            return -1;
        }
    } else {
    // Initialize default game state if no save file exists
    initGame(game);
  }
  computeFinishedResources(game);
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
void processAction(GameData *game, int argc, char *argv[])
{
    // Go over the code logic (init, init when corrupt, starting a new game, loading, etc)

    if (argc < 2)
    {
        // printf("Addresses A:%p B:%p\n", (void *)playerA, (void *)playerB);
        printGameState(game);
        return;
    }
    int turn_happened = 0;
    int round_over_bool = 0;
    PlayerScore *curr_player_score;
    int *curr_player_hand;
    if (game->turn_of == PLAYER_A_CHAR)
    {
        curr_player_score = &(game->playerA);
        curr_player_hand = game->hand_plA;
    } else if (game->turn_of == PLAYER_B_CHAR) {
    curr_player_score = &(game->playerB);
    curr_player_hand = game->hand_plB;
  } else {
    if (game->was_initialized == 0) {
      initGame(game);
    } else 
    printf("Data is corrupted: player turn of %c\n", game->turn_of);
    return;
  }
  // printf("Addresses A:%p B:%p, current:%p\n", (void *)playerA, (void *)playerB, (void *)curr_player);

  if (strncmp(argv[1], "--camels", 8) == 0) {
    int camels_no = game->market[camels];
    if (camels_no==0){
      printf("Error, no camels  in the market");
      return;
    }
    game->market[camels]=0;
    curr_player_hand[camels]+=camels_no;
    drawCardsFromDeck(&(game->market),game,camels_no);
    turn_happened += 1;
  } else if (strncmp(argv[1], "--sell", 6) == 0) {
    //We assume maximum sale? No
    if (argc < 4) {
      printf("Too few arguments.\n");
      return;
    }
    char *goods    = argv[2];
    int   no_goods = atoi(argv[3]);
    cardSale(game,curr_player_score,curr_player_hand, goods, no_goods);
    turn_happened += 1;
  } else if (strncmp(argv[1], "--exchange", 10) == 0) {
    //Here the structure of the arguments has to be "--exchange seq num seq" where seq is a sequence of characters
    //Each sequence of characters will be composed of the characters referring to cards 
    if (argc < 5) {
      printf("Too few arguments.\n");
      return;
    }
    char* hand_idx=argv[2];
    int hand_idx_len=strlen(hand_idx);
    int camels_no = atoi(argv[3]);
    char* market_goods_positions=argv[4];
    int market_goods_positions_len=strlen(market_goods_positions);
    if (camels_no>curr_player_hand[camels]){
      printf("Cannot exchange more camels than owned");
      return;
    }
    if (hand_idx_len+camels_no!=market_goods_positions_len){
      printf("Number of cards from hand and market to be exchanged do not match");
      return;
    }
    if (market_goods_positions_len>5){
      printf("The market has only 5 cards, do not input more than 5 positions.");
      return;
    }
    cardExchange(game->market,curr_player_hand,hand_idx,market_goods_positions,camels_no,hand_idx_len,market_goods_positions_len);
    turn_happened += 1;
  } else if (strncmp(argv[1], "--take", 6) == 0) {
    if (sumOfCardsGroup(curr_player_hand,1)>=7){
      printf("Error, hand is full");
      return;
    }
    if (argc < 3) { //Here in theory it would be "--take 0-4"
      printf("Too few arguments.\n");
      return;
    }
    int idx=(int)(strtol(argv[2],NULL,10)&INT_MAX);
    if (idx>=5) {
      printf("There are only 5 cards in the market, indexed 0-4.\n");
      return;
    }
    if (takeCardFromMarket(&(game->market),curr_player_hand,argv[2])==0){
      drawCardsFromDeck(game->market, game, 1);
      turn_happened += 1;
    }
  } else if (strncmp(argv[1], "--state", 7) == 0) {
    printGameState(game);
  } else if (strncmp(argv[1], "--reset", 7) == 0) {
    game->was_initialized=0;
    initGame(game);
  } else if (strncmp(argv[1], "--help", 6) == 0) {
    print_help();
  } else {
    printf("Unknown command: %s\n", argv[1]);
  }
  if (turn_happened) {
    game->turn_of = (((game->turn_of - PLAYER_A_CHAR) + 1) & 1) + PLAYER_A_CHAR;
  }
  if (round_over_bool || isRoundOver(game)) {
    roundOverWinningPlayer(game);
    initRound(game);
  } else {
    printGameState(game);
  }
  if (isGameOver(&(game->playerA), &(game->playerB))) {
    gameOverPrint(&(game->playerA), &(game->playerB));
    initGame(game);
  }
}

int drawCardsFromDeck(int card_group[CARD_GROUP_SIZE], GameData *game, int cards){
  for (int i=0;i<cards;i++){
    char card=deck[game->deck[game->deck_ptr++]];

    
  }
}

int takeCardFromMarket(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], int index){
  if (sum_cards_market(market)!=5) return -1;
  card_index card_type_index=getCardTypeIndex(market,index);
  if (card_type_index==camels){
    printf("Taking an individual camel is not allowed");
    return -1;
  }
  player_hand[card_type_index]++;
  market[card_type_index]--;
  return 0;
}

void cardSale(GameData *game,PlayerScore* player_score,int player_hand[CARD_GROUP_SIZE], char card_type, int no_cards) {
  int card_index=char_to_enum_lookup_table[card_type];
  int end = min(no_cards+game->resource_tk_ptrs[card_index],no_cards_lookup_table[card_index]);
  for (int token_idx=game->resource_tk_ptrs[card_index];token_idx<end;token_idx++){
    player_score->points+=diamond_tokens[token_idx];
  }
  player_score->no_goods_tokens+=end-game->resource_tk_ptrs[card_index];
  game->resource_tk_ptrs[card_index]=end;

  if (no_cards<=2) return;
  no_cards=min(2,no_cards-3);
  if (game->bonus_tk_ptrs[no_cards]<MAX_BONUS_TOKENS){
    player_score->points+=game->bonus_tk_arrays[no_cards][game->bonus_tk_ptrs[no_cards]];
    game->bonus_tk_ptrs[no_cards]++;
    player_score->no_bonus_tokens++;
  }
}

int cardExchange(int market[CARD_GROUP_SIZE], int player_hand[CARD_GROUP_SIZE], char *hand_idx, char *market_idx, int camels_no,int hand_idx_len,int market_goods_positions_len){
  //From the process_args function where this is called we know the strlens of the two char*s are valid (<6)
  int cards_from_hand[CARD_GROUP_SIZE]={0};
  for (int idx=0;idx<hand_idx_len;idx++){
    cards_from_hand[char_to_enum_lookup_table[hand_idx[idx]]]++;
  }
  cards_from_hand[camels]=camels_no;
  int cards_from_market[CARD_GROUP_SIZE]={0};
  for (int idx=0;idx<market_goods_positions_len;idx++){
    cards_from_market[char_to_enum_lookup_table[market_idx[idx]]]++;
  }
  
  //Check if the exchange from market includes both goods and camels
  if (cards_from_market[camels]){
    for (int card_type=0;card_type<RESOURCE_TYPES;card_type++){
      if (cards_from_market[card_type]!=0) return -1;
    }
  }
  for (int card_type=0;card_type<CARD_GROUP_SIZE;card_type++){
    market[card_type]+=cards_from_hand[card_type]-cards_from_market[card_type];
    player_hand[card_type]+=cards_from_market[card_type]-cards_from_hand[card_type];
  }
  return 0;
}

int isGameOver(PlayerScore *playerA, PlayerScore *playerB) {
  return playerA->seals == SEALS_TO_WIN || playerB->seals == SEALS_TO_WIN;
}

int isRoundOver(GameData *game) {
  return computeFinishedResources(game) == FINISHED_GOODS_LIMIT || game->deck_ptr==DECK_SIZE;
}

void gameOverPrint(PlayerScore *playerA, PlayerScore *playerB) {
  if (playerA->seals == SEALS_TO_WIN) {
    print_winning_trophy(PLAYER_A_CHAR);
  } else if (playerB->seals == SEALS_TO_WIN) {
    print_winning_trophy(PLAYER_B_CHAR);
  }
}

int roundOverWinningPlayer(GameData *game) {
  if (playerA->camels > playerB->camels) {
    playerA->points += CAMEL_TOKEN_VAL;
  } else if (playerB->camels > playerA->camels) {
    playerB->camels += CAMEL_TOKEN_VAL;
  }
  if (playerA->points > playerB->points) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_A_CHAR);
    }
    return;
  } else if (playerA->points < playerB->points) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_B_CHAR);
    }
    return;
  }
  if (playerA->no_bonus_tokens > playerB->no_bonus_tokens) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_A_CHAR);
    }
    return;
  } else if (playerA->no_bonus_tokens < playerB->no_bonus_tokens) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_B_CHAR);
    }
    return;
  }
  if (playerA->no_goods_tokens > playerB->no_goods_tokens) {
    playerA->seals++;
    game->turn_of = PLAYER_B_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_A_CHAR);
    }
    return;
  } else if (playerA->no_goods_tokens < playerB->no_goods_tokens) {
    playerB->seals++;
    game->turn_of = PLAYER_A_CHAR;
    if (isGameOver(playerA, playerB) == 0) {
      print_new_round_message(PLAYER_B_CHAR);
    }
    return;
  }
  printf("ERROR: IT WAS A DRAW! CONGRATULATIONS! THIS IS NORMALLY IMPOSSIBLE\n");
}

void roundOverPrint(GameData *game){

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
    game_state->bonus_3=MAX_BONUS_TOKENS-game_data->bonus_tk_ptrs;
    game_state->bonus_4=MAX_BONUS_TOKENS-game_data->bonus_4_ptr;
    game_state->bonus_5=MAX_BONUS_TOKENS-game_data->bonus_5_ptr;
    game_state->diamond=DIAMOND_TOKEN_SIZE-game_data->diamond_ptr;
    game_state->gold=GOLD_TOKEN_SIZE-game_data->gold_ptr;
    game_state->silver=SILVER_TOKEN_SIZE-game_data->silver_ptr;
    game_state->spice=SPICE_TOKEN_SIZE-game_data->spice_ptr;
    game_state->cloth=CLOTH_TOKEN_SIZE-game_data->cloth_ptr;
    game_state->leather=LEATHER_TOKEN_SIZE-game_data->leather_ptr;
    game_state->cards_in_deck=DECK_SIZE-game_data->deck_ptr;
}
