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

public:
    TrieNode(TrieNode *parent = nullptr)
        : value(EMPTY_VAL), children(nullptr) {
    }

    ~TrieNode() {
        if (!children) return;
        for (short i = 0; i < 4; ++i)
            if (children[i]) delete children[i];
        delete [] children;
    }

    /** Returns the index of the first child that is not null.
     * If all children are null, returns -1.
     * @return index of the first child or -1 if no children exist.
     */

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

    bool hasChildren(const short size) const {
        if (!children) return false;
        for (short i = 0; i < size; ++i)
            if (children[i]) return true;
        return false;
    }

    TrieNode *getLeftmostLeaf(short curr_size, const short childSize) {
        TrieNode *p = this;

        while (p->hasChildren(curr_size)) {
            for (short i = 0; i < curr_size; ++i)
                if (p->children[i]) {
                    p = p->children[i];
                    curr_size = childSize;
                    break;
                }
        }
        return p;
    }

    void print(const short cur_size, const short childSize) {
        if (!isEmpty()) {
            std::printf("%d ", this->value);
        }
        if (!children) return;

        for (short i = 0; i < cur_size; i++) {
            if (children[i] != nullptr) {
                children[i]->print(childSize, childSize);
            }
        }
    }
};

#endif //TRIENODE_H
