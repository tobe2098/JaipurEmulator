# Project structure
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin/obj

# Detect OS and set platform-specific variables
ifeq ($(OS),Windows_NT)
    SHARED_LIB_EXT := dll
    SHARED_LIB_PREFIX :=
    EXE_EXT := .exe
    RM := del /Q /S
    RMDIR := rmdir /S /Q
    MKDIR := mkdir
    SHARED_LIB_FLAGS := -shared
    # Fix directory creation for Windows
    MKDIR_P = @cmd /c if not exist "$1" mkdir "$1"
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LIB_EXT := dylib
        SHARED_LIB_FLAGS := -dynamiclib -install_name @rpath/$(SHARED_LIB_PREFIX)$(LIB_NAME).$(SHARED_LIB_EXT)
    else
        SHARED_LIB_EXT := so
        SHARED_LIB_FLAGS := -shared -fPIC
    endif
    SHARED_LIB_PREFIX := lib
    EXE_EXT :=
    RM := rm -f
    RMDIR := rm -rf
    MKDIR := mkdir -p
    MKDIR_P = mkdir -p "$1"
endif

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -O2 -fPIC
INCLUDES := -I$(SRC_DIR)

# Library name and files
LIB_NAME := gamelib
LIB_SOURCES := game_data.c ltables.c prints.c utils.c
LIB_OBJECTS := $(LIB_SOURCES:%.c=$(OBJ_DIR)/%.o)
LIB_DEPS := $(LIB_OBJECTS:%.o=%.d)
SHARED_LIB := $(SHARED_LIB_PREFIX)$(LIB_NAME).$(SHARED_LIB_EXT)

# Executable name and files
EXE_NAME := console_emulator$(EXE_EXT)
EXE_SOURCES := console_emulator.c
EXE_OBJECTS := $(EXE_SOURCES:%.c=$(OBJ_DIR)/%.o)
EXE_DEPS := $(EXE_OBJECTS:%.o=%.d)

# All source files are in src directory
VPATH := $(SRC_DIR)

# Targets
.PHONY: all clean directories print-debug

all: directories $(BIN_DIR)/$(EXE_NAME) $(BIN_DIR)/$(SHARED_LIB)

print-debug:
	@echo "Library sources: $(LIB_SOURCES)"
	@echo "Library objects: $(LIB_OBJECTS)"
	@echo "Library deps: $(LIB_DEPS)"
	@echo "Executable sources: $(EXE_SOURCES)"
	@echo "Executable objects: $(EXE_OBJECTS)"
	@echo "Executable deps: $(EXE_DEPS)"

directories:
ifeq ($(OS),Windows_NT)
	$(call MKDIR_P,$(subst /,\,$(BIN_DIR)))
	$(call MKDIR_P,$(subst /,\,$(OBJ_DIR)))
else
	$(call MKDIR_P,$(BIN_DIR))
	$(call MKDIR_P,$(OBJ_DIR))
endif

# Compile source files to object files and generate dependencies
$(OBJ_DIR)/%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Link executable
$(BIN_DIR)/$(EXE_NAME): $(EXE_OBJECTS) $(LIB_OBJECTS)
	@echo "Linking executable..."
	$(CC) $(CFLAGS) $^ -o $@

# Create shared library
$(BIN_DIR)/$(SHARED_LIB): $(LIB_OBJECTS)
	@echo "Creating shared library..."
	$(CC) $(SHARED_LIB_FLAGS) $(CFLAGS) $^ -o $@

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(subst /,\,$(BIN_DIR))" $(RMDIR) "$(subst /,\,$(BIN_DIR))"
else
	$(RMDIR) $(BIN_DIR)
endif

# Include dependency files
-include $(LIB_DEPS) $(EXE_DEPS)