# Project structure
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin/obj


# Force Windows command interpreter
SHARED_LIB_PREFIX := lib
ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
    SHARED_LIB_EXT := dll
    EXE_EXT := .exe
    SHARED_LIB_FLAGS := -shared
    # Windows commands
    MKDIR = @if not exist $(subst /,\,$1) (echo Creating directory: $(subst /,\,$1) && md $(subst /,\,$1))
    RM = @if exist $(subst /,\,$1) (echo Deleting file: $(subst /,\,$1) && del /F /Q $(subst /,\,$1))
    RMDIR = @if exist $(subst /,\,$1) (echo Removing directory: $(subst /,\,$1) && rmdir /S /Q $(subst /,\,$1))
else
    # CFLAGS += -fsanitize=address
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LIB_EXT := dylib
        SHARED_LIB_FLAGS := -dynamiclib -install_name @rpath/$(LIB_NAME).$(SHARED_LIB_EXT)
    else
        SHARED_LIB_EXT := so
        SHARED_LIB_FLAGS := -shared
    endif
    EXE_EXT :=
    MKDIR = @if [ ! -d "$1" ]; then echo "Creating directory: $1" && mkdir -p "$1"; fi
    RM = @if [ -f "$1" ]; then echo "Deleting file: $1" && rm -f "$1"; fi
    RMDIR = @if [ -d "$1" ]; then echo "Removing directory: $1" && rm -rf "$1"; fi
endif

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -Werror -fPIC

LDFLAGS :=
INCLUDES := -I$(SRC_DIR) -Iinclude # Include directories

# Debug flags
DEBUG_FLAGS := -DDEBUG -g3 -O0

RELEASE_FLAGS := -O3 -march=native #Remove architecture for the general binaries

SHARED_LIB_FLAGS_OBJ := $(RELEASE_FLAGS)
SHARED_LIB_FLAGS += $(RELEASE_FLAGS)
# Library name and files
EXE_BASE := jaipur

LIB_BASE := $(EXE_BASE)
LIB_NAME := $(SHARED_LIB_PREFIX)$(LIB_BASE)
LIB_SOURCES := game_data.c ltables.c prints.c utils.c
LIB_OBJECTS := $(LIB_SOURCES:%.c=$(OBJ_DIR)/%.o)
LIB_DEPS := $(LIB_OBJECTS:%.o=%.d)
SHARED_LIB := $(LIB_NAME).$(SHARED_LIB_EXT)

# Executable name and files
# Executable name and files
EXE_NAME_DEBUG := $(EXE_BASE)_debug$(EXE_EXT)
EXE_NAME_RELEASE := $(EXE_BASE)_release$(EXE_EXT)
EXE_SOURCES := console_emulator.c $(LIB_SOURCES)
EXE_OBJECTS_DEBUG := $(EXE_SOURCES:%.c=$(OBJ_DIR)/%_debug.o)
EXE_OBJECTS_RELEASE := $(EXE_SOURCES:%.c=$(OBJ_DIR)/%_release.o)
EXE_DEPS_DEBUG := $(EXE_OBJECTS_DEBUG:%.o=%.d)
EXE_DEPS_RELEASE := $(EXE_OBJECTS_RELEASE:%.o=%.d)

# All source files are in src directory
VPATH := $(SRC_DIR)

# Targets
.PHONY: all clean directories print-debug debug release lib

all: lib debug release 

# debug: CFLAGS += $(DEBUG_FLAGS)
debug: directories $(BIN_DIR)/$(EXE_NAME_DEBUG)

# release: CFLAGS += $(RELEASE_FLAGS)
release: directories $(BIN_DIR)/$(EXE_NAME_RELEASE)

lib: CFLAGS += $(SHARED_LIB_FLAGS)
lib: directories $(BIN_DIR)/$(SHARED_LIB)

print-debug:
	@echo Library sources: $(LIB_SOURCES)
	@echo Library objects: $(LIB_OBJECTS)
	@echo Library deps: $(LIB_DEPS)
	@echo Executable sources: $(EXE_SOURCES)
	@echo Executable objects debug: $(EXE_OBJECTS_DEBUG)
	@echo Executable objects release: $(EXE_OBJECTS_RELEASE)

directories:
	$(call MKDIR,$(BIN_DIR))
	$(call MKDIR,$(OBJ_DIR))


# Compile source files to object files and generate dependencies
$(OBJ_DIR)/%.o: %.c
	@echo Compiling library objects $<...
	$(CC) $(CFLAGS) $(SHARED_LIB_FLAGS_OBJ) $(INCLUDES) -MMD -MP -c $< -o $@

# Compile source files to object files and generate dependencies (debug)
$(OBJ_DIR)/%_debug.o: %.c
	@echo Compiling debug $<...
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Compile source files to object files and generate dependencies (release)
$(OBJ_DIR)/%_release.o: %.c
	@echo Compiling release $<...
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Link debug executable
$(BIN_DIR)/$(EXE_NAME_DEBUG): $(EXE_OBJECTS_DEBUG)
	@echo Linking debug executable...
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $^ -o $@

# Link release executable
$(BIN_DIR)/$(EXE_NAME_RELEASE): $(EXE_OBJECTS_RELEASE)
	@echo Linking release executable...
	$(CC) $(RELEASE_FLAGS) $(CFLAGS) $^ -o $@

#Library
$(BIN_DIR)/$(SHARED_LIB): $(LIB_OBJECTS)
	@echo Creating shared library...
	$(CC) $(SHARED_LIB_FLAGS) $(CFLAGS) $^ -o $@

# Clean build files
clean:
	$(call RMDIR,$(BIN_DIR))

# Include dependency files
-include  $(LIB_DEPS) $(EXE_DEPS_DEBUG) $(EXE_DEPS_RELEASE)