#include "prints.h"

void printGoodsTokenArray(char name, const int *array, int size, int cutoff) {
  printf("<Goods> Remaining [%c] tokens:  \t", name);
  for (int i = 0; i < size; i++) {
    if (i < cutoff) {
      printf(" %c ", TOKEN_USED_CHAR);  // Three spaces
    } else {
      printf(" %i ", array[i]);
    }
  }
  printf("\n");
}
void printWinner(int player) {
  if (player == PLAYER_A_NUM) {
    printf("      ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      \n");
    printf("      ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗     \n");
    printf("      ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     \n");
    printf("      ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     \n");
    printf("      ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     \n");
    printf("      ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     \n");
    printf("                                                            \n");
    printf("       █████╗     ██╗    ██╗██╗███╗   ██╗███████╗██╗        \n");
    printf("      ██╔══██╗    ██║    ██║██║████╗  ██║██╔════╝██║        \n");
    printf("      ███████║    ██║ █╗ ██║██║██╔██╗ ██║███████╗██║        \n");
    printf("      ██╔══██║    ██║███╗██║██║██║╚██╗██║╚════██║╚═╝        \n");
    printf("      ██║  ██║    ╚███╔███╔╝██║██║ ╚████║███████║██╗        \n");
    printf("      ╚═╝  ╚═╝     ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝        \n");
  } else if (player == PLAYER_B_NUM) {
    printf("      ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      \n");
    printf("      ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗     \n");
    printf("      ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     \n");
    printf("      ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     \n");
    printf("      ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     \n");
    printf("      ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     \n");
    printf("                                                            \n");
    printf("      ██████╗     ██╗    ██╗██╗███╗   ██╗███████╗██╗        \n");
    printf("      ██╔══██╗    ██║    ██║██║████╗  ██║██╔════╝██║        \n");
    printf("      ██████╔╝    ██║ █╗ ██║██║██╔██╗ ██║███████╗██║        \n");
    printf("      ██╔══██╗    ██║███╗██║██║██║╚██╗██║╚════██║╚═╝        \n");
    printf("      ██████╔╝    ╚███╔███╔╝██║██║ ╚████║███████║██╗        \n");
    printf("      ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝        \n");
  }
}

void printCardGroup(int *card_group, int bool_camel) {
  char line_array[5][8][9];
  int  card_counter = 0;
  // char line1[8][11];
  // char line2[8][11];
  // char line3[8][11];
  // char line4[8][11];
  // char line5[8][11];
  for (int card_type = 0; card_type < (bool_camel ? CARD_GROUP_SIZE : camels); card_type++) {
    for (int card_it = 0; card_it < card_group[(int)card_type]; card_it++) {
      if (card_counter >= 7) {
        break;
      }
      char cardChar = enum_to_char_lookup_table[(int)card_type];
      snprintf(line_array[0][card_counter], sizeof(line_array[0][card_counter]), "  _____ ");
      snprintf(line_array[1][card_counter], sizeof(line_array[1][card_counter]), " |%c    |", cardChar);
      snprintf(line_array[2][card_counter], sizeof(line_array[2][card_counter]), " |     |");
      snprintf(line_array[3][card_counter], sizeof(line_array[3][card_counter]), " |    %c|", cardChar);
      snprintf(line_array[4][card_counter], sizeof(line_array[4][card_counter]), "  ----- ");
      card_counter++;
    }
  }
  if (card_counter == 0) {
    printf(".------------------------------------------------------------------.\n");
    printf("| _   _                 _   _                            _         |\n");
    printf("|| | | | __ _ _ __   __| | (_)___    ___ _ __ ___  _ __ | |_ _   _ |\n");
    printf("|| |_| |/ _` | '_ \\ / _` | | / __|  / _ \\ '_ ` _ \\| '_ \\| __| | | ||\n");
    printf("||  _  | (_| | | | | (_| | | \\__ \\ |  __/ | | | | | |_) | |_| |_| ||\n");
    printf("||_| |_|\\__,_|_| |_|\\__,_| |_|___/  \\___|_| |_| |_| .__/ \\__|\\__, ||\n");
    printf("|                                                 |_|        |___/ |\n");
    printf("'------------------------------------------------------------------'\n");
    printf("\n");
    return;
  }
  for (int line_buffer = 0; line_buffer < 5; line_buffer++) {
    for (int card = 0; card < card_counter; card++) {
      printf("%s", line_array[line_buffer][(int)card]);
    }
    printf("\n");
  }
}
void printWinningTrophy(int player) {
  printf("                        xxxxxxXXXxxxXx                         \n");
  printf("                  xxxXXxxxxxxxxxxxXxxxxxxxxx                   \n");
  printf("                xxxxxxxxxxxxxx+++xxxxxxxxxxxxxx                \n");
  printf("             xxxxxXxxxxxxx+++xXXxx++xxxxxxxXxxxxxX             \n");
  printf("          xxxxxxxxxxxxx++xxxxXXXXXXxxx+++xxxxxxxxxxx           \n");
  printf("        xXxxxxxXxx+++xxxxxxXXXXxxxXXXXXXx++++xXXxxxxXx         \n");
  printf("       XxxxXxxx++xxXxxxxxxXXXXxXXxxxXXXXxxXXx++xxxxxxxxX       \n");
  printf("     xxXxxxx+xxxXxXxx+;:+xXXXXXxxxxXXxxXxxxXXXXxx++xxxxxx      \n");
  printf("    xxxxx+xXxxxXX+;;+xXX$XXXXxxxxXXXxxxxXXx;;xXXxxXXxxxxxx     \n");
  printf("   xxxxx++xxXx;;;xXXXXxxxXXXxXXXXXXxxXXXXXXXx;;;+xXxx+xxxxx    \n");
  printf("  xxxxxx+xxxx;;+XXxxXXXxxxxXXXXXXXXXXXxxXxxxx+;;;+Xxx++xxxxX   \n");
  printf("  xXxxx++XxX+;;xXXxxxXXXXxxxxXXXXXXXxxxXxxxxXx;;;;xXxx+xxxxXx  \n");
  printf(" xxxxxx+xxxx;;+X$$XXXxxX$XxxxxxXXXXXxXXXxxxxXX+;;;+Xxx++xxxXx  \n");
  printf(" XxxxXx+Xxxx;;;X$XXX$XXxxXXXXXXXXXXxXXXxxxxxXXx;;;+xxXx+XXxxxXX\n");
  printf("xxxXxx++xxX+;;;;x$$$XXX$XXxxXX$$XxxXXXxXXXXX$x;;;;;xXxx+xxXXxxx\n");
  printf("xxxxxx+xxXx;;++++x$$$$XXxXXXXXXXXXXXxxXXX$$X+;+;++;+xxXx+xxXxxx\n");
  printf("Xxxxx++xxX++++++++xX$XXX$$XXXXXXXXX$$$$$$Xx+++++++++xXxx+xxxxxx\n");
  printf("xxxxx+xXxx+++++++++xX$XX$XXXXXx;+XXXX$$$x++++++++++++xxX++xxxxx\n");
  printf("xxxXx+xxXx+++++++++++X$$$XXXxxx++xxxx$X++++++++++++++Xxxx+XXxxx\n");
  printf("xXxx++xxx++++++++++++xxX$Xxx+xXx+++++XX+++++++++++++;+Xxx++xXXX\n");
  printf("xxxx+xXxXx;++++++++++xxX$X+++xXx++++xXX++++++++++++++xxxXxxXxxx\n");
  printf(" xxxx+xXxxX++xx+++xxxxxX$XXX$$$$$$$XX$Xxx+++xxx++++xXxXX++xxxx \n");
  printf(" xxxxxx+xxxxx+x+++xxxX$$$$$$XXXXXXX$$$$$Xx++xxxx++xxxXx+xxxXx  \n");
  printf("  xxxxxx+xxxXx++++xxX$$$$$$$$XxxxxX$$$XXXx++xxx++Xxxx++xxxxXx  \n");
  printf("   Xxxxxxx+XXxXx;+++XXX$$$$$$$$$$$$$$X+;+++++;+xXxXx+xxxxxxX   \n");
  printf("    xxxXxxx+xxxxX++xxXXX$$$$$$$$$XXX$$xx+++++xXxxX++xxxxxXx    \n");
  printf("     xxxxxxX++xxxXxxxxXX$$$$$$X$$$$XXXX+;;++xxxxx+xxxxxxxX     \n");
  printf("      xxxXxxxx+xXxxXXxxX$$$$$$$XX$$$$$$x;;+XxxX++xxxXXxxx      \n");
  printf("       xxXxxxxx++xxxXXxXX$$$$$XxxxXXXXxxxxXxXx+xxxxxxxx        \n");
  printf("         xxxxxxx++xXXxXXXXXXXXxxxxxxxxXxxxXx++xxxxxxx          \n");
  printf("           xxxxXxx+++xxxxxxxxx+xxxxxxxxxxx+++xxxxxx            \n");
  printf("              xxxxxxxXxxxxxxxxxxxxXxxxxxxxxxxxxxx              \n");
  printf("                xXxXxxxXXxxxxxxXXxxxXxxxxxxxXX                 \n");
  printf("                    xXXxxxxxXxxxxXXxxxxxxx                     \n");
  (void)getchar();
  printWinner(player);
}

void printWelcomeMessage() {
  printf(":::+++;;;;;:.....:++++;+:;:..::::::::::...........:::;X:::::;::\n");
  printf("::;+;+;;::;:.....:;+++;+:;;:.:;:;:.:..............::.:$++;x+:::\n");
  printf("+;++;;;::::....;;;;;;;;;;;;;;;;;;::::................+$+;;;x:..\n");
  printf("++;+++;;;;;;;;;;;;;;;;;;;;;;;;;;;:::::::::...........$$&&X;;X;.\n");
  printf(";;;::;;;;;;;;;;;X&&&&&Xx&&$&X:$&&&X::::::::::.......x$XXx+XX$..\n");
  printf(";::::::;;;;;;;;+&$$$$x:$$$X$+:XXXX$;:..::::::.......+&$$$$X++;.\n");
  printf(";;;;;;;;;;;;;;;+&$$$$:X&&&&&;+$XX$&&&+:::::::::.....$$&&xX++x;.\n");
  printf(";;;;;;;;;;;;;x&&&&&&X+&&&&&&+x&&&$&$$&&&;::::::::::;$xX&:+X$x..\n");
  printf("+;;;;;;++++;X&&&&$$&$X$$$$$&Xx$XX$&$&&&;:::::::::::X+xX$..x....\n");
  printf("x+;;;;++++++&&&&&&&&$&&&&&&&X$&&&&&x&&X:;;;;;;;;;;x+xxX$;+X;;;;\n");
  printf("x+;;;;++++++&&$&&&&$$&&&&&&&$&&&&&&x&&&;;+;;;+;;+&x+xx$x;Xx;;++\n");
  printf("x+;;;;+++XXX&&$$$&&$x&&&&&&&$&&&$Xxx&&&&&&X++xX$X++++X$;+XX;;++\n");
  printf("x+;;;;;x&X+x&$$$$$$xX&$$$$x&&$&X++;+$&&&&&x++XXX+;;+x$x;;xX;;;;\n");
  printf(";:::;:x&X++x&&&&&&&&$$&&&x+$&$Xx+;;+$xxX&$+++XXx+;;+XX;;;Xx;;;;\n");
  printf("+;;;+$&x:++X&&&&&&&&&$&&&$$$&$X&&&&&&$xx&x;XX$XX++X&x;;;;$+;;;;\n");
  printf("+;;+&&x;;xx$&$$$&&&&&&&&&&&&&$X$$$$$&&Xx&++X&$$$$&&+;++;;&;;;+x\n");
  printf("              ██╗ █████╗ ██╗ ██████╗ ██╗   ██╗██████╗          \n");
  printf("              ██║██╔══██╗██║ ██╔══██╗██║   ██║██╔══██╗         \n");
  printf("              ██║███████║██║ ██████╔╝██║   ██║██████╔╝         \n");
  printf("         ██   ██║██╔══██║██║ ██╔═══╝ ██║   ██║██╔══██╗         \n");
  printf("███████╗ ╚█████╔╝██║  ██║██║ ██║     ╚██████╔╝██║  ██║ ███████╗\n");
  printf("╚══════╝  ╚════╝ ╚═╝  ╚═╝╚═╝ ╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚══════╝\n");
}

void printVersion() {
  printf("Jaipur Game Emulator %s\n", PROJECT_VER);
  printf("Built for %s\n", OS_NAME);
  printf("%s\n", LICENSE_VERSION);
  printf("This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law.\n");
}

void printNewRoundMessage(int player) {
  printWinner(player);
  (void)getchar();
  printf("////////////////////////////////////////////////////////////\n");
  printf("//            ███╗   ██╗███████╗██╗  ██╗████████╗         //\n");
  printf("//            ████╗  ██║██╔════╝╚██╗██╔╝╚══██╔══╝         //\n");
  printf("//█████╗█████╗██╔██╗ ██║█████╗   ╚███╔╝    ██║█████╗█████╗//\n");
  printf("//╚════╝╚════╝██║╚██╗██║██╔══╝   ██╔██╗    ██║╚════╝╚════╝//\n");
  printf("//            ██║ ╚████║███████╗██╔╝ ██╗   ██║            //\n");
  printf("//            ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝   ╚═╝            //\n");
  printf("//                                                        //\n");
  printf("//      ██████╗  ██████╗ ██╗   ██╗███╗   ██╗██████╗       //\n");
  printf("//      ██╔══██╗██╔═══██╗██║   ██║████╗  ██║██╔══██╗      //\n");
  printf("//█████╗██████╔╝██║   ██║██║   ██║██╔██╗ ██║██║  ██║█████╗//\n");
  printf("//╚════╝██╔══██╗██║   ██║██║   ██║██║╚██╗██║██║  ██║╚════╝//\n");
  printf("//      ██║  ██║╚██████╔╝╚██████╔╝██║ ╚████║██████╔╝      //\n");
  printf("//      ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═════╝       //\n");
  printf("////////////////////////////////////////////////////////////\n");
  // printf("██████╗  ██████╗ ██╗   ██╗███╗   ██╗██████╗                  \n");
  // printf("██╔══██╗██╔═══██╗██║   ██║████╗  ██║██╔══██╗██╗              \n");
  // printf("██████╔╝██║   ██║██║   ██║██╔██╗ ██║██║  ██║╚═╝              \n");
  // printf("██╔══██╗██║   ██║██║   ██║██║╚██╗██║██║  ██║██╗              \n");
  // printf("██║  ██║╚██████╔╝╚██████╔╝██║ ╚████║██████╔╝╚═╝              \n");
  // printf("╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═════╝                  \n");

  // printf(" ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██╗   ██╗███████╗██████╗ \n");
  // printf("██╔════╝██╔═══██╗████╗  ██║██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
  // printf("██║     ██║   ██║██╔██╗ ██║██║   ██║██║   ██║█████╗  ██████╔╝\n");
  // printf("██║     ██║   ██║██║╚██╗██║██║▄▄ ██║██║   ██║██╔══╝  ██╔══██╗\n");
  // printf("╚██████╗╚██████╔╝██║ ╚████║╚██████╔╝╚██████╔╝███████╗██║  ██║\n");
  // printf(" ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚══▀▀═╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝\n");
  // printf("                                                             \n");
  // printf("████████╗██╗  ██╗███████╗                                    \n");
  // printf("╚══██╔══╝██║  ██║██╔════╝                                    \n");
  // printf("   ██║   ███████║█████╗                                      \n");
  // printf("   ██║   ██╔══██║██╔══╝                                      \n");
  // printf("   ██║   ██║  ██║███████╗                                    \n");
  // printf("   ╚═╝   ╚═╝  ╚═╝╚══════╝                                    \n");
  // printf("                                                             \n");
  // printf("███╗   ███╗ █████╗ ██████╗ ██╗  ██╗███████╗████████╗██╗      \n");
  // printf("████╗ ████║██╔══██╗██╔══██╗██║ ██╔╝██╔════╝╚══██╔══╝██║      \n");
  // printf("██╔████╔██║███████║██████╔╝█████╔╝ █████╗     ██║   ██║      \n");
  // printf("██║╚██╔╝██║██╔══██║██╔══██╗██╔═██╗ ██╔══╝     ██║   ╚═╝      \n");
  // printf("██║ ╚═╝ ██║██║  ██║██║  ██║██║  ██╗███████╗   ██║   ██╗      \n");
  // printf("╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝      \n");
}
void printHelp() {
  // Finish after everything else is done
  printf("Usage: ./program [options]\n");
  printf("Options:\n");
  printf("  --help||-h                     Show this help message\n");
  printf("  --version||-v                  Show the version of the executable\n");
  printf("  --rules||-u                    Show the game's rules\n");
  printf("  --reset||-r                    Restart the game from scratch\n");
  // printf("  --state   -s                    Print the current state of the game. Default argument.\n");
  printf("  --take||-t  <market-card>      Example: -t g\n");
  printf("    > Take a card from the market. The market draws a card from the deck. Camels not allowed.\n\n");
  printf("  --camels||c                    Example: -c 3\n");
  printf("    >Take all camels from the market. The market draws as many cards\n\n");
  printf("  --sell <card-type> <value>     Example: --sell d 3\n");
  printf("    >Sell a number of goods of the specified type. Earn points from them.\n\n");
  printf("  --exchange||-e <hand-cards> <camels> <market-cards> \n");
  printf("                                 Example: -e dg 1 ppp\n");
  printf("    >Change cards in hand and camels for cards in market. Number has to be equal.\n\n");
  printf("Card types and their respective characters:\n");
  printf("Diamonds: [%c], golds: [%c], Silvers: [%c], Spice: [%c], Cloth: [%c], Leather: [%c], Camels: [%c]\n", DIAMOND_CHAR, GOLD_CHAR,
         SILVER_CHAR, SPICE_CHAR, CLOTH_CHAR, LEATHER_CHAR, CAMEL_CHAR);
}

void printRules() {
  printf("\nNotes:\n");
  printf("- Goods cards are non-camel cards.\n");
  printf("- A player cannot have more than 7 goods cards in hand.\n");
  printf("- Each player starts with five cards. The face-down deck starts with 40 cards.\n");
  printf("\nRules:\n");
  printf("\n1. The game starts with three camels and two other cards in the market.\n");
  printf("\n2. On your turn you can either trade with the market or sell goods in your hand.\n");
  printf("  -Trade: Cards from hand and from the camel herd (your camels) can be traded with the market's goods cards.\n");
  printf("  -Trade: Take a single goods card from the market. The market draws a card from the deck.\n");
  printf("  -Trade: Take all the camels. The market draws as many cards from the deck.\n");
  printf("  -Sell: Sell a non-zero number of cards from your hand. Receive points depending on the highest-value tokens remaining.\n");
  printf("  *If you sell 3 or more cards you receive a random bonus token according to that number if there are any remaining.\n");
  printf("  *Bonus tokens give 1,2 or 3 points if you sold 3 cards, 4,5 or 6 if 4 cards or 7,8 or 9 if 5 cards.\n");
  printf(
    "\n3. The game ends when there are no cards left in the draw pile when attempting to draw or the tokens of three goods are "
    "finished.\n");
  printf("\n\n");
}