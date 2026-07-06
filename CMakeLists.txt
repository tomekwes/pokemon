cmake_minimum_required(VERSION 3.25)

project(pokemon
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type if none specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# Keep binaries organized
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ── Library: game engine ──────────────────────────────────────────
add_library(pokemon_lib STATIC
    src/battler.h
    src/battle.h
    src/elements.h
    src/utils.h
    src/pokemons.h     src/pokemons.cpp
    src/interface/imove.h
    src/interface/icondition.h
    src/interface/iattempt.h
    src/interface/inumber.h
    src/interface/itarget.h
    src/interface/ieffect.h
    src/moves.h
    src/conditions.h
    src/attempts.h
    src/effects.h
)

target_include_directories(pokemon_lib PUBLIC src)
target_compile_options(pokemon_lib PRIVATE -Wall -Wextra -Wpedantic)

# ── Executable ─────────────────────────────────────────────────────
add_executable(pokemon src/main.cpp)
target_link_libraries(pokemon PRIVATE pokemon_lib)
target_compile_options(pokemon PRIVATE -Wall -Wextra -Wpedantic)
