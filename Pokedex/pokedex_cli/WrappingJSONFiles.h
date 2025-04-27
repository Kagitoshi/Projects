#ifndef POKEDEX_CLI_WRAPPINGJSONFILES_H
#define POKEDEX_CLI_WRAPPINGJSONFILES_H

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>


void wrapPokemonJson(const std::string& pokemonNum, const std::string& pokemonFilename,
                     rapidjson::Document& pokemonJsonDocument);

void wrapTypeDamageJson(const std::string& pokemonFilename,
                        rapidjson::Document& pokemonJsonDocument);


#endif //POKEDEX_CLI_WRAPPINGJSONFILES_H
