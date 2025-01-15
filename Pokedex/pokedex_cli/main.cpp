#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <string>
#include <unordered_map>
#include <vector>

void wrapPokemonJson(const std::string& pokemonNum, const std::string& pokemonFilename,
                     rapidjson::Document& pokemonJsonDocument)
{
    std::ifstream pokemonJsonFile("");

    //Closing file and reopening it so string stream can start from the beginning of the file.
    pokemonJsonFile.clear();
    pokemonJsonFile.close();
    pokemonJsonFile.open("../pokemon/" + pokemonNum + '/' + pokemonFilename);

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

void printPokemonEvoChainDFS(std::string previousPokemonName, const rapidjson::Value& EvoChain)
{
    // run a recursive loop to print the evolution line if "evolves_to" not null
    for(auto& i : EvoChain.GetArray())
    {
        if (EvoChain.Size() > 1)
        {
            // print next evolution chain
            std::string pokemonName{i["species"]["name"].GetString()};
            pokemonName[0] = std::toupper(pokemonName[0]);
            std::cout << previousPokemonName << " can evolve into " << pokemonName;

            assert(i["evolves_to"].IsArray());
            printPokemonEvoChainDFS(pokemonName, i["evolves_to"]);
        }
        else if(i["evolves_to"].Empty())
        {
            // print next evolution chain
            std::string pokemonName{i["species"]["name"].GetString()};
            pokemonName[0] = std::toupper(pokemonName[0]);
            std::cout << previousPokemonName << " evolves into " << pokemonName << ".\n";
        }
        else
        {
            // print next evolution chain
            std::string pokemonName{i["species"]["name"].GetString()};
            pokemonName[0] = std::toupper(pokemonName[0]);
            std::cout << previousPokemonName << " evolves into " << pokemonName << " then ";

            assert(i["evolves_to"].IsArray());
            printPokemonEvoChainDFS(pokemonName, i["evolves_to"]);
        }
    }
}

void printPokemonEvolutions(const rapidjson::Document& pokemonEvolutionsJsonFile)
{
    if(pokemonEvolutionsJsonFile["chain"]["evolves_to"].Empty())
    {
        // print the only line in the evolution chain
        std::string pokemonName{pokemonEvolutionsJsonFile["chain"]["species"]["name"].GetString()};
        pokemonName[0] = std::toupper(pokemonName[0]);
        std::cout << '\n' << pokemonName << " does not evolve into anything.\n";
    }
    else
    {
        // print first chain of evolution line
        std::string pokemonName{pokemonEvolutionsJsonFile["chain"]["species"]["name"].GetString()};
        pokemonName[0] = std::toupper(pokemonName[0]);
        std::cout << "\nEvolution Chain: ";

        const rapidjson::Value& arrayOfEvolutions = pokemonEvolutionsJsonFile["chain"]["evolves_to"];
        printPokemonEvoChainDFS(pokemonName, arrayOfEvolutions);
    }

}

void printPokemonName(const rapidjson::Document& pokemonJsonFile)
{
    // printing the Pokemon's name with the first letter capitalized.
    std::string pokemonName{pokemonJsonFile["name"].GetString()};
    pokemonName[0] = std::toupper(pokemonName[0]);
    std::cout << "\nPokemon Name: " << pokemonName << "\n";
}

void printPokemonTypes(const rapidjson::Document& pokemonStatsJsonDocument)
{
    // printing Pokemon types
    const rapidjson::Value& arrayOfTypes = pokemonStatsJsonDocument["types"];
    assert(arrayOfTypes.IsArray() && "arrayOfTypes is not an array");

    int typeNum{1};
    for(auto& i : arrayOfTypes.GetArray())
    {
        std::string pokemonType {i["type"]["name"].GetString()};
        pokemonType[0] = std::toupper(pokemonType[0]);

        std::cout << "Type " << typeNum << ": " << pokemonType << '\n';
        typeNum++;
    }
}

void printPokemonDamageChart(const std::string& pokemonNum, const rapidjson::Document& pokemonStatsJsonDocument)
{
    std::unordered_map<std::string, float> typeDamageMap;

    const rapidjson::Value& arrayOfTypes = pokemonStatsJsonDocument["types"];
    assert(arrayOfTypes.IsArray() && "arrayOfTypes is not an array");

    for(auto& i : arrayOfTypes.GetArray())
    {
        std::string pokemonType {i["type"]["name"].GetString()};

        // Creating document types using rapidjson
        rapidjson::Document pokemonTypeJsonFile;
        std::string pokemonDamageJsonFilename{pokemonType + ".json"};

        wrapTypeDamageJson(pokemonDamageJsonFilename,
                        pokemonTypeJsonFile);

        for(auto& i : pokemonTypeJsonFile["damage_relations"]["double_damage_from"].GetArray())
        {
            if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
            {
                typeDamageMap[i["name"].GetString()] = 2.0;
            }
            else
            {
                typeDamageMap[i["name"].GetString()] *= 2.0;
            }
        }

        for(auto& i : pokemonTypeJsonFile["damage_relations"]["double_damage_from"].GetArray())
        {
            if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
            {
                typeDamageMap[i["name"].GetString()] = 0.5;
            }
            else
            {
                typeDamageMap[i["name"].GetString()] *= 0.5;
            }
        }

        for(auto& i : pokemonTypeJsonFile["damage_relations"]["no_damage_from"].GetArray())
        {
            if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
            {
                typeDamageMap[i["name"].GetString()] = 0.0;
            }
            else
            {
                typeDamageMap[i["name"].GetString()] *= 0.0;
            }
        }
    }

    bool firstLineToPrint{true};
    for(auto const& [type, damage] : typeDamageMap)
    {
        std::cout << type << " damage amount is " << damage << '\n';
        if(damage == 4.0)
        {
            if (firstLineToPrint)
            {
                std::cout << "Takes quadruple damage from:\n";
                std::cout << type << '\n';

                firstLineToPrint = false;
            }
            else
            {
                std::cout << type << '\n';
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == 2.0)
        {
            if (firstLineToPrint)
            {
                std::cout << "Takes double damage from:\n";
                std::cout << type << '\n';

                firstLineToPrint = false;
            }
            else
            {
                std::cout << type << '\n';
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == 0.5)
        {
            if (firstLineToPrint)
            {
                std::cout << "Takes half damage from:\n";
                std::cout << type << '\n';

                firstLineToPrint = false;
            }
            else
            {
                std::cout << type << '\n';
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == 0.25)
        {
            if (firstLineToPrint)
            {
                std::cout << "Takes quarter damage from:\n";
                std::cout << type << '\n';

                firstLineToPrint = false;
            }
            else
            {
                std::cout << type << '\n';
            }
        }
        else
        {}
    }

    firstLineToPrint = true;


    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == 0.0)
        {
            if (firstLineToPrint)
            {
                std::cout << "Takes no damage from:\n";
                std::cout << type << '\n';

                firstLineToPrint = false;
            }
            else
            {
                std::cout << type << '\n';
            }
        }
        else
        {}
    }
}

void printPokemonData(const std::string& pokemonNum,
                      const rapidjson::Document& pokemonJsonFile,
                      const rapidjson::Document& pokemonStatsJsonDocument,
                      rapidjson::Document& pokemonEvolutionsJsonFile)
{
    // printing the Pokemon's name with the first letter capitalized.
    printPokemonName(pokemonJsonFile);

    // printing Pokemon types
    printPokemonTypes(pokemonStatsJsonDocument);

    // printing Pokemon damage chart
    printPokemonDamageChart(pokemonNum, pokemonStatsJsonDocument);

    // printing Pokemon Evolution chain
    printPokemonEvolutions(pokemonEvolutionsJsonFile);
}

void printPokemonNameInEnglish(const rapidjson::Document& pokemonJsonFile)
{
    // printing the Pokemon's name with the first letter capitalized.
    std::string pokemonName{pokemonJsonFile["name"].GetString()};
    pokemonName[0] = std::toupper(pokemonName[0]);
    std::cout << pokemonName;
}

int main()
{
    // Creating document types using rapidjson
    rapidjson::Document pokemonJsonFile;
    std::string pokemonJsonFilename{"pokemonInfo.json"};

    rapidjson::Document pokemonStatsJsonFile;
    std::string pokemonStatsJsonFilename{"pokemonStats.json"};

    rapidjson::Document pokemonEvolutionJsonFile;
    std::string pokemonEvolutionJsonFilename{"pokemonEvolutions.json"};


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
            wrapPokemonJson(std::to_string(pokemonNum), pokemonStatsJsonFilename,
                            pokemonStatsJsonFile);
            wrapPokemonJson(std::to_string(pokemonNum), pokemonEvolutionJsonFilename,
                            pokemonEvolutionJsonFile);


            printPokemonData(std::to_string(pokemonNum),
                             pokemonJsonFile, pokemonStatsJsonFile,
                             pokemonEvolutionJsonFile);
            std::cout << '\n';
        }
    }

    return 0;
}
