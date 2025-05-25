//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIENODE_H
#define TRIENODE_H


template<typename T>
class TrieNode {
private:
    bool empty;
    T value;
    TrieNode **children;
    TrieNode *parent;
    size_t childSize;

public:
    TrieNode(size_t s, TrieNode *parent = nullptr)
        : empty(true), parent(parent), childSize(s) {
        children = new TrieNode *[s];
        for (size_t i = 0; i < s; i++) {
            children[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (size_t i = 0; i < childSize; ++i)
            if (children[i]) delete children[i];
        delete [] children;
    }

    /** Returns the index of the first child that is not null.
     * If all children are null, returns -1.
     * @return index of the first child or -1 if no children exist.
     */

    bool isEmpty() const {
        return empty;
    }

    bool contains(T v) const {
        return (this->value == v && !empty);
    }

    void setValue(T v) {
        this->value = v;
        empty = false;
    }

    void clearValue() {
        empty = true;
        value = T{};
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

    size_t getChildSize() const {
        return childSize;
    }

    bool hasChildren() const {
        for (size_t i = 0; i < childSize; ++i)
            if (children[i]) return true;
        return false;
    }

    TrieNode* getLeftmostLeaf() {
        TrieNode *p = this;
        while (p->hasChildren()) {
            for (size_t i = 0; i < p->childSize; ++i)
                if (p->children[i]) { p = p->children[i]; break; }
        }
        return p;
    }

    TrieNode *getParent() const {
        return parent;
    }

    void print() {
        if (!isEmpty()) {
            std::printf("%d ", this->value);
        }
        for (size_t i = 0; i < childSize; i++) {
            if (children[i] != nullptr) {
                children[i]->print();
            }
        }
    }

    void remove() {
        delete this;
    }
};

#endif //TRIENODE_H
