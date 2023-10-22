#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <cassert>

#include "HashMap.h"
#include "utils.h"

int main() {
    using namespace std;
    using namespace std::chrono;

    ifstream input("./WarAndPeace.txt");
    if (!input) {
        cerr << "Erreur lors de l'ouverture du fichier WarAndPeace.txt" << endl;
        return 1;
    }

    auto start = steady_clock::now();
    cout << "Analyse de War and Peace en cours..." << endl;

    pr::HashMap<string, int> wordCountHashMap(100); // Utilisation de HashMap avec des int pour les occurrences

    size_t totalWords = 0;
    string word;
    regex re(R"([^a-zA-Z])");

    while (input >> word) {
        word = regex_replace(word, re, "");
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        int* occurrencesPtr = wordCountHashMap.get(word);

        if (occurrencesPtr) {
            (*occurrencesPtr)++;
        } else {
            wordCountHashMap.put(word, 1);
        }

        totalWords++;
    }
    input.close();

    cout << "Analyse de War and Peace terminée." << endl;

    auto end = steady_clock::now();
    cout << "L'analyse a pris " << duration_cast<milliseconds>(end - start).count() << "ms." << endl;

    size_t numberOfDifferentWords = wordCountHashMap.size();
    cout << "Nombre total de mots différents : " << numberOfDifferentWords << endl;

    // Question 6 : Afficher le nombre d'occurrences de certains mots
    const string wordsToFind[] = {"war", "peace", "toto"};
    for (const string& targetWord : wordsToFind) {
        int* occurrencesPtr = wordCountHashMap.get(targetWord);
        if (occurrencesPtr) {
            cout << "Occurrences de \"" << targetWord << "\": " << *occurrencesPtr << endl;
        }
    }

    // Question 7 : Initialiser un vecteur à partir des entrées de la table de hash
    vector<pair<string, int>> wordOccurrencesVector;
    const auto& entries = wordCountHashMap.getEntries();
    for (const auto& entry : entries) {
        wordOccurrencesVector.emplace_back(entry.key, entry.value);
    }

    // Question 8 : Trier le vecteur par nombre d'occurrences décroissantes et afficher les dix mots les plus fréquents
    sort(wordOccurrencesVector.begin(), wordOccurrencesVector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "Les mots les plus fréquents : " << endl;
    for (size_t i = 0; i < min<size_t>(10, wordOccurrencesVector.size()); ++i) {
        cout << wordOccurrencesVector[i].first << ": " << wordOccurrencesVector[i].second << " occurrences" << endl;
    }

    return 0;
}

int main2(){
    using namespace std;

    vector<string> vec;
    vec.push_back("the");
    vec.push_back("tata");
    vec.push_back("toto");

    assert(vec.size() == pr::count(vec.begin(), vec.end()));
    assert(2 == pr::count_if_equal(vec.begin(), vec.end(), "the"));
    assert(1 == pr::count_if_equal(vec.begin(), vec.end(), "tata"));

    return 0;
}