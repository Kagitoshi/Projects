cmake_minimum_required(VERSION 3.24)
project(pokedex_cli)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(TEST_SOURCES main.cpp)
add_executable(tests
        tst/tests.cpp PrintPokemonInfo.cpp PrintPokemonInfo.h WrappingJSONFiles.cpp WrappingJSONFiles.h)
add_executable(pokedex_cli
        main.cpp PrintPokemonInfo.cpp PrintPokemonInfo.h WrappingJSONFiles.cpp WrappingJSONFiles.h)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

Include (Catch)
catch_discover_tests(tests)
