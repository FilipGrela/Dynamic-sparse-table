//
// Created by Filip Grela on 25/05/2025.
//

#include <iostream>

#include "Trie.h"

void readInput(int &numberOtTests, int &minimumValue, int &maximumValue, short &rootNodes, short &childNodes) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> numberOtTests;
    std::cin >> minimumValue >> maximumValue;
    std::cin >> rootNodes >> childNodes;
    std::cin.ignore(1, '\n');
}

void testCases(Trie<int> *trie) {
    char command;
    int value;
    std::cin >> command;

    switch (command) {
        case 'P':
            trie->print();
            break;
        case 'I':
            std::cin >> value;
            if (!trie->insert(value))
                printf("%d exist\n", value);

            break;
        case 'L':
            std::cin >> value;
            if (trie->search(value).node)
                printf("%d exist\n", value);
            else
                printf("%d not exist\n", value);
            break;
        case 'D':
            std::cin >> value;
            if (!trie->remove(value)) {
                printf("%d not exist\n", value);
            }
            break;
        default:
            fprintf(stderr, "Unknown command: %c\n", command);
    }
}

int main() {
    int numberOtTests;
    int minimumValue, maximumValue;
    short rootNodes, childNodes;

    readInput(numberOtTests, minimumValue, maximumValue, rootNodes, childNodes);

    Trie<int> *trie = new Trie<int>(rootNodes, childNodes);


    for (int i = 0; i < numberOtTests; i++) {
        testCases(trie);
    }

    delete trie;
    return 0;
}
