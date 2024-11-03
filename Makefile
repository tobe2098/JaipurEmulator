# Project structure
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin/obj

# Force Windows command interpreter
ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
    SHARED_LIB_EXT := dll
    SHARED_LIB_PREFIX :=
    EXE_EXT := .exe
    SHARED_LIB_FLAGS := -shared
    # Windows commands
    MKDIR = if not exist $(subst /,\,$1) md $(subst /,\,$1)
    RM = del /F /Q $(subst /,\,$1)
    RMDIR = if exist $(subst /,\,$1) rmdir /S /Q $(subst /,\,$1)
else
    SHARED_LIB_EXT := so
    SHARED_LIB_PREFIX := lib
    EXE_EXT :=
    SHARED_LIB_FLAGS := -shared -fPIC
    MKDIR = mkdir -p $1
    RM = rm -f $1
    RMDIR = rm -rf $1
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
	@echo Library sources: $(LIB_SOURCES)
	@echo Library objects: $(LIB_OBJECTS)
	@echo Library deps: $(LIB_DEPS)
	@echo Executable sources: $(EXE_SOURCES)
	@echo Executable objects: $(EXE_OBJECTS)
	@echo Executable deps: $(EXE_DEPS)

directories:
	$(call MKDIR,$(BIN_DIR))
	$(call MKDIR,$(OBJ_DIR))

# Compile source files to object files and generate dependencies
$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<...
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Link executable
$(BIN_DIR)/$(EXE_NAME): $(EXE_OBJECTS) $(LIB_OBJECTS)
	@echo Linking executable...
	$(CC) $(CFLAGS) $^ -o $@

# Create shared library
$(BIN_DIR)/$(SHARED_LIB): $(LIB_OBJECTS)
	@echo Creating shared library...
	$(CC) $(SHARED_LIB_FLAGS) $(CFLAGS) $^ -o $@

# Clean build files
clean:
	$(call RMDIR,$(BIN_DIR))

# Include dependency files
-include $(LIB_DEPS) $(EXE_DEPS)