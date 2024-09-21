cmake_minimum_required(VERSION 3.10)

# Define the executable name with version

# Set the project name
project(projectname VERSION 1.0.0)

set(EXECUTABLE_NAME "projectname-${PROJECT_VERSION}")

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include the src directory to build the sources



add_subdirectory(src)



# Define the version
set(VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(VERSION_STRING "${PROJECT_VERSION}")
if(WIN32)
    set(OS_NAME "Windows")
elseif(APPLE)
    set(OS_NAME "macOS")
elseif(UNIX)
    set(OS_NAME "Linux")
else()
    set(OS_NAME "Unknown")
endif()

set(COPYRIGHT "Copyright (C) 2024 Antoni Bertolin")
set(LICENSE_VERSION "MIT License")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/config.h @ONLY)
# Configure the version header file

include_directories(${PROJECT_BINARY_BIN}) #// this allows the 'config.h' file to be used throughout the program


# Optionally set compiler flags here
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")


# Platform-specific settings (if needed)
# if(WIN32)
#     # Windows-specific settings
#     set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}.exe")
# elseif(APPLE)
#     # macOS-specific settings
#     # macOS automatically handles versioned application bundles, so you might not need to adjust the name here.
# elseif(UNIX)
#     # Linux-specific settings
#     # Linux executables don’t usually have extensions, but if you want to add one:
#     set_target_properties(${EXECUTABLE_NAME} PROPERTIES
#         OUTPUT_NAME "${EXECUTABLE_NAME}"
#     )
# endif()