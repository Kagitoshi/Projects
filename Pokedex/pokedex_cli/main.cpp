#include "PrintPokemonInfo.h"
#include "rapidjson/document.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // Creating document types using rapidjson
    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokedex.json"};

//    rapidjson::Document pokemonJsonFile;
//    std::string pokemonJsonFilename{"pokemonInfo.json"};
//
//    rapidjson::Document pokemonStatsJsonFile;
//    std::string pokemonStatsJsonFilename{"pokemonStats.json"};
//
//    rapidjson::Document pokemonEvolutionJsonFile;
//    std::string pokemonEvolutionJsonFilename{"pokemonEvolutions.json"};


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
            wrapPokemonJson(std::to_string(pokemonNum), pokemonJsonFilename,
                            pokemonJsonFile);
//            wrapPokemonJson(std::to_string(pokemonNum), pokemonStatsJsonFilename,
//                            pokemonStatsJsonFile);
//            wrapPokemonJson(std::to_string(pokemonNum), pokemonEvolutionJsonFilename,
//                            pokemonEvolutionJsonFile);


//            printPokemonData(std::to_string(pokemonNum),
//                             pokemonJsonFile, pokemonStatsJsonFile,
//                             pokemonEvolutionJsonFile);
            printPokemonData(pokemonNum,
                             pokemonJsonFile);
            std::cout << '\n';
        }
    }

    return 0;
}
