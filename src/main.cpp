//Author: Ege Yurtsever
//CS300 Homework 2: Search Engine


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "AvlTree.h"
#include "WordItem.h"


std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}


int main(){
    //Create an `AvlTree` instance of `WordItem`
    //Read and preproccess the input files
    //Populate the AvlTree
    //Take input queries and show results


    // Initialize the tree with a "not found" item.
    WordItem notFound("NOT_FOUND");
    AvlTree<WordItem> wordTree(notFound);

    // Insert WordItem objects into the tree, with some initial document counts.
    std::cout << "Inserting words with initial document counts...\n";
    WordItem apple("apple");
    apple.updateDocument("Doc1.txt", 1);
    wordTree.insert(apple);

    WordItem banana("banana");
    banana.updateDocument("Doc2.txt", 2);
    wordTree.insert(banana);

    WordItem cherry("cherry");
    cherry.updateDocument("Doc3.txt", 3);
    wordTree.insert(cherry);

    // Print the tree to show its content after the insertions.
    std::cout << "Tree after insertions:\n";
    wordTree.printTree();
    std::cout << "\n\n";

    // Demonstrate searching for a specific word item.
    std::cout << "Searching for 'banana':\n";
    const auto& foundItem = wordTree.find(WordItem("banana"));
    if (foundItem.word != notFound.word) { // Check if the word was found.
        std::cout << foundItem << "\n"; // Utilizing the overloaded << operator.
    } else {
        std::cout << "'banana' not found in the tree.\n";
    }

    // Demonstrate finding the minimum and maximum items in the tree.
    std::cout << "Minimum item in the tree: " << wordTree.findMin() << "\n";
    std::cout << "Maximum item in the tree: " << wordTree.findMax() << "\n";
    std::cout << "Printing the tree:\n";
    wordTree.printTree();
    std::cout << "\n\n";
    std::cout << "Removing element " << banana.word << std::endl;
    wordTree.remove(banana);
    std::cout << "Printing the tree:\n";
    wordTree.printTree();
    std::cout << "\n\n";

    return 0;

}
