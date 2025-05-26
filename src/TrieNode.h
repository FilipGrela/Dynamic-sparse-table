//
// Created by Filip Grela on 25/05/2025.
//

#ifndef TRIENODE_H
#define TRIENODE_H

#define EMPTY_VAL 0

template<typename T>
class TrieNode {
private:
    T value;
    TrieNode **children;
    TrieNode *parent;

public:
    TrieNode(TrieNode *parent = nullptr)
        : value(EMPTY_VAL), children(nullptr), parent(parent) {
    }

    ~TrieNode() {
        if (!children) return;
//        for (short i = 0; i < getChildSize(); ++i)
//            if (children[i]) delete children[i];
        delete [] children;
    }

    /** Returns the index of the first child that is not null.
     * If all children are null, returns -1.
     * @return index of the first child or -1 if no children exist.
     */

//    inline short getChildSize() const {
//        if (!children) return -1;
//        short size = 0;
//        while (children[size] != nullptr) ++size;
//        return size;
//    }

    bool isEmpty() const {
        return value == EMPTY_VAL;
    }

    bool contains(T v) const {
        return (this->value == v && !isEmpty());
    }

    void setValue(T v) {
        this->value = v;
    }

    void clearValue() {
        value = EMPTY_VAL;
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

    void setChild(short index, TrieNode *child, const short newNodeSize) {
        if (!children) {
            children = new TrieNode *[newNodeSize];
            for (short i = 0; i < newNodeSize; ++i)
                children[i] = nullptr;
        }
        children[index] = child;
    }

    bool hasChildren(const short rootSize, const short childSize) const {
        if (!children) return false;
        const short size = (parent == nullptr ? rootSize : childSize);
        for (short i = 0; i < size; ++i)
            if (children[i]) return true;
        return false;
    }

    TrieNode *getLeftmostLeaf(const short rootSize, const short childSize) {
        TrieNode *p = this;

        short size = (parent == nullptr ? rootSize : childSize);
        while (p->hasChildren(rootSize, childSize)) {
            for (short i = 0; i < size; ++i)
                if (p->children[i]) {
                    p = p->children[i];
                    size = childSize;
                    break;
                }
        }
        return p;
    }

    TrieNode *getParent() const {
        return parent;
    }

    void print(const short rootSize, const short childSize) {
        if (!isEmpty()) {
            std::printf("%d ", this->value);
        }
        if (!children) return;

        const short size = (parent == nullptr ? rootSize : childSize);
        for (short i = 0; i < size; i++) {
            if (children[i] != nullptr) {
                children[i]->print(rootSize, childSize);
            }
        }
    }
};

#endif //TRIENODE_H
