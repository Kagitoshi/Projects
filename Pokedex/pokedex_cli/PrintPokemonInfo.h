#ifndef POKEDEX_CLI_PRINTPOKEMONINFO_H
#define POKEDEX_CLI_PRINTPOKEMONINFO_H

#include "WrappingJSONFiles.h"
#include "rapidjson/document.h"
#include <iostream>
#include <string>
#include <unordered_map>

void printEvolutionChain(const int& pokemonNumInArray, const rapidjson::Document& pokemonJsonFile);

void printPokemonEvolutions(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile);

void printPokemonName(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile);

void printPokemonTypes(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile);

void printPokemonDamageChart(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile);

void printPokemonData(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile);


#endif //POKEDEX_CLI_PRINTPOKEMONINFO_H
