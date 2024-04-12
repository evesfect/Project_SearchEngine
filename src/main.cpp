//Author: Ege Yurtsever
//CS300 Homework 2: Search Engine


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>
#include "AvlTree.h"
#include "WordItem.h"


std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

std::string cleanWord(std::string word) {
    word.erase(std::remove_if(word.begin(), word.end(), [](char c) 
    { return !std::isalpha(c); }), word.end());
    return toLower(word);
}

void updateOrInsertWord(AvlTree<WordItem>& tree, const std::string& word, const std::string& documentName) {
    WordItem tempItem(word);
    const WordItem& foundItem = tree.find(tempItem);
    if (foundItem.word != "NOT_FOUND") {
        //Word found, update document count
        WordItem updatedItem = foundItem; //Make a copy to update
        updatedItem.updateDocument(documentName, 1);
        tree.remove(foundItem); //Remove old item
        tree.insert(updatedItem); //Insert updated item
    } else {
        //Word not found, insert a new WordItem
        WordItem newItem(word);
        newItem.updateDocument(documentName, 1);
        tree.insert(newItem);
    }
}

int main(){
    
    //Create an `AvlTree` instance of `WordItem`
    //Read and preproccess the input files
    //Populate the AvlTree
    //Take input queries and show results
    
    //Take number of input files
    int inputFileCount;
    std::cout << "Enter number of input files: ";
    std::cin >> inputFileCount;

    //Take names of input files
    std::vector<std::string> inputFileVector(inputFileCount, "");
    int fileCounter = 1;
    for (std::string& s : inputFileVector) {
        std::cout << "Enter " << fileCounter << ". file name: ";
        std::cin >> s;
        fileCounter++;
    }

    //Initialize the tree with a "not found" item.
    WordItem notFound("NOT_FOUND");
    AvlTree<WordItem> wordTree(notFound);

    //Tree processing loop
    for (const auto& fileName : inputFileVector) {
        std::ifstream file(fileName);
        std::string word;
        while (file >> word) {
            word = cleanWord(word);
            if (!word.empty()) {
                //Insert/update the AvlTree
                updateOrInsertWord(wordTree, word, fileName);
            }
        }
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool running = true;
    while(running) {
        //Take query input, seperate and clean the words
        std::string queryLine;
        std::cout << "Enter queried words in one line: ";
        std::getline(std::cin, queryLine);
        //Terminating input check
        if (queryLine == "ENDOFINPUT") {
            running = false;
            break;
        }
        std::istringstream queryStream(queryLine);
        std::vector<std::string> queryWords;

        std::string queryWord;
        bool removeFlag = false;
        while (queryStream >> queryWord) {
            if (queryWord == "REMOVE") {
                queryWords.push_back(queryWord);
            }
            else {
                queryWords.push_back(cleanWord(queryWord));
            }
        }
        if (!queryWords.empty() && queryWords[0] == "REMOVE") {
            for (size_t i = 1; i < queryWords.size(); i++) {
                WordItem wordToRemove(queryWords[i]);
                wordTree.remove(wordToRemove);
                std::cout << wordToRemove.word << " has been REMOVED\n";
            }
            continue;
        }

        std::map<std::string, std::map<std::string, int>> documentWordCounts;

        //Occurence of each word in each document, stored in the map
        for (const auto& word : queryWords) {
            WordItem tempItem(word);
            const WordItem& foundItem = wordTree.find(tempItem);
            if (foundItem.word != "NOT_FOUND") {
                for (const auto& doc : foundItem.documents) {
                    documentWordCounts[doc.documentName][word] = doc.count;
                }
            }
        }

        //find documents that contain all the query
        std::vector<std::string> commonDocuments;
        for (auto it = documentWordCounts.begin(); it != documentWordCounts.end(); ++it) {
            if (it->second.size() == queryWords.size()) {
                commonDocuments.push_back(it->first);
            }
        }

        //output
        if (commonDocuments.empty()) {
            std::cout << "No document contains the given query\n";
        }
        else {
            for (const auto& docName : commonDocuments) {
                std::cout << "in Document " << docName;
                for (const auto& word : queryWords) {
                    std::cout << ", " << word << " found " << documentWordCounts[docName][word] << " times";
                }
                std::cout << ".\n";
            }
        }
    }

    return 0;
}
