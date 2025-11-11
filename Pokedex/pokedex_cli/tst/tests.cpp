#include "catch2/catch_test_macros.hpp"
#include "PrintPokemonInfo.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include "WrappingJSONFiles.h"
#include <rapidjson/stringbuffer.h>
#include <sstream>
#include <iostream>
#include <windows.h> //To set the encoding for the windows cli to print font correctly. Windows only.

std::unordered_map<std::string, float> typeDamageMapCheck(int& pokemonIndex, const rapidjson::Document& pokemonJsonFile)
{
    const float quadrupleDamage{4.0};
    const float doubleDamage{2.0};
    const float halfDamage{0.5};
    const float quarterDamage{0.25};
    const float noDamage{0.0};

    int pokemonNumInArray {pokemonIndex - 1};

    std::unordered_map<std::string, float> typeDamageMap;

    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    for(auto& i : pokedexJson[pokemonNumInArray]["type"].GetArray())
    {
        std::string pokemonType {i.GetString()};

        // Creating document types using rapidjson
        rapidjson::Document pokemonTypeJsonFile;
        std::string pokemonDamageJsonFilename{pokemonType + ".json"};

        wrapTypeDamageJson(pokemonDamageJsonFilename,
                           pokemonTypeJsonFile);

        populateTypeDamageMap(pokemonTypeJsonFile, typeDamageMap);
    }

    return typeDamageMap;
}

TEST_CASE("Check Pokemon Damage Chart", "[typeDamageMapCheck]")
{
    const float quadrupleDamage{4.0};
    const float doubleDamage{2.0};
    const float halfDamage{0.5};
    const float quarterDamage{0.25};
    const float noDamage{0.0};

    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokedex.json"};
    wrapPokemonJson(pokemonJsonFilename, pokemonJsonFile);

    int pikachusIndexNum{25};
    std::unordered_map<std::string, float> pikachusDamageChart{
            typeDamageMapCheck(pikachusIndexNum, pokemonJsonFile)};

    REQUIRE(pikachusDamageChart["ground"] == doubleDamage);
    REQUIRE(pikachusDamageChart["water"] != doubleDamage);
    REQUIRE(pikachusDamageChart["fire"] != doubleDamage);

}

//TEST_CASE("printPokemonName with stringstream", "[pokemon]") {
//    rapidjson::Document pokemonJsonFile;
//    std::string pokemonJsonFilename{"pokedex.json"};
//
//    wrapPokemonJson(pokemonJsonFilename, pokemonJsonFile);
//
//    SECTION("Test with stringstream") {
//        std::ostringstream testOutput;
//
//        // Call function with our test stream
//        printPokemonName(1, pokemonJsonFile, testOutput);
//
//        std::string result = testOutput.str();
//
//        // Verify output
//        REQUIRE(result.find("Pikachu") != std::string::npos);
//        REQUIRE(result.find("Pokémon Name: Pikachu") != std::string::npos);
//        // ... additional assertions
//    }
//}



unsigned int Factorial( unsigned int number )
{
    return number > 1 ? Factorial(number-1) * number : 1;
}

TEST_CASE( "Factorials are computed", "[factorial]" )
{
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
    REQUIRE( Factorial(10) != 36238800 );
}


//TEST_CASE( "Check if Pokemon count variable has been initialized.")
//{
//    REQUIRE( pokemonCount == 151);
//}
//
