cmake_minimum_required(VERSION 3.31)
project(Dynamic_sparse_table)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dynamic_sparse_table src/main.cpp
        src/TrieNode.h
        src/Trie.h)


# Define DEBUG variable if not already defined
if(NOT DEFINED DEBUG)
    set(DEBUG 0)
endif()

# Add DEBUG definition to compiler flags
if(DEBUG)
    add_definitions(-DDEBUG)
endif()