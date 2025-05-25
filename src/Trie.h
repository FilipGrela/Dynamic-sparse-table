//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

template <typename T>
class Trie {
private:
    size_t index;

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
        TrieNode<T> *currentNode = root;
        size_t currentIndex = value % rootSize; // Reszta z dzielenia przez rootSize

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(currentIndex);

            if (nextNode == nullptr) {
                // Tworzymy nowy węzeł, jeśli nie istnieje
                nextNode = new TrieNode<T>(childSize);
                nextNode->setValue(value);
                currentNode->setChild(currentIndex, nextNode);
                return true;
            }

            if (nextNode->contains(value)) {
                // Wartość już istnieje
                return false;
            }

            currentNode = nextNode;

            value /= childSize;
            currentIndex = value % childSize;
        }
    }


    /**
     * Searches for node that should contain the value.
     * @param value value to search for.
     * @return node containing the value or nullptr if not found.
     */
    TrieNode<T>* search(T value) {
        TrieNode<T> *currentNode = root; // Start from the root node

        index = value % rootSize;
        while (currentNode != nullptr) {
            if (currentNode->contains(value)) {
                return currentNode;
            }

            value /= childSize; // Dzielimy wartość przez childSize
            index = value % childSize; // Obliczamy resztę z dzielenia przez childSize
            currentNode = currentNode->getChild(index);

        }
        return nullptr;
    }

    void print() const {
        root->print();
        std::cout << std::endl;
    }
};

#endif //TRIE_H
