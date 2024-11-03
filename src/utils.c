#include "utils.h"

void randomizeArrayInt(int arr[], int start, int size) {
  // Function to shuffle an array of integers using Fisher-Yates algorithm, from a starting index to an ending index.
  // Starting index is included in the shuffling, the ending index is not (equivalent to size).
  for (int i = size - 1; i > start; i--) {
    int j    = (rand() % (i + 1 - start)) + start;
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
  }
}

void randomizeArrayChar(char arr[], int start, int size) {
  // Function to shuffle an array of chars using Fisher-Yates algorithm, from a starting index to an ending index.
  // Starting index is included in the shuffling, the ending index is not (equivalent to size).
  for (int i = size - 1; i > start; i--) {
    int j    = (rand() % (i + 1 - start)) + start;
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
  }
}

void randomize_void_array(void *arr, int arr_size, int type_size) {
  // Function to shuffle an array of chars using Fisher-Yates algorithm, from a starting index to an ending index.
  // Starting index is included in the shuffling, the ending index is not (equivalent to size).
  char temp[type_size];
  for (int i = arr_size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    memcpy(temp, (void *)((char *)arr + i * type_size), type_size);
    memcpy((void *)((char *)arr + i * type_size), (void *)((char *)arr + j * type_size), type_size);
    memcpy((void *)((char *)arr + j * type_size), temp, type_size);
  }
}

void find_data_path(char *data_path) {
  char exe_path[MAX_PATH - strlen("\\..\\data\\jaipur_game_state.json")];
  int  size = sizeof(exe_path);
  // Function to get the executable path based on the operating system
#ifdef _WIN32
  // On Windows
  if (GetModuleFileName(NULL, exe_path, size) == 0) {
    printf("Error: Could not get executable path.\n");
  }

  // Remove the executable name from the path
  char *last_backslash = strrchr(exe_path, '\\');
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
  char *last_slash = strrchr(exe_path, '/');
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
const char *getPlayerName(int player) {
  if (player == PLAYER_A_NUM) {
    return PLAYER_A;
  }
  if (player == PLAYER_B_NUM) {
    return PLAYER_B;
  }
  return NULL;
}

void printErrors(int flags) {
  if (flags & TOO_FEW_ARGS_FLAG) {
    printf("Error: Too few arguments.\n");
  }
  if (flags & MIXING_GOODS_CAMELS) {
    printf("Error: You are attempting to trade cards for both camels and goods.\n");
  }
  if (flags & DATA_CORRUPTED_FLAG) {
    printf("Error: The data has been corrupted, it does not fit the constraints.\n");
    printf("Data was partially corrupted, use `--reset` to restart the game or manually correct the json.\n");
    printf("Input into the template json file your data manually as an alternative.\n");
    // perror("Data could not be read:");
  }
  if (flags & TOO_FEW_C_MARKET_FLAG) {
    printf("Error: There are not enough cards in the market.\n");
  }
  if (flags & TOO_FEW_C_HAND_FLAG) {
    printf("Error: You do not have enough cards in your hand.\n");
  }
  if (flags & TOO_MANY_C_MARKET_FLAG) {
    printf("Error: There are too many cards in the market.\n");
  }
  if (flags & TOO_MANY_C_HAND_FLAG) {
    printf("Error: Your hand is full.\n");
  }
  if (flags & NOT_ALLOWED_FLAG) {
    printf("Error: The action is not allowed.\n");
  }
  if (flags & MISSING_CARD_FLAG) {
    printf("Error: The card is not in the market.\n");
  }
  if (flags & ARG_OVERFLOW_FLAG) {
    printf("Error: Input less than 5 cards for the market.\n");
  }
  if (flags & NO_CAMELS) {
    printf("Error: There are no camels in the market.\n");
  }
  if (flags & ARGS_MISS_MATCH_FLAG) {
    printf("Error: The number of exchanged cards does not match.\n");
  }
  if (flags & DATA_NOT_INIT_FLAG) {
    printf("Error: The data was not properly initialized.\n");
  }
  if (flags & TOO_FEW_CARDS_SALE) {
    printf("Error: Cannot sell less than 1 card.\n");
  }
}