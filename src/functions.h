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
double generateRandomDouble(const double& from, const double& to);
void notifyAboutProgress(int& size, unsigned int progress, string&& message);
void generateUsers(vector<User>& users);
int generateNextUserIndex(int& i, unsigned int size);
void generateTransactions(list<Transaction>& transactions, vector<User>& users);
string hashBlock(Block &block);
bool isHashValid(string& hash, int& difficulty);
void validateTransactions(list<Transaction>& transactions);

// https://stackoverflow.com/a/16421677
template<typename RandomGenerator>
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end, RandomGenerator& g);
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end);
template<typename RandomGenerator>
vector<Transaction>::iterator select_randomly(vector<Transaction>::iterator start, vector<Transaction>::iterator end, RandomGenerator& g);
vector<Transaction>::iterator select_randomly(vector<Transaction>::iterator start, vector<Transaction>::iterator end);
template<typename RandomGenerator>
vector<Block>::iterator select_randomly(vector<Block>::iterator start, vector<Block>::iterator end, RandomGenerator& g);
vector<Block>::iterator select_randomly(vector<Block>::iterator start, vector<Block>::iterator end);

vector<list<Transaction>> generateFiveTransactionPacks (list<Transaction>& transPool, int numberOfTransInList);
vector<Block>::iterator selectRemainingBlock(vector<vector<Block>::iterator>& usedBlocks, vector<Block>& blockPool);

#endif //BLOCKCHAIN_FUNCTIONS_H
