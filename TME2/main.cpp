#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <unordered_map> // Pour la question 2
#include "HashMap.h" // Inclusion de la classe HashMap que vous avez implémentée

int main()
{
    using namespace std;
    using namespace std::chrono;

    ifstream input = ifstream("./WarAndPeace.txt");

    auto start = steady_clock::now();
    cout << "Parsing War and Peace" << endl;

    vector<pair<string, size_t>> freq; //Pour la question 3
    unordered_map<string, size_t> wordCount; //Pour la question 2

    size_t nombre_lu = 0;
    string word;
    regex re(R"([^a-zA-Z])");

    //pr::HashMap<string, size_t> wordCountHashMap(100);
    pr::HashMap<string, int> wordCountHashMap(100); //Utilisation de HashMap avec des int pour les occurences

    while (input >> word)
    {
        word = regex_replace(word, re, "");
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        //size_t* countPtr = wordCountHashMap.get(word);
        size_t* occurrencesPtr = wordCountHashMap.get(word);
        /*if (countPtr) {
            (*countPtr)++;
        } else {
            wordCountHashMap.put(word, static_cast<size_t>(1));
        }*/

        if (occurencesPtr) {
            (*occurencesPtr)++;
        } else {
            wordCountHashMap.put(word, 1);
        }

        bool trouve = false;

        for (auto &pair : freq)
        {
            if (pair.first == word)
            {
                trouve = true;
                pair.second++;
                break;
            }
        }
        if (!trouve)
        {
            freq.emplace_back(word, 1);

            if (nombre_lu % 100 == 0)
                cout << nombre_lu << ": " << word << endl;
            nombre_lu++;
        }
    }
    input.close();

    cout << "Finished Parsing War and Peace" << endl;

    auto end = steady_clock::now();
    cout << "Parsing took " << duration_cast<milliseconds>(end - start).count() << "ms.\n";

    size_t numberOfDifferentWords = wordCountHashMap.size();
    cout << "Found a total of " << numberOfDifferentWords << " different words." << endl;

    /*for (const string &targetWord : {"war", "peace", "toto"})
    {
        size_t* occurrencesPtr = wordCountHashMap.get(targetWord);
        size_t occurrences = (occurrencesPtr) ? *occurrencesPtr : 0;
        cout << "Occurrences of \"" << targetWord << "\": " << occurrences << endl;
    }*/

    size_t occurrencesOfWar = *(wordCountHashMap.get("war"));
    size_t occurrencesOfPeace = *(wordCountHashMap.get("peace"));
    size_t occurrencesOfToto = *(wordCountHashMap.get("toto"));

    cout << "Occurrences of \"war\": " << occurrencesOfWar << endl;
    cout << "Occurrences of \"peace\": " << occurrencesOfPeace << endl;
    cout << "Occurrences of \"toto\": " << occurrencesOfToto << endl;

    return 0;
}
