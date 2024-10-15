# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Library name
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIB_NAME = libmylib.so
    LDFLAGS += -shared
endif
ifeq ($(UNAME_S),Darwin)
    LIB_NAME = libmylib.dylib
    LDFLAGS += -dynamiclib
endif
ifeq ($(OS),Windows_NT)
    LIB_NAME = mylib.dll
    LDFLAGS += -shared
endif

# Executable name
EXE_NAME = myprogram

# Targets
all: directories $(BIN_DIR)/$(LIB_NAME) $(BIN_DIR)/$(EXE_NAME)

directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create shared library
$(BIN_DIR)/$(LIB_NAME): $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))
	$(CC) $(LDFLAGS) $^ -o $@

# Create executable
$(BIN_DIR)/$(EXE_NAME): $(OBJ_FILES)
	$(CC) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean directories

# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Library-specific source files (add your specific files here)
LIB_SRC_FILES = $(SRC_DIR)/file1.c $(SRC_DIR)/file2.c
LIB_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC_FILES))

# Library name
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIB_NAME = libmylib.so
    LDFLAGS += -shared
endif
ifeq ($(UNAME_S),Darwin)
    LIB_NAME = libmylib.dylib
    LDFLAGS += -dynamiclib
endif
ifeq ($(OS),Windows_NT)
    LIB_NAME = mylib.dll
    LDFLAGS += -shared
endif

# Executable name
EXE_NAME = myprogram

# Targets
all: directories $(BIN_DIR)/$(LIB_NAME) $(BIN_DIR)/$(EXE_NAME)

directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create shared library (only with specified object files)
$(BIN_DIR)/$(LIB_NAME): $(LIB_OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

# Create executable
$(BIN_DIR)/$(EXE_NAME): $(OBJ_FILES)
	$(CC) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean directories