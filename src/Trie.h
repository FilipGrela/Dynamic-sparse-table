//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

template<typename T>
class Trie {
private:
    size_t rootSize, childSize;
    TrieNode<T> *root;

public:
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
                nextNode = new TrieNode<T>(childSize, currentNode);
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
    TrieNode<T> *search(T value) {
        T originalValue = value;
        TrieNode<T> *currentNode = root;
        if (currentNode->getValue() == value) {
            return currentNode;
        }

        bool first_run = true;
        size_t index = value % rootSize;

        while (true) {
            TrieNode<T> *nextNode = currentNode->getChild(index);

            if (nextNode == nullptr) {
                return nullptr;
            }
            if (nextNode->contains(originalValue)) {
                return nextNode;
            }

            currentNode = nextNode;

            value /= first_run ? rootSize : childSize;
            first_run = false;
            index = value % childSize;
        }
    }

    void print() const {
        root->print();
        printf("\n");
    }

    bool remove(T value) {
        TrieNode<T> *nodeToRemove = search(value);
        if (!nodeToRemove) return false;

        // Leaf (has no children)
        if (nodeToRemove->getFirstChildIndex() == -1) {
            TrieNode<T> *parent = nodeToRemove->getParent();
            if (parent) {
                for (size_t i = 0; i < childSize; ++i) {
                    if (parent->getChild(i) == nodeToRemove) {
                        parent->setChild(i, nullptr);
                        break;
                    }
                }
                delete nodeToRemove;
            } else {
                nodeToRemove->setValue(0); // Clear root value without deleting it
            }
            return true;
        }

        // Node with children
        TrieNode<T> *currentNode = nodeToRemove;
        short index;

        while ((index = currentNode->getFirstChildIndex()) != -1) {
            currentNode = currentNode->getChild(index);
        }

        nodeToRemove->setValue(currentNode->getValue());
        TrieNode<T> *parentNode = currentNode->getParent();
        currentNode->remove();

        if (parentNode) parentNode->setChild(index, nullptr);

        return true;
    }
};

#endif //TRIE_H
