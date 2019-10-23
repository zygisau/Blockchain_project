cmake_minimum_required(VERSION 3.13)
project(Blockchain)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../build")
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-O3")

add_executable(Blockchain ./src/main.cpp src/classes/User/User.cpp src/classes/User/User.h  src/main.h src/functions.cpp src/functions.h src/classes/Transaction/Transaction.cpp src/classes/Transaction/Transaction.h src/classes/Block/Block.cpp src/classes/Block/Block.h src/classes/Header/Header.cpp src/classes/Header/Header.h src/classes/Blockchain/Blockchain.cpp src/classes/Blockchain/Blockchain.h vendors/SHA-256/sha256.cpp vendors/SHA-256/sha256.h)