//
// Created by zygim on 2019-10-17.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include "../Block/Block.h"
#include "../../functions.h"

class Blockchain {
private:
	list<Block> blocks;
	int nextVersion = 0;
	int sizeOfTransactionsInBlock = 100;
	int difficulty = 4;

	list<Transaction> pickTransactions(list<Transaction>& transPool) {
		list<Transaction> pickedTransactions;
		for (int i = 1; i <= sizeOfTransactionsInBlock && !transPool.empty(); i++) {
			auto it = select_randomly(transPool.begin(), transPool.end());
			pickedTransactions.emplace_back(*it);
			transPool.erase(it);
		}
		return pickedTransactions;
	}

	Block generateAndMine(list<Transaction>& transactions, string* prevBlock) {
		int nonce = 0;
		Block newBlock(prevBlock, nextVersion++, nonce, difficulty, transactions);
		string blockHash = hashBlock(newBlock);
		while (!isHashValid(blockHash, difficulty)) {
			nonce++;
			newBlock.getHeader()->incNonce();
			newBlock.getHeader()->setTimeout();
			blockHash = hashBlock(newBlock);
		}
		newBlock.setHash(blockHash);
		return newBlock;
	}

public:
	void generateGenesisBlock(list<Transaction>& transPool) {
		cout << "Picking transactions from the pool" << endl;
		list<Transaction> transactions = pickTransactions(transPool);
		cout << "Mining" << endl;
		Block block = generateAndMine(transactions, nullptr);
		blocks.push_back(block);
		cout << "Genesis block created" << endl;
	}

	void generateBlocks(list<Transaction>& transPool) {
		int counter = 0;
		while (!transPool.empty()) {
			cout << ++counter << " Next block" << endl;
			cout << "Picking transactions from the pool" << endl;
			list<Transaction> transactions = pickTransactions(transPool);
			cout << "Mining" << endl;
			Block block = generateAndMine(transactions, blocks.back().getBlockHashPtr());
			blocks.push_back(block);
			cout << "Block generated" << endl << endl;
		}
	}

	size_t getBlockchainSize() {
		return blocks.size();
	}
};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
