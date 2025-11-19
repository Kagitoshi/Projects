#include "PrintPokemonInfo.h"

std::unordered_map<std::string, float> populateTypeDamageMap(const rapidjson::Document& pokemonTypeJsonFile,
                                                             std::unordered_map<std::string, float>& typeDamageMap)
{
    const float doubleDamage{2.0};
    const float halfDamage{0.5};
    const float noDamage{0.0};

    for(auto& i : pokemonTypeJsonFile["damage_relations"]["double_damage_from"].GetArray())
    {
        if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
        {
            typeDamageMap[i["name"].GetString()] = doubleDamage;
        }
        else
        {
            typeDamageMap[i["name"].GetString()] *= doubleDamage;
        }
    }

    for(auto& i : pokemonTypeJsonFile["damage_relations"]["half_damage_from"].GetArray())
    {
        if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
        {
            typeDamageMap[i["name"].GetString()] = halfDamage;
        }
        else
        {
            typeDamageMap[i["name"].GetString()] *= halfDamage;
        }
    }

    for(auto& i : pokemonTypeJsonFile["damage_relations"]["no_damage_from"].GetArray())
    {
        if(typeDamageMap.find(i["name"].GetString()) == typeDamageMap.end())
        {
            typeDamageMap[i["name"].GetString()] = noDamage;
        }
        else
        {
            typeDamageMap[i["name"].GetString()] *= noDamage;
        }
    }

    return typeDamageMap;
}



void printEvolutionChain(const int& pokemonNumInArray, const rapidjson::Document& pokemonJsonFile)
{
    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    while (pokedexJson[pokemonNumInArray]["evolution"].HasMember("next"))
    {
        bool firstInEvoSplit = true;

        for (auto& i : pokedexJson[pokemonNumInArray]["evolution"]["next"].GetArray())
        {
            if(firstInEvoSplit)
            {
                std::cout << "Then\n";
            }
            else
            {
                std::cout << "or\n";
            }

            std::string pokemonName{pokedexJson[pokemonNumInArray]["name"]["english"].GetString()};

            int nextPokeIndexInArray {std::stoi(i[0].GetString()) - 1};

            std::string nextInEvoChain {pokedexJson[nextPokeIndexInArray]["name"]["english"].GetString()};
            std::string evoMethod {i[1].GetString()};

            std::cout << pokemonName << " evolves to : " << nextInEvoChain << '\n';
            std::cout << "Evolution Method: " << evoMethod << '\n';

            printEvolutionChain(nextPokeIndexInArray, pokemonJsonFile);

            firstInEvoSplit = false;
        }

        break;
    }
}

void printPokemonEvolutions(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
{
    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    int pokemonNumInArray {pokemonNum - 1};

    if(pokedexJson[pokemonNumInArray]["evolution"].MemberCount())
    {
        while (true)
        {
            if(pokedexJson[pokemonNumInArray]["evolution"].HasMember("prev"))
            {
                pokemonNumInArray = (std::stoi(pokedexJson[pokemonNumInArray]["evolution"]["prev"][0].GetString())  - 1);
            }
            else
            {
                break;
            }
        }

        std::cout << "\n***** Evolution Chain *****\n";

        while (pokedexJson[pokemonNumInArray]["evolution"].HasMember("next"))
        {
            bool firstInEvoSplit = true;

            for (auto& i : pokedexJson[pokemonNumInArray]["evolution"]["next"].GetArray())
            {
                if(firstInEvoSplit)
                {}
                else
                {
                    std::cout << "or\n";
                }

                std::string pokemonName{pokedexJson[pokemonNumInArray]["name"]["english"].GetString()};

                int nextPokeIndexInArray {std::stoi(i[0].GetString()) - 1};

                std::string nextInEvoChain {pokedexJson[nextPokeIndexInArray]["name"]["english"].GetString()};
                std::string evoMethod {i[1].GetString()};

                std::cout << pokemonName << " evolves to : " << nextInEvoChain << '\n';
                std::cout << "Evolution Method: " << evoMethod << '\n';

                printEvolutionChain(nextPokeIndexInArray, pokemonJsonFile);

                firstInEvoSplit = false;
            }

            break;
        }
    }
    else
    {

    }

}

void printPokemonName(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
{
    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    int pokemonNumInArray {pokemonNum - 1};

    std::string pokemonName{pokedexJson[pokemonNumInArray]["name"]["english"].GetString()};
    std::string pokemonJPNName{pokedexJson[pokemonNumInArray]["name"]["japanese"].GetString()};
    int pokemonNationalIndex{pokedexJson[pokemonNumInArray]["id"].GetInt()};
    std::string pokemonSpecies{pokedexJson[pokemonNumInArray]["species"].GetString()};
    std::string pokemonDescription{pokedexJson[pokemonNumInArray]["description"].GetString()};

    std::cout << "\n***** "<< pokemonName << " *****\n"
              << "Pokémon Name: " << pokemonName << '\n'
              << "Japanese Name: " << pokemonJPNName << '\n'
              << "National Pokédex Index #: " << pokemonNationalIndex << '\n'
              << "Species: " << pokemonSpecies << '\n'
              << "\n***** "<< "Description" << " *****\n"
              << pokemonDescription << '\n';
}

void printPokemonTypes(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
{
    const rapidjson::Value& pokedexJson = pokemonJsonFile;
    assert(pokedexJson.IsArray() && "pokedexJson is not an array");

    int pokemonNumInArray {pokemonNum - 1};
    int typeNum{1};

    std::cout << "\n***** "<< "Pokémon Type and Damage Chart" << " *****\n";

    for(auto& i : pokedexJson[pokemonNumInArray]["type"].GetArray())
    {
        std::string pokemonType {i.GetString()};

        std::cout << "Type " << typeNum << ": " << pokemonType << '\n';
        typeNum++;
    }
}

void printPokemonDamageChart(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
{
    const float quadrupleDamage{4.0};
    const float doubleDamage{2.0};
    const float halfDamage{0.5};
    const float quarterDamage{0.25};
    const float noDamage{0.0};

    int pokemonNumInArray {pokemonNum - 1};

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

    bool firstLineToPrint{true};

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == quadrupleDamage)
        {
            std::string capitalizedType{type};
            capitalizedType[0] = std::toupper(capitalizedType[0]);

            if (firstLineToPrint)
            {
                std::cout << "\nTakes quadruple damage from: ";

                // Capitalizing the first character
                std::cout << capitalizedType;

                firstLineToPrint = false;
            }
            else
            {
                std::cout << ", " << capitalizedType;
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == doubleDamage)
        {
            std::string capitalizedType{type};
            capitalizedType[0] = std::toupper(capitalizedType[0]);

            if (firstLineToPrint)
            {
                std::cout << "\nTakes double damage from: ";
                std::cout << capitalizedType;

                firstLineToPrint = false;
            }
            else
            {
                std::cout << ", " << capitalizedType;
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == halfDamage)
        {
            std::string capitalizedType{type};
            capitalizedType[0] = std::toupper(capitalizedType[0]);

            if (firstLineToPrint)
            {
                std::cout << "\nTakes half damage from: ";
                std::cout << capitalizedType;

                firstLineToPrint = false;
            }
            else
            {
                std::cout << ", " << capitalizedType;
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == quarterDamage)
        {
            std::string capitalizedType{type};
            capitalizedType[0] = std::toupper(capitalizedType[0]);

            if (firstLineToPrint)
            {
                std::cout << "\nTakes quarter damage from: ";
                std::cout << capitalizedType;

                firstLineToPrint = false;
            }
            else
            {
                std::cout << ", " << capitalizedType;
            }
        }
        else
        {}
    }

    firstLineToPrint = true;

    for(auto const& [type, damage] : typeDamageMap)
    {
        if(damage == noDamage)
        {
            std::string capitalizedType{type};
            capitalizedType[0] = std::toupper(capitalizedType[0]);

            if (firstLineToPrint)
            {
                std::cout << "\nTakes no damage from: ";
                std::cout << capitalizedType;

                firstLineToPrint = false;
            }
            else
            {
                std::cout << ", " << capitalizedType;
            }
        }
        else
        {}
    }

    std::cout << '\n';
}
//std::string printPokemonData(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
void printPokemonData(const int& pokemonNum, const rapidjson::Document& pokemonJsonFile)
{
    // printing the Pokemon's name with the first letter capitalized.
    //printPokemonName(pokemonNum, pokemonJsonFile, stringStreamVar)
    //e.g. https://stackoverflow.com/questions/5193173/getting-cout-output-to-a-stdstring
    printPokemonName(pokemonNum, pokemonJsonFile);

    // printing Pokemon types
    printPokemonTypes(pokemonNum, pokemonJsonFile);

    // printing Pokemon damage chart
    printPokemonDamageChart(pokemonNum, pokemonJsonFile);

    // printing Pokemon Evolution chain
    printPokemonEvolutions(pokemonNum, pokemonJsonFile);
}