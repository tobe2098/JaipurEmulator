#include "utils.h"

void randomize_index_array(int arr[], int size) {
  // Function to shuffle an array of integers using Fisher-Yates algorithm
  for (int i = size - 1; i > 0; i--) {
    int j    = rand() % (i + 1);
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
  }
}

void print_array_goods(char* name, const int* array, int size, int cutoff) {
  printf("<Goods> Remaining %s tokens:  \t", name);
  for (int i = 0; i < size; i++) {
    if (i < cutoff) {
      printf(" * ");  // Three spaces
    } else {
      printf(" %i ", array[i]);
    }
  }
  printf("\n");
}
void print_player_wins(char player) {
  if (player == 'A') {
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
  } else if (player == 'B') {
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
void printCardGroup(int *card_group,int bool_camel){
  char line_array[5][8][9];
  int card_counter=0;
  // char line1[8][11];
  // char line2[8][11];
  // char line3[8][11];
  // char line4[8][11];
  // char line5[8][11];
  for (int card_type=0;card_type<(bool_camel?CARD_GROUP_SIZE:camels);card_type++){
    for (int card_it=0;card_it<card_group[card_type];card_it++){
      if (card_counter>=7) break;
      char cardChar=enum_to_char_lookup_table[card_type];
      snprintf(line_array[0][card_counter],sizeof(line_array[0][card_counter]),"  _____ ");
      snprintf(line_array[1][card_counter],sizeof(line_array[1][card_counter])," |%c    |",cardChar);
      snprintf(line_array[2][card_counter],sizeof(line_array[2][card_counter])," |     |");
      snprintf(line_array[3][card_counter],sizeof(line_array[3][card_counter])," |    %c|",cardChar);
      snprintf(line_array[4][card_counter],sizeof(line_array[4][card_counter]),"  -----");
      card_counter++;
    }
  }
  for (int line_buffer=0;line_buffer<5;line_buffer++){
    for (int card=0;card<card_counter;card++){
      printf("%s",line_array[line_buffer][card]);
    }
    printf("\n");
  }
}


void find_data_path(char *data_path)
{
    char exe_path[MAX_PATH];
    int size = sizeof(exe_path);
    // Function to get the executable path based on the operating system
#ifdef _WIN32
  // On Windows
  if (GetModuleFileName(NULL, exe_path, size) == 0) {
    printf("Error: Could not get executable path.\n");
  }

  // Remove the executable name from the path
  char* last_backslash = strrchr(exe_path, '\\');
  if (last_backslash != NULL) {
    *last_backslash = '\0';  // Remove the executable name
  }

#elif defined(__linux__) || defined(__APPLE__)
  // On Linux and macOS
  ssize_t len;

#ifdef __linux__
  // Linux-specific method to get executable path
  len = readlink("/proc/self/exe", exe_path, size - 1);
#elif defined(__APPLE__)
  // macOS-specific method to get executable path
  uint32_t bufsize = (uint32_t)size;
  if (_NSGetExecutablePath(exe_path, &bufsize) != 0) {
    printf("Error: Buffer size too small; increase size.\n");
    return;
  }
  len = strlen(exe_path);
#endif

  if (len == -1) {
    perror("Error getting executable path");
  } else {
    exe_path[len] = '\0';  // Null-terminate the path
  }

  // Remove the executable name from the path
  char* last_slash = strrchr(exe_path, '/');
  if (last_slash != NULL) {
    *last_slash = '\0';  // Remove the executable name
  }

#endif
  // Construct the relative path to the file
#ifdef _WIN32
  snprintf(data_path, MAX_PATH, "%s\\..\\data\\jaipur_game_state.json", exe_path);
#else
  snprintf(data_path, MAX_PATH, "%s/../data/jaipur_game_state.json", exe_path);
#endif
}
void print_winning_trophy(char player) {
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

  print_player_wins(player);
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

void print_new_round_message(char player) {
  print_player_wins(player);
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
