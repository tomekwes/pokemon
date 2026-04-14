cmake_minimum_required(VERSION 3.25) # Required for better C++23 support

project(pokemon
    VERSION 1.0
    LANGUAGES CXX
)

# Force C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Keep the binary output organized
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add your source files
add_executable(pokemon
    src/main.cpp
    src/battler.h
    src/elements.h
    src/imove.h
    src/moves.h
)

# Optional: Enable common warnings to keep your code sharp
target_compile_options(pokemon PRIVATE -Wall -Wextra -Wpedantic)
