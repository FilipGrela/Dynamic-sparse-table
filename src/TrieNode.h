//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIENODE_H
#define TRIENODE_H


template<typename T>
class TrieNode {
private:
    T value;
    TrieNode **children;
    TrieNode *parent;
    size_t childSize;

public:
    TrieNode(size_t s, TrieNode *parent = nullptr)
        : value(0), children(new TrieNode *[s]), childSize(s), parent(parent) {
        for (size_t i = 0; i < s; i++) {
            children[i] = nullptr;
        }
    }

    // ~TrieNode() {
    //     for (size_t i = 0; i < childSize; i++) {
    //         delete children[i];
    //     }
    //     delete[] children;
    // }

    /** Returns the index of the first child that is not null.
     * If all children are null, returns -1.
     * @return index of the first child or -1 if no children exist.
     */

    short getFirstChildIndex() const {
        for (size_t i = 0; i < childSize; i++) {
            if (children[i] != nullptr) {
                return i;
            }
        }
        return -1; // Jeśli nie ma dzieci, zwracamy childSize
    }

    bool contains(T value) const {
        return (value == this->value);
    }

    void setValue(T value) {
        this->value = value;
    }

    const T &getValue() const {
        return this->value;
    }

    TrieNode *getChild(size_t index) {
        return children[index];
    };

    void setChild(size_t index, TrieNode *child) {
        children[index] = child;
    }

    TrieNode *getParent() const {
        return parent;
    }

    void print(size_t index = 0) {
        // printf("(%d, %zu) ", value, index);
        printf("%d ", value);

        for (size_t i = 0; i < childSize; i++) {
            if (children[i] != nullptr) {
                children[i]->print(i); // Rekurencyjnie przechodzimy do dzieci
            }
        }
    }

    void remove() {
        delete this;
    }
};


#endif //TRIENODE_H
