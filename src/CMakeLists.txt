# Set flags for all configurations
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")

# Set flags specifically for Debug builds
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

# Set flags specifically for Release builds
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")


# Add executable target
add_executable(${EXECUTABLE_NAME}
    main.c          # Main file
)

# Include directories (for header files)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
