//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

template<typename T>
class Trie {
private:

public:
    size_t rootSize, childSize;
    TrieNode<T> *root;

    Trie(const size_t n, const size_t k) : root(new TrieNode<T>(n)) {
        rootSize = n;
        childSize = k;
    }

    /**
     * Inserts a value into the trie.
     *
     * @param value The value to insert into the trie.
     * @return true if the value was successfully inserted, false if it already exists.
     */
    bool insert(T value) {
        bool first_run = true; // Flaga do pierwszego przebiegu
        T originalValue = value;
        if (root->getValue() == 0) {
            // Jeśli korzeń jest pusty, ustawiamy wartość
            root->setValue(originalValue);
            return true;
        }

        TrieNode<T> *currentNode = root;

        size_t index = value % rootSize; // Reszta z dzielenia przez rootSize

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(index);

            if (nextNode == nullptr) {
                // Tworzymy nowy węzeł, jeśli nie istnieje
                nextNode = new TrieNode<T>(childSize);
                nextNode->setValue(originalValue);
                currentNode->setChild(index, nextNode);
                return true;
            }

            if (nextNode->contains(value)) {
                // Wartość już istnieje
                return false;
            }

            currentNode = nextNode;

            if (first_run) {
                value /= rootSize;
                first_run = false;
            } else {
                value /= childSize;
            }
            index = value % childSize;
        }
    }


    /**
     * Checks if value exists.
     * @param value value to search for.
     * @return true or false.
     */
    bool search(T value) {
        T originalValue = value;
        TrieNode<T> *currentNode = root; // Start from the root node
        if (currentNode->getValue() == value) {
            return true; // If root is empty, return nullptr
        }

        size_t index = value % rootSize; // Reszta z dzielenia przez rootSize

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(index);

            if (nextNode == nullptr) {
                // If the next node does not exist, the value is not found
                return false;
            }
            if (nextNode->contains(originalValue)) {
                // If the value is found in the current node
                return true;
            }

            currentNode = nextNode;

            value /= (currentNode == root) ? rootSize : childSize; // Adjust division based on current node
            index = value % ((currentNode == root) ? childSize : childSize);
        }
    }

    void print() const {
        root->print();
        std::cout << std::endl;
    }
};

#endif //TRIE_H
