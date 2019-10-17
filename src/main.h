//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_MAIN_H
#define BLOCKCHAIN_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <memory>
#include <sstream>
#include <list>
#include <algorithm>
#include  <iterator>
using std::string; using std::vector; using std::cout; using std::endl; using std::ifstream;
using std::unique_ptr; using std::list;

#include "../vendors/SHA-256/sha256.h"
const auto HASH_FUNC = sha256;
//#include "../vendors/ZA-256/ZA256.h"
//const auto HASH_FUNC = zygisau::ZA256::hash;

#endif //BLOCKCHAIN_MAIN_H
