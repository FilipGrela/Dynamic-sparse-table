//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include <cstdint>

#include "TrieNode.h"

template<typename T>
class Trie {
private:
    short rootSize, childSize;
    TrieNode<T> *root;

public:
    Trie(const short n, const short k) : rootSize(n), childSize(k) {
        root = new TrieNode<T>(rootSize);
    }

    Trie(const Trie &other) : rootSize(other.rootSize), childSize(other.childSize) {
        root = new TrieNode<T>(*other.root);
    }

    Trie &operator=(const Trie &other) {
        if (this == &other) return *this;

        delete root;
        rootSize = other.rootSize;
        childSize = other.childSize;
        root = new TrieNode<T>(*other.root);
        return *this;
    }

    ~Trie() {
        delete root;
    }

    /**
     * Inserts a value into the trie.
     *
     * @param value The value to insert into the trie.
     * @return true if the value was successfully inserted, false if it already exists.
     */
    bool insert(T value) {
        T tmp = value;
        if (root->isEmpty()) {
            // Jeśli korzeń jest pusty, ustawiamy wartość
            root->setValue(value);
            return true;
        }
        if (root->contains(value)) {
            return false; // Wartość już istnieje
        }

        TrieNode<T> *currentNode = root;
        short index = tmp % rootSize;
        tmp /= rootSize;

        while (true) {
            if (!currentNode->getChild(index)) {
                currentNode->setChild(index, new TrieNode<T>(childSize, currentNode));
            }

            currentNode = currentNode->getChild(index);

            if (currentNode->isEmpty()) {
                currentNode->setValue(value);
                return true; // Wartość już istnieje
            }
            if (currentNode->contains(value)) {
                return false; // Wartość już istnieje
            }

            index = tmp % childSize;
            tmp /= childSize;
        }
    }


    /**
     * Checks if value exists.
     * @param value value to search for.
     * @return true or false.
     */
    TrieNode<T> *search(T value) {
        if (root->contains(value)) {
            return root;
        }
        if (root->isEmpty()) {
            return nullptr; // no value
        }

        T tmp = value;
        TrieNode<T> *currentNode = root;


        short index = tmp % rootSize;
        tmp /= rootSize;

        while (currentNode) {
            currentNode = currentNode->getChild(index);

            if (!currentNode) {
                return nullptr;
            }
            if (currentNode->contains(value)) {
                return const_cast<TrieNode<T> *>(currentNode);
            }

            index = tmp % childSize;
            tmp /= childSize;
        }
        return nullptr;
    }

    void print() const {
        root->print();
        std::printf("\n");
    }

    bool remove(T value) {
        TrieNode<T> *nodeToRemove = search(value);
        if (!nodeToRemove) return false;

        // Leaf (has no children)
        if (!nodeToRemove->hasChildren()) {
            if (nodeToRemove == root) {
                nodeToRemove->clearValue(); // Reset root value
                return true;
            }
            TrieNode<T> *parent = nodeToRemove->getParent();
            for (short i = 0; i < parent->getChildSize(); i++)
                if (parent->getChild(i) == nodeToRemove) {
                    parent->setChild(i, nullptr);
                    break;
                }
            delete nodeToRemove;
            return true;
        }

        // Node with children
        TrieNode<T> *leaf = nodeToRemove->getLeftmostLeaf();
        nodeToRemove->setValue(leaf->getValue());

        TrieNode<T> *parent = leaf->getParent();
        for (short i = 0; i < parent->getChildSize(); i++)
            if (parent->getChild(i) == leaf) {
                parent->setChild(i, nullptr);
                break;
            }
        delete leaf;
        return true;
    }
};

#endif //TRIE_H
