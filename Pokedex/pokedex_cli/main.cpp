#include "PrintPokemonInfo.h"
#include "rapidjson/document.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h> //To set the encoding for the windows cli to print font correctly. Windows only.

int main()
{
    //Setting the encoding of the console, so it prints the font correctly. Only for windows.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Creating document types using rapidjson
    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokedex.json"};

    int pokemonNum{};
    int pokemonCount{151};

    while(true)
    {

        std::cout << "Enter a Pokémon's national index number: ";
        std::cin >> pokemonNum;

        if(pokemonNum == 9876)
        {
            break;
        }
        else if(pokemonNum > pokemonCount || pokemonNum < 0)
        {
            std::cout << "This Pokédex only contains the first 151 pokemon.\n"
                      << "Please enter an Pokémon index that is within the Gen 1 Pokédex.\n";
        }
        else
        {
            wrapPokemonJson(pokemonJsonFilename, pokemonJsonFile);

            printPokemonData(pokemonNum, pokemonJsonFile);
            std::cout << '\n';
        }
    }

    return 0;
}
