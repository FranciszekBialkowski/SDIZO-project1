cmake_minimum_required(VERSION 3.24)
project(projekt1)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(projekt1 main/main.cpp main/Menu.cpp structures/Table.cpp headers/Table.h headers/Menu.h headers/List.h structures/List.cpp headers/Structure.h structures/BST.cpp headers/BST.h structures/Heap.cpp headers/Heap.h structures/RBT.cpp headers/RBT.h)
