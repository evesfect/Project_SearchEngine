#ifndef WORDITEM_H
#define WORDITEM_H


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct DocumentItem {
    std::string documentName;
    int count;
    DocumentItem(std::string name, int count) : documentName(std::move(name)), count(count) {}
};

struct WordItem {
    std::string word;
    std::vector<DocumentItem> documents;
    WordItem(std::string w) : word(std::move(w)) {}

    void updateDocument(const std::string& documentName, int count) {
        auto it = std::find_if(documents.begin(), documents.end(), [&documentName](const DocumentItem& di) {
            return di.documentName == documentName;
        });
        if (it != documents.end()) {
            it->count += count;
        } else {
            documents.emplace_back(documentName, count);
        }
    }
    bool operator<(const WordItem& other) const {
        return word < other.word;
    }
    bool operator>(const WordItem& other) const {
        return word > other.word;
    }
    bool operator==(const WordItem& other) const {
        return word == other.word;
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

#endif