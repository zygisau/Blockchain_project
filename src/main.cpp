//
// Created by zygisau on 2019-10-06.
//

#include "main.h"
#include "functions.h"
#include "classes/Blockchain/Blockchain.h"

int main () {
	cout << "Starting Bitcoin clone..." << endl;
	vector<User> users;
	generateUsers(users);
	list<Transaction> transactionsPool;
	generateTransactions(transactionsPool, users);
//	cout << transactionsPool.size() << endl;
	validateTransactions(transactionsPool);
//	cout << transactionsPool.size() << endl;

	size_t poolSize = transactionsPool.size();

	Blockchain blockchain;
	blockchain.generateGenesisBlock(transactionsPool);
	blockchain.generateBlocks(transactionsPool);

	cout << "Number of users created: " << users.size() << endl;
	cout << "Number of transactions created: " << poolSize << endl;
	cout << "Number of blocks in the blockchain: " << blockchain.getBlockchainSize() << endl;
	cout << "Number of transactions left in the pool: " << transactionsPool.size() << endl;
	return 0;
}