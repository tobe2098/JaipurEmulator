#include "utils.h"

void randomize_int_array(int arr[], int size) {
  // Function to shuffle an array of integers using Fisher-Yates algorithm
  for (int i = size - 1; i > 0; i--) {
    int j    = rand() % (i + 1);
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
  }
}

void randomize_char_array(char arr[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j    = rand() % (i + 1);
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
  }
}

void randomize_void_array(void *arr, int arr_size, int type_size) {
  char temp[type_size];
  for (int i = arr_size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    memcpy(temp, (void *)((char *)arr + i * type_size), type_size);
    memcpy((void *)((char *)arr + i * type_size), (void *)((char *)arr + j * type_size), type_size);
    memcpy((void *)((char *)arr + j * type_size), temp, type_size);
  }
}

void find_data_path(char *data_path) {
  char exe_path[MAX_PATH];
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
const char *getPlayerName(char player) {
  if (player == PLAYER_A_CHAR) {
    return PLAYER_A;
  }
  if (player == PLAYER_B_CHAR) {
    return PLAYER_B;
  }
  return NULL;
}
