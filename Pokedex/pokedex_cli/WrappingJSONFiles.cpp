#include "WrappingJSONFiles.h"

void wrapPokemonJson(const std::string& pokemonNum, const std::string& pokemonFilename,
                     rapidjson::Document& pokemonJsonDocument)
{
//    std::ifstream pokemonJsonFile("");
//
//    //Closing file and reopening it so string stream can start from the beginning of the file.
//    pokemonJsonFile.clear();
//    pokemonJsonFile.close();
//    pokemonJsonFile.open("../pokemon/" + pokemonNum + '/' + pokemonFilename);
//
//    rapidjson::IStreamWrapper pokemonJsonWrapper(pokemonJsonFile);
//    pokemonJsonDocument.ParseStream(pokemonJsonWrapper);

    std::ifstream pokemonJsonFile("");

    //Closing file and reopening it so string stream can start from the beginning of the file.
    pokemonJsonFile.clear();
    pokemonJsonFile.close();
    pokemonJsonFile.open("../pokemon/" + pokemonFilename);

    rapidjson::IStreamWrapper pokemonJsonWrapper(pokemonJsonFile);
    pokemonJsonDocument.ParseStream(pokemonJsonWrapper);
}

void wrapTypeDamageJson(const std::string& pokemonFilename,
                        rapidjson::Document& pokemonJsonDocument)
{
    std::ifstream pokemonJsonFile("");

    //Closing file and reopening it so string stream can start from the beginning of the file.
    pokemonJsonFile.clear();
    pokemonJsonFile.close();
    pokemonJsonFile.open("../pokemonTypes/" + pokemonFilename);

    rapidjson::IStreamWrapper pokemonJsonWrapper(pokemonJsonFile);
    pokemonJsonDocument.ParseStream(pokemonJsonWrapper);
}