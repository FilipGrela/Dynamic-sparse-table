//
// Created by Filip Grela on 25/05/2025.
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
    short childSize;

public:
    TrieNode(short s, TrieNode *parent = nullptr)
        : empty(true), value(), children(nullptr), parent(parent), childSize(s) {
    }

    ~TrieNode() {
        if (!children) return;
        for (short i = 0; i < childSize; ++i)
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

    TrieNode *getChild(short index) {
        if (!children) {
            return nullptr;
        }
        return children[index];
    };

    void setChild(short index, TrieNode *child) {
        if (!children) {
            children = new TrieNode *[childSize];
            for (short i = 0; i < childSize; ++i)
                children[i] = nullptr;
        }
        children[index] = child;
    }

    short getChildSize() const {
        return childSize;
    }

    bool hasChildren() const {
        if (!children) return false;
        for (short i = 0; i < childSize; ++i)
            if (children[i]) return true;
        return false;
    }

    TrieNode *getLeftmostLeaf() {
        TrieNode *p = this;
        while (p->hasChildren()) {
            for (short i = 0; i < p->childSize; ++i)
                if (p->children[i]) {
                    p = p->children[i];
                    break;
                }
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
        if (!children) return;
        for (short i = 0; i < childSize; i++) {
            if (children[i] != nullptr) {
                children[i]->print();
            }
        }
    }
};

#endif //TRIENODE_H
