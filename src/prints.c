#include "prints.h"

void printGoodsTokenArray(char name, const int *array, int size, int cutoff) {
  printf("<Goods> Remaining %c tokens:  \t", name);
  for (int i = 0; i < size; i++) {
    if (i < cutoff) {
      printf(" * ");  // Three spaces
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
    for (int card_it = 0; card_it < card_group[card_type]; card_it++) {
      if (card_counter >= 7) {
        break;
      }
      char cardChar = enum_to_char_lookup_table[card_type];
      snprintf(line_array[0][card_counter], sizeof(line_array[0][card_counter]), "  _____ ");
      snprintf(line_array[1][card_counter], sizeof(line_array[1][card_counter]), " |%c    |", cardChar);
      snprintf(line_array[2][card_counter], sizeof(line_array[2][card_counter]), " |     |");
      snprintf(line_array[3][card_counter], sizeof(line_array[3][card_counter]), " |    %c|", cardChar);
      snprintf(line_array[4][card_counter], sizeof(line_array[4][card_counter]), "  -----");
      card_counter++;
    }
  }
  for (int line_buffer = 0; line_buffer < 5; line_buffer++) {
    for (int card = 0; card < card_counter; card++) {
      printf("%s", line_array[line_buffer][card]);
    }
    printf("\n");
  }
}
void print_winning_trophy(int player) {
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

void print_welcome_message() {
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

void print_version() {
  printf("Jaipur Game Tracker %s\n", PROJECT_VER);
  printf("Built for %s\n", OS_NAME);
  printf("%s\n", LICENSE_VERSION);
  printf("This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law.\n");
}

void print_new_round_message(int player) {
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
void print_help() {
  // Finish after everything else is done
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
  printf("                                Example: --sell d 3\n");
  printf("Card types and their respective characters:\n");
  printf("Diamonds: d, \n");
  printf("REMEMBER: Indexing on position is 0-based. \n");
}

void print_rules() {
  printf("Notes on rules:\n");
  printf("1. The game ends when there are no cards left in the draw pile or the tokens of three resources are finished\n");
  printf("2. Cards from hand and from the herd can be traded with the market\n");
  printf("3. When trading you can only take either goods or camels from the market, not both\n");
  printf("3. \n");
}