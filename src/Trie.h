//
// Created by Filip Grela on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

template<typename T>
class Trie {
private:
    short rootSize, childSize;
    TrieNode<T> *root;

public:
    Trie(const short n, const short k) : rootSize(n), childSize(k) {
        root = new TrieNode<T>();
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
            root->setChild(0, nullptr, rootSize);
            return true;
        }
        if (root->contains(value)) {
            return false; // Wartość już istnieje
        }

        TrieNode<T> *currentNode = root;
        short index = tmp % rootSize;
        tmp /= rootSize;

        const short curr_size = root->isEmpty() ? rootSize : childSize;

        while (true) {
            if (!currentNode->getChild(index)) {
                currentNode->setChild(index, new TrieNode<T>(currentNode), curr_size);
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
        root->print(rootSize, childSize);
        std::printf("\n");
    }

    TrieNode<T>* findParent(TrieNode<T>* current, TrieNode<T>* target, short rootSize, short childSize) {

        if (!current || !current->hasChildren(isRoot(current) ? rootSize : childSize)) return nullptr;

        short size = (current == root) ? rootSize : childSize;

        for (short i = 0; i < size; ++i) {
            TrieNode<T>* child = current->getChild(i);
            if (child == nullptr) continue;
            if (child == target) return current;
            TrieNode<T>* p = findParent(child, target, rootSize, childSize);
            if (p != nullptr) return p;
        }
        return nullptr;
    }

    inline const bool isRoot(TrieNode<T> *node){
        return node == root;
    }

    bool remove(T value) {
        TrieNode<T> *nodeToRemove = search(value);
        if (!nodeToRemove) return false;

        // Usuwanie liścia


        if (!nodeToRemove->hasChildren(isRoot(nodeToRemove) ? rootSize : childSize)) {
            if (isRoot(nodeToRemove)) {
                nodeToRemove->clearValue();
                return true;
            }
            TrieNode<T>* parent = findParent(root, nodeToRemove, rootSize, childSize);
            if (!parent) return false; // Nie znaleziono rodzica (błąd)

            short size = (parent == root) ? rootSize : childSize;
            for (short i = 0; i < size; ++i) {
                if (parent->getChild(i) == nodeToRemove) {
                    parent->setChild(i, nullptr, size);
                    break;
                }
            }
            delete nodeToRemove;
            return true;
        }

        // Usuwanie węzła z dziećmi
        TrieNode<T> *leaf = nodeToRemove->getLeftmostLeaf(rootSize, childSize);
        nodeToRemove->setValue(leaf->getValue());

        TrieNode<T>* parent = findParent(root, leaf, rootSize, childSize);
        if (!parent) return false;
        short size = (parent == root) ? rootSize : childSize;
        for (short i = 0; i < size; ++i) {
            if (parent->getChild(i) == leaf) {
                parent->setChild(i, nullptr, size);
                break;
            }
        }
        delete leaf;
        return true;
    }

};

#endif //TRIE_H
