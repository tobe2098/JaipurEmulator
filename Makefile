# Project structure
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin/obj

CFLAGS := -Wall -Wextra -Werror -fPIC

# Force Windows command interpreter
ifeq ($(OS),Windows_NT)
    SHELL := cmd.exe
    SHARED_LIB_EXT := dll
    SHARED_LIB_PREFIX :=
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
        SHARED_LIB_FLAGS := -dynamiclib -install_name @rpath/$(SHARED_LIB_PREFIX)$(LIB_NAME).$(SHARED_LIB_EXT)
    else
        SHARED_LIB_EXT := so
        SHARED_LIB_FLAGS := -shared
    endif
    SHARED_LIB_PREFIX := lib
    EXE_EXT :=
    #MKDIR = mkdir -p $1
    MKDIR = @if [ ! -d "$1" ]; then echo "Creating directory: $1" && mkdir -p "$1"; fi
    #RM = rm -f $1
    RM = @if [ -f "$1" ]; then echo "Deleting file: $1" && rm -f "$1"; fi
    #RMDIR = rm -rf $1
    RMDIR = @if [ -d "$1" ]; then echo "Removing directory: $1" && rm -rf "$1"; fi
endif

# Compiler settings
CC := gcc

LDFLAGS :=
INCLUDES := -I$(SRC_DIR) -Iinclude # Include directories

# Debug flags
DEBUG_FLAGS := -DDEBUG -g3 -O0

RELEASE_FLAGS := -O3 -march=native #Remove architecture for the general binaries

# Library name and files
EXE_BASE := jaipur

LIB_BASE := jaipur_lib
LIB_NAME_DEBUG := $(LIB_BASE)_debug
LIB_NAME_RELEASE := $(LIB_BASE)_release
LIB_SOURCES := game_data.c ltables.c prints.c utils.c
LIB_OBJECTS := $(LIB_SOURCES:%.c=$(OBJ_DIR)/%.o)
LIB_DEPS := $(LIB_OBJECTS:%.o=%.d)
SHARED_LIB_DEBUG := $(SHARED_LIB_PREFIX)$(LIB_NAME_DEBUG).$(SHARED_LIB_EXT)
SHARED_LIB_RELEASE := $(SHARED_LIB_PREFIX)$(LIB_NAME_RELEASE).$(SHARED_LIB_EXT)

# Debug/Release specific objects and libraries
LIB_OBJECTS_DEBUG := $(LIB_SOURCES:%.c=$(OBJ_DIR)/%_debug.o)
LIB_OBJECTS_RELEASE := $(LIB_SOURCES:%.c=$(OBJ_DIR)/%_release.o)
LIB_DEPS_DEBUG := $(LIB_OBJECTS_DEBUG:%.o=%.d)
LIB_DEPS_RELEASE := $(LIB_OBJECTS_RELEASE:%.o=%.d)

# Executable name and files
# Executable name and files
EXE_BASE := jaipur
EXE_NAME_DEBUG := $(EXE_BASE)_debug$(EXE_EXT)
EXE_NAME_RELEASE := $(EXE_BASE)_release$(EXE_EXT)
EXE_SOURCES := console_emulator.c
EXE_OBJECTS_DEBUG := $(EXE_SOURCES:%.c=$(OBJ_DIR)/%_debug.o)
EXE_OBJECTS_RELEASE := $(EXE_SOURCES:%.c=$(OBJ_DIR)/%_release.o)
EXE_DEPS_DEBUG := $(EXE_OBJECTS_DEBUG:%.o=%.d)
EXE_DEPS_RELEASE := $(EXE_OBJECTS_RELEASE:%.o=%.d)

# All source files are in src directory
VPATH := $(SRC_DIR)

# Targets
.PHONY: all clean directories print-debug debug release

all: debug release

debug: CFLAGS += $(DEBUG_FLAGS)
debug: directories $(BIN_DIR)/$(EXE_NAME_DEBUG) $(BIN_DIR)/$(SHARED_LIB_DEBUG)

release: CFLAGS += $(RELEASE_FLAGS)
release: directories $(BIN_DIR)/$(EXE_NAME_RELEASE) $(BIN_DIR)/$(SHARED_LIB_RELEASE)

print-debug:
	@echo Library sources: $(LIB_SOURCES)
	@echo Library objects debug: $(LIB_OBJECTS_DEBUG)
	@echo Library objects release: $(LIB_OBJECTS_RELEASE)
	@echo Library deps debug: $(LIB_DEPS_DEBUG)
	@echo Library deps release: $(LIB_DEPS_RELEASE)
	@echo Executable sources: $(EXE_SOURCES)
	@echo Executable objects debug: $(EXE_OBJECTS_DEBUG)
	@echo Executable objects release: $(EXE_OBJECTS_RELEASE)

directories:
	$(call MKDIR,$(BIN_DIR))
	$(call MKDIR,$(OBJ_DIR))


# Compile source files to object files and generate dependencies (debug)
$(OBJ_DIR)/%_debug.o: %.c
	@echo Compiling debug $<...
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Compile source files to object files and generate dependencies (release)
$(OBJ_DIR)/%_release.o: %.c
	@echo Compiling release $<...
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Link debug executable
$(BIN_DIR)/$(EXE_NAME_DEBUG): $(EXE_OBJECTS_DEBUG) $(LIB_OBJECTS_DEBUG)
	@echo Linking debug executable...
	$(CC) $(CFLAGS) $^ -o $@

# Link release executable
$(BIN_DIR)/$(EXE_NAME_RELEASE): $(EXE_OBJECTS_RELEASE) $(LIB_OBJECTS_RELEASE)
	@echo Linking release executable...
	$(CC) $(CFLAGS) $^ -o $@

# Create debug shared library
$(BIN_DIR)/$(SHARED_LIB_DEBUG): $(LIB_OBJECTS_DEBUG)
	@echo Creating debug shared library...
	$(CC) $(SHARED_LIB_FLAGS) $(CFLAGS) $^ -o $@

# Create release shared library
$(BIN_DIR)/$(SHARED_LIB_RELEASE): $(LIB_OBJECTS_RELEASE)
	@echo Creating release shared library...
	$(CC) $(SHARED_LIB_FLAGS) $(CFLAGS) $^ -o $@

# Clean build files
clean:
	$(call RMDIR,$(BIN_DIR))

# Include dependency files
-include $(LIB_DEPS_DEBUG) $(LIB_DEPS_RELEASE) $(EXE_DEPS_DEBUG) $(EXE_DEPS_RELEASE)