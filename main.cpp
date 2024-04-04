//Author: Ege Yurtsever
//CS300 Homework 2: Search Engine


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "AvlTree.h"


struct DocumentItem {
    std::string documentName;
    int count;
    DocumentItem(std::string name, int count) : documentName(std::move(name)), count(count) {}
};

struct WordItem {
    std::string word;
    std::vector<DocumentItem> documents;
    WordItem(std::string w) : word(std::move(w)) {}

    void checkDocument(const std::string& documentName, int count) {
        auto it = std::find_if(documents.begin(), documents.end(), [&documentName](const DocumentItem& di) {
            return di.documentName == documentName;
        });
        if (it != documents.end()) {
            it->count += count;
        } else {
            documents.emplace_back(documentName, count);
        }
    }
};

//Operator Overloading `<<` for printTree()
std::ostream& operator<<(std::ostream& os, const WordItem& item) {
    os << "Word: \"" << item.word << "\", Documents: [";
    for (const auto& document : item.documents) {
        os << "{Name: " << document.documentName << ", Count: " << document.count << "}, ";
    }
    os << "]";
    return os;
}

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

    AvlTree<int> tree(-1);
    
    
    return 0;
}
