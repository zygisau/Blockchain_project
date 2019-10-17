//
// Created by zygim on 2019-10-11.
//

#ifndef BLOCKCHAIN_FUNCTIONS_H
#define BLOCKCHAIN_FUNCTIONS_H

#include "main.h"
#include "classes/Block/Block.h"
#include "classes/User/User.h"
#include "classes/Transaction/Transaction.h"

string generateRandomString(size_t len);
int generateRandomInteger(const int& from, const unsigned int& to);
double generateRandomDouble(const int& from, const int& to);
void notifyAboutProgress(int& size, unsigned int progress, string&& message);
void generateUsers(vector<User>& users);
int generateNextUserIndex(int& i, unsigned int size);
void generateTransactions(list<Transaction>& transactions, vector<User>& users);
string hashBlock(Block &block);
bool isHashValid(string& hash, int& difficulty);

// https://stackoverflow.com/a/16421677
template<typename RandomGenerator>
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end, RandomGenerator& g);
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end);

#endif //BLOCKCHAIN_FUNCTIONS_H
