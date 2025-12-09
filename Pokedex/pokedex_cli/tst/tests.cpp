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

TEST_CASE("Check Pokemon Evo Chart", "[getFirstInEvoChain]")
{
    const int charmandersIndexInTheArrayControl{3};
    int charmanderIndexInTheArray{3};
    int charmeleonIndexInTheArray{4};
    int charizardIndexInTheArray{5};
    int pikachuIndexInTheArray{24};
    int raichuIndexInTheArray{25};

    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokedex.json"};
    wrapPokemonJson(pokemonJsonFilename, pokemonJsonFile);

    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    getFirstInEvoChain(charmanderIndexInTheArray, pokemonJsonFile);
    getFirstInEvoChain(charmeleonIndexInTheArray, pokemonJsonFile);
    getFirstInEvoChain(charizardIndexInTheArray, pokemonJsonFile);
    getFirstInEvoChain(pikachuIndexInTheArray, pokemonJsonFile);
    getFirstInEvoChain(raichuIndexInTheArray, pokemonJsonFile);

    REQUIRE(charmanderIndexInTheArray == charmandersIndexInTheArrayControl);
    REQUIRE(charmeleonIndexInTheArray == charmandersIndexInTheArrayControl);
    REQUIRE(charizardIndexInTheArray == charmandersIndexInTheArrayControl);
    REQUIRE(pikachuIndexInTheArray != charmandersIndexInTheArrayControl);
    REQUIRE(raichuIndexInTheArray != charmandersIndexInTheArrayControl);

}
