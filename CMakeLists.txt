cmake_minimum_required(VERSION 3.31)
project(Dynamic_sparse_table)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dynamic_sparse_table src/main.cpp
        src/TrieNode.h
        src/Trie.h)
