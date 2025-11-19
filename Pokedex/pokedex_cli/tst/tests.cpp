#include "catch2/catch_test_macros.hpp"
#include "PrintPokemonInfo.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include "WrappingJSONFiles.h"
#include <rapidjson/stringbuffer.h>
#include <sstream>
#include <iostream>
#include <windows.h> //To set the encoding for the windows cli to print font correctly. Windows only.

TEST_CASE("Check Pokemon Damage Chart", "[populateTypeDamageMap]")
{
    const float quadrupleDamage{4.0};
    const float doubleDamage{2.0};
    const float halfDamage{0.5};
    const float quarterDamage{0.25};
    const float noDamage{0.0};

    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokedex.json"};
    wrapPokemonJson(pokemonJsonFilename, pokemonJsonFile);

    int moltresPokedexIndexNum{146};
    int moltresIndexInTheArray{moltresPokedexIndexNum - 1};
    std::unordered_map<std::string, float> moltresDamageChart{};

    for(auto& i : pokemonJsonFile[moltresIndexInTheArray]["type"].GetArray())
    {
        std::string pokemonType {i.GetString()};

        // Creating document types using rapidjson
        rapidjson::Document pokemonTypeJsonFile;
        std::string pokemonDamageJsonFilename{pokemonType + ".json"};

        wrapTypeDamageJson(pokemonDamageJsonFilename,
                           pokemonTypeJsonFile);

        populateTypeDamageMap(pokemonTypeJsonFile, moltresDamageChart);
    }

    REQUIRE(moltresDamageChart["ground"] == noDamage);
    REQUIRE(moltresDamageChart["grass"] == quarterDamage);
    REQUIRE(moltresDamageChart["fire"] == halfDamage);
    REQUIRE(moltresDamageChart["water"] == doubleDamage);
    REQUIRE(moltresDamageChart["rock"] == quadrupleDamage);
    REQUIRE(moltresDamageChart["steel"] != quadrupleDamage);
    REQUIRE(moltresDamageChart["fairy"] != noDamage);

}



//
//unsigned int Factorial( unsigned int number )
//{
//    return number > 1 ? Factorial(number-1) * number : 1;
//}
//
//TEST_CASE( "Factorials are computed", "[factorial]" )
//{
//    REQUIRE( Factorial(0) == 1 );
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//    REQUIRE( Factorial(10) != 36238800 );
//}