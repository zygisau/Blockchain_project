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

	void updateBlockInfo(vector<Block>::iterator block) {
		block->getHeader()->setPreviousHash(blocks.back().getBlockHashPtr());
		block->getHeader()->setVersion(nextVersion);
	}

public:
	void generateGenesisBlock(list<Transaction>& transPool) {
		cout << "Picking transactions from the pool" << endl;
		list<Transaction> transactions = pickTransactions(transPool);
		if(!transactions.empty()) {
			cout << "Mining" << endl;
			Block block = generateAndMine(transactions, nullptr);
			blocks.push_back(block);
			cout << "Genesis block created" << endl;
		}
	}

	void generateBlocks(list<Transaction>& transPool) {
		if (!transPool.empty()) {
			cout << "Picking 500 transactions" << endl;
			vector<Block> blockPool = generateBlockPool(transPool, nextVersion, difficulty, sizeOfTransactionsInBlock,
														blocks.back());
			nextVersion++;

			bool mined;
			int times = 10;
			int tries;
			string blockHash;
			auto blockIt = select_randomly(blockPool.begin(), blockPool.end());
			vector<vector<Block>::iterator> usedBlocks;
			usedBlocks.reserve(5);
			cout << "Preparing to mine (prev block hash)" << endl << *(blockIt->getHeader()->getPrevBlock()) << endl;
			while (!transPool.empty() || blockIt != blockPool.end()) {
				mined = false;
				usedBlocks.push_back(blockIt);
				blockHash = "";
				tries = 0;
				while (tries != times) {
					blockHash = hashBlock(*blockIt);
					if (!isHashValid(blockHash, difficulty)) {
						blockIt->getHeader()->incNonce();
						blockIt->getHeader()->setTimeout();
						tries++;
					} else {
						mined = true;
						blockIt->setHash(blockHash);
						blocks.push_back(*blockIt);
						nextVersion++;
						cout << "Block mined in " << tries << " tries" << endl << endl;
						break;
					}
				}
				if (mined) {
					moveUnusedTransToPool(blockIt, blockPool, transPool);
					blockIt = blockPool.end();
					if (!transPool.empty()) {
						blockPool = generateBlockPool(transPool, nextVersion, difficulty, sizeOfTransactionsInBlock,
													  blocks.back());
						nextVersion++;
						cout << "Selecting random block" << endl;
						blockIt = select_randomly(blockPool.begin(), blockPool.end());
						updateBlockInfo(blockIt);
						cout << "Preparing to mine (prev block hash)" << endl << *(blockIt->getHeader()->getPrevBlock())
							 << endl;
					}
				} else {
					if (usedBlocks.size() < 5) {
						cout << "TIMEOUT" << "\t" << "Selecting other block" << endl;
						blockIt = selectRemainingBlock(usedBlocks, blockPool);
						updateBlockInfo(blockIt);
					} else {
						cout << "TIMEOUT" << "\t" << "Making bigger counter" << endl;
						usedBlocks.clear();
						times += 10;
						blockIt = select_randomly(blockPool.begin(), blockPool.end());
						updateBlockInfo(blockIt);
					}
				}
			}
		}
	}

	size_t getBlockchainSize() {
		return blocks.size();
	}
};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
