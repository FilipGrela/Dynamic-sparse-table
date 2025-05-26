//
// Created by Filip Grela on 25/05/2025.
//

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

template<typename T>

class Trie {
private:
    static const int POOL_SIZE = 500;
    static TrieNode<int>* freeStack[POOL_SIZE];
    static int top;

    short rootSize, childSize;
    TrieNode<T> *root;

    struct pair{
        TrieNode<T> *node;
        TrieNode<T> *parent;
    };

public:
    Trie(const short n, const short k) : rootSize(n), childSize(k) {
        root = new TrieNode<T>();
        top = -1;
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
                currentNode->setChild(index, new TrieNode<T>(), curr_size);
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
    pair search(T value) {
        pair result = {nullptr, nullptr};
        if (root->contains(value)) {
            return {const_cast<TrieNode<T>*>(root), nullptr};
        }
        if (root->isEmpty()) {
            return result;
        }

        TrieNode<T> *currentNode = root;
        TrieNode<T> *parentNode = nullptr;
        T tmp = value;
        short index = tmp % rootSize;
        tmp /= rootSize;

        while (currentNode) {
            TrieNode<T>* child = currentNode->getChild(index);
            if (!child) return result;
            if (child->contains(value)) {
                return {child, currentNode};
            }
            parentNode = currentNode;
            currentNode = child;
            index = tmp % childSize;
            tmp /= childSize;
        }
        return result;
    }

    void print() const {
        root->print(rootSize, childSize);
        std::printf("\n");
    }

    inline const bool isRoot(TrieNode<T> *node){
        return node == root;
    }

    bool remove(int value) {
        pair p = search(value);
        TrieNode<int>* nodeToRemove = p.node;
        TrieNode<int>* parent = p.parent;

        if (!nodeToRemove) return false; // brak klucza

        // jeśli nodeToRemove nie ma dzieci
        const short curr_size = isRoot(nodeToRemove) ? rootSize : childSize;

        if (!nodeToRemove->hasChildren(curr_size)) {
            if (isRoot(nodeToRemove)) {
                nodeToRemove->clearValue();
                return true;
            }
            // szukamy indeksu w rodzicu
            TrieNode<int>** siblings = parent->getChildren();
            for (short i = 0; i < childSize; i++) {
                if (siblings && siblings[i] == nodeToRemove) {
                    delete siblings[i];
                    siblings[i] = nullptr;
                    break;
                }
            }
            return true;
        }

        // jeśli ma dzieci, szukamy lewego liścia potomnego
        TrieNode<int>* leaf = nodeToRemove->getLeftmostLeaf(rootSize, childSize);
        nodeToRemove->setValue(leaf->getValue());

        TrieNode<int>* leafParent = nullptr;
        // szukamy rodzica liścia
        TrieNode<int>* curr = root;
        TrieNode<int>* prev = nullptr;
        short size = rootSize;
        int tmp = leaf->getValue();

        // Szukamy liścia od korzenia (trzeba tu wyliczyć indeksy jak w insert/search)
        while (curr && curr != leaf) {
            prev = curr;
            short index = tmp % size;
            tmp /= size;
            TrieNode<int>** currChildren = curr->getChildren();
            if (!currChildren || !currChildren[index]) break;
            curr = currChildren[index];
            size = childSize;
        }
        leafParent = prev;

        if (leafParent) {
            TrieNode<int>** siblings = leafParent->getChildren();
            for (short i = 0; i < childSize; i++) {
                if (siblings && siblings[i] == leaf) {
                    delete siblings[i];
                    siblings[i] = nullptr;
                    break;
                }
            }
        }
        return true;
    }



};

template<typename T>
TrieNode<int>* Trie<T>::freeStack[POOL_SIZE];

template<typename T>
int Trie<T>::top = -1;

#endif //TRIE_H
