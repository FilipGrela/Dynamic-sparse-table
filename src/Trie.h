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

    struct pair {
        TrieNode<T> *node;
        TrieNode<T> *parent;
    };

    inline bool isRoot(TrieNode<T> *node) const {
        return node == root;
    }

    void deleteChildFromParent(TrieNode<int> *child, TrieNode<int> *parent) {
        TrieNode<int> **siblings = parent->getChildren();
        for (short i = 0; i < childSize; i++) {
            if (siblings && siblings[i] == child) {
                delete siblings[i];
                siblings[i] = nullptr;
                break;
            }
        }
    }

    bool removeLeaf(TrieNode<int> *nodeToRemove, TrieNode<int> *parent) {
        // Node is root no need to delete
        if (isRoot(nodeToRemove)) {
            nodeToRemove->clearValue();
            return true;
        }

        // Remove pointer to leaf form parent and delete leaf
        deleteChildFromParent(nodeToRemove, parent);

        return true;
    }

    /**
     * This function finds parent of leaf based on its value.
     * @param leaf
     * @return pointer to parent.
     */
    TrieNode<int> *findLeafParent(TrieNode<int> *leaf) {
        TrieNode<int> *curr = root;
        TrieNode<int> *prev = nullptr;
        short size = rootSize;
        int tmp = leaf->getValue();

        while (curr && curr != leaf) {
            prev = curr;
            auto index = static_cast<short>(tmp % size);
            tmp /= size;
            TrieNode<int> **currChildren = curr->getChildren();
            if (!currChildren || !currChildren[index]) break;
            curr = currChildren[index];
            size = childSize;
        }
        return prev;
    }

    bool removeNodeWithChildren(TrieNode<int> *nodeToRemove) {
        // Find the first left leaf
        TrieNode<int> *leaf = nodeToRemove->getLeftmostLeaf(rootSize, childSize);
        nodeToRemove->setValue(leaf->getValue());

        // In case leaf parent is not removed node parent, we have to find its parent to reset a pointer
        TrieNode<int> *leafParent = findLeafParent(leaf);
        if (leafParent) {
            deleteChildFromParent(leaf, leafParent);
        }
        return true;
    }

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
            // If root empty set value
            root->setValue(value);
            root->setChild(0, nullptr, rootSize);
            return true;
        }else if (root->contains(value)) {
            return false; // Value already exists
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
     * @return pair of nodes {node, parent}, node contains value
     */
    pair search(T value) const {
        pair result = {nullptr, nullptr};
        if (root->contains(value)) {
            return {const_cast<TrieNode<T> *>(root), nullptr};
        }
        if (root->isEmpty()) {
            return result;
        }

        TrieNode<T> *currentNode = root;
        T tmp = value;
        short index = tmp % rootSize;
        tmp /= rootSize;

        while (currentNode) {
            TrieNode<T> *child = currentNode->getChild(index);
            if (!child) return result;
            if (child->contains(value)) {
                return {child, currentNode};
            }
            currentNode = child;
            index = tmp % childSize;
            tmp /= childSize;
        }
        return result;
    }

    bool remove(int value) {
        pair p = search(value);
        TrieNode<int> *nodeToRemove = p.node;
        TrieNode<int> *parent = p.parent;

        // Node does not exist
        if (!nodeToRemove) return false;

        const short curr_size = isRoot(nodeToRemove) ? rootSize : childSize;

        // Node is Leaf (No children)
        if (!nodeToRemove->hasChildren(curr_size)) {
            return removeLeaf(nodeToRemove, parent);
        }

        return removeNodeWithChildren(nodeToRemove);
    }

    void print() const {
        root->print(rootSize, childSize);
        std::printf("\n");
    }
};

#endif //TRIE_H
