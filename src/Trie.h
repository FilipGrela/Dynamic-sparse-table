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
        T originalValue = value;
        if (root->getValue() == 0) {
            // Jeśli korzeń jest pusty, ustawiamy wartość
            root->setValue(originalValue);
            return true;
        }

        TrieNode<T> *currentNode = root;
        size_t index = value % rootSize; // Reszta z dzielenia przez rootSize
        bool first_run = true; // Flaga do pierwszego przebiegu

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(index);

            if (nextNode == nullptr) {
                nextNode = new TrieNode<T>(childSize);
                nextNode->setValue(originalValue);
                currentNode->setChild(index, nextNode);
                return true;
            }

            if (nextNode->contains(value)) {
                return false;
            }

            currentNode = nextNode;
            value /= first_run ? rootSize : childSize;
            first_run = false;
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
        TrieNode<T> *currentNode = root;
        if (currentNode->getValue() == value) {
            return true;
        }

        bool first_run = true;
        size_t index = value % rootSize;

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(index);

            if (nextNode == nullptr) {
                return false;
            }
            if (nextNode->contains(originalValue)) {
                return true;
            }

            currentNode = nextNode;

            value /= first_run ? rootSize : childSize;
            first_run = false;
            index = value % childSize;
        }
    }

    void print() const {
        root->print();
        std::cout << std::endl;
    }

    bool remove(T value) {
        if (!search(value))
            return false;
    }
};

#endif //TRIE_H
