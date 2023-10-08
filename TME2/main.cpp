#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <unordered_map> // Pour la question 2

int main()
{
    using namespace std;
    using namespace std::chrono;

    ifstream input = ifstream("./WarAndPeace.txt");

    auto start = steady_clock::now();
    cout << "Parsing War and Peace" << endl;

    vector<pair<string, size_t>> freq;       // Pour la question 3
    unordered_map<string, size_t> wordCount; // Pour la question 2

    size_t nombre_lu = 0;
    // prochain mot lu
    string word;
    // une regex qui reconnaît les caractères anormaux (négation des lettres)
    regex re(R"([^a-zA-Z])");
    while (input >> word)
    {
        // élimine la ponctuation et les caractères spéciaux
        word = regex_replace(word, re, "");
        // passe en minuscules
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Question 2 : Compter le nombre de mots différents
        wordCount[word]++;

        bool trouve = false;

        // Question 3 : Calculer le nombre d'occurrences de chaque mot
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

            // word est maintenant "tout propre"
            if (nombre_lu % 100 == 0)
                // on affiche un mot "propre" sur 100
                cout << nombre_lu << ": " << word << endl;
            nombre_lu++;
        }
    }
    input.close();

    cout << "Finished Parsing War and Peace" << endl;

    auto end = steady_clock::now();
    cout << "Parsing took " << duration_cast<milliseconds>(end - start).count() << "ms.\n";

    // Question 2 : Afficher le nombre de mots différents
    cout << "Found a total of " << wordCount.size() << " different words." << endl;

    // Question 3 : Afficher le nombre d'occurrences des mots spécifiques
    for (const string &targetWord : {"war", "peace", "toto"})
    {
        for (const auto &pair : freq)
        {
            if (pair.first == targetWord)
            {
                cout << "Occurrences of \"" << targetWord << "\": " << pair.second << endl;
                break;
            }
        }
    }

    return 0;
}

