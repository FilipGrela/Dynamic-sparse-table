#include <iostream>

#include "Trie.h"

void readInput(int &numberOtTests, int &minimumValue, int &maximumValue, int &rootNodes, int &childNodes) {
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
                std::cout << value << " exist" << std::endl;

            break;
        case 'L':
            std::cin >> value;
            if (trie->search(value))
                std::cout << value << " exist" << std::endl;
            else
                std::cout << value << " not exist" << std::endl;
            break;
        case 'D':
            std::cin >> value;
            break;
        default:
            std::cerr << "Unknown command: " << command << std::endl;
    }
}

int main() {
    int numberOtTests;
    int minimumValue, maximumValue;
    int rootNodes, childNodes;

    readInput(numberOtTests, minimumValue, maximumValue, rootNodes, childNodes);

    Trie<int> *trie = new Trie<int>(rootNodes, childNodes);


    for (int i = 0; i < numberOtTests; i++) {
        testCases(trie);
    }

    delete trie;
    return 0;
}
