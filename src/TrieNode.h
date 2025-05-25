//
// Created by fgrel on 25/05/2025.
//

#ifndef TRIENODE_H
#define TRIENODE_H


template <typename T>
class TrieNode {
private:
    T value;
    TrieNode **children;
    size_t childSize;
public:
    TrieNode(size_t s) : value(0), children(new TrieNode*[s]), childSize(s) {
        for (size_t i = 0; i < s; i++) {
            children[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (size_t i = 0; i < sizeof(children) / sizeof(children[0]); i++) {
            delete children[i];
        }
        delete[] children;
    }

    bool contains(T value) const {
        return (value == this->value);
    }

    void setValue(T value) {
        this->value = value;
    }

    const T& getValue() const {
        return this->value;
    }

    TrieNode *getChild(size_t index) {
        return children[index];
    };

    void setChild(size_t index, TrieNode *child) {
          if (children[index] != nullptr) {
              delete children[index];
          }
          children[index] = child;
      }

    void print() const {
        std::cout << value << " ";
        for (size_t i = 0; i < childSize; i++) {
            if (children[i] != nullptr) {
                children[i]->print();
            }
        }
    }
};



#endif //TRIENODE_H
