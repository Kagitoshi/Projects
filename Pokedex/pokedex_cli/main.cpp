#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <string>
#include <unordered_map>
#include <vector>

void printPokemonData(const rapidjson::Document& pokemonJsonFile, const rapidjson::Document& pokemonStatsJsonDocument)
{
    // printing the Pokemon's name with the first letter capitalized.
    std::string pokemonName{pokemonJsonFile["name"].GetString()};
    pokemonName[0] = std::toupper(pokemonName[0]);
    std::cout << "Pokemon Name: " << pokemonName << "\n";

    // printing pokemon types
    const rapidjson::Value& arrayOfTypes = pokemonStatsJsonDocument["types"];
    assert(arrayOfTypes.IsArray());
    int typeNum{1};
    for(auto& i : arrayOfTypes.GetArray())
    {
        std::cout << "Type " << typeNum << ": " << i["type"]["name"].GetString() << '\n';
        typeNum++;
    }
}

void printPokemonNameInEnglish(const rapidjson::Document& pokemonJsonFile)
{
    // printing the Pokemon's name with the first letter capitalized.
    std::string pokemonName{pokemonJsonFile["name"].GetString()};
    pokemonName[0] = std::toupper(pokemonName[0]);
    std::cout << pokemonName;
}

void wrapPokemonJson(const std::string& pokemonNum, rapidjson::Document& pokemonJsonDocument,
                     rapidjson::Document& pokemonStatsJsonDocument)
{
    std::ifstream pokemonJsonFile("");

    //Closing file and reopening it so string stream can start from the beginning of the file.
    pokemonJsonFile.clear();
    pokemonJsonFile.close();
    pokemonJsonFile.open("../pokemon/" + pokemonNum + '/' + pokemonNum + ".json");

    rapidjson::IStreamWrapper pokemonJsonWrapper(pokemonJsonFile);
    pokemonJsonDocument.ParseStream(pokemonJsonWrapper);

    //Closing file and reopening it so string stream can start from the beginning of the file.
    pokemonJsonFile.clear();
    pokemonJsonFile.close();
    pokemonJsonFile.open("../pokemon/" + pokemonNum + '/' + "pokemonStats.json");

    rapidjson::IStreamWrapper pokemonJsonDataWrapper(pokemonJsonFile);
    pokemonStatsJsonDocument.ParseStream(pokemonJsonDataWrapper);
}

int main()
{
    rapidjson::Document pokemonJsonFile;
    rapidjson::Document pokemonStatsJsonFile;

    // prints range of Pokemon by index
//    for(int pokemonIndex{1}; pokemonIndex < 10; pokemonIndex++)
//    {
//        wrapPokemonJson(std::to_string(pokemonIndex), pokemonJsonFile);
//
//        printPokemonNameInEnglish(pokemonJsonFile);
//        std::cout << '\n';
//    }

    int pokemonNum{};
    int pokemonCount{151};

    while(true)
    {
        std::cout << "Enter a Pokemon's national index number: ";
        std::cin >> pokemonNum;

        if(pokemonNum == 9876)
        {
            break;
        }
        else if(pokemonNum > pokemonCount || pokemonNum < 0)
        {
            std::cout << "This PokeDex only contains the first 151 pokemon.\n"
                      << "Please enter an Pokemon index that is within the Gen 1 Pokedex.\n";
        }
        else
        {
            wrapPokemonJson(std::to_string(pokemonNum), pokemonJsonFile, pokemonStatsJsonFile);
            printPokemonData(pokemonJsonFile, pokemonStatsJsonFile);
            std::cout << '\n';
        }
    }

    return 0;
}
