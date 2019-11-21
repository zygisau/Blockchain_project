//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "../../main.h"
#include "../Transaction/Transaction.h"
#include "../Header/Header.h"

class Block {
private:
	string blockHash;
	Header *header;
	list<Transaction> transactions;

	string static findRoot(vector<string>& output) {
		vector<string> results;
		string concat;

		vector<string>::iterator nextIt;
		for (auto it = output.begin(); it < output.end(); it += 2) {
			nextIt = it + 1;
			if (nextIt != output.end()) {
				concat = HASH_FUNC(*it) + HASH_FUNC(*nextIt);
			} else {
				concat = HASH_FUNC(*it) + HASH_FUNC(*it);
			}
			results.push_back(concat);
		}

		if (results.size() == 1) {
			return results.front();
		}
		return findRoot(results);
	}

	// generates Merkle Abstract Syntax Tree
	string static genMAST(list<Transaction> &transactions) {
		vector<string> results;
		string concat;
		
		if (transactions.empty()) {
			return HASH_FUNC("");
		} else if (transactions.size() == 1) {
			return transactions.begin()->getTransactionId();
		}

		list<Transaction>::iterator nextIt;
		int reverseCount = transactions.size();
		for (auto it = transactions.begin(); it != transactions.end() && reverseCount > 0; ++it) {
			nextIt = std::next(it);
			if (reverseCount != 1) {
				concat = HASH_FUNC(it->toString()) + HASH_FUNC(nextIt->toString());
			} else {
				concat = HASH_FUNC(it->toString()) + HASH_FUNC(it->toString());
				results.push_back(concat);
				break;
			}
			results.push_back(concat);
			it = std::next(it);
			reverseCount -= 2;
		}

		if (results.size() == 1) {
			return results.front();
		}
		return findRoot(results);
	}
public:
	Block(string *prevBlock, int version, int nonce, int difficultyTarget, list<Transaction> &transactions) {
		string merkleTreeHash = genMAST(transactions);
		header = new Header(prevBlock, version, nonce, difficultyTarget, merkleTreeHash);
		this->transactions = transactions;
	}

	Block(const Block &newBlock) : blockHash(newBlock.getBlockHash()), header(newBlock.getHeader()),
							transactions(newBlock.getTransactions()) {}

	~Block() {
		transactions.clear();
	}

	Block& operator=(const Block &newBlock);
	Block& operator=(Block &&newBlock) noexcept;

	void setHash(string &hash) { blockHash = hash; }

	string getBlockHash() { return blockHash; }
	[[nodiscard]] string getBlockHash() const { return blockHash; }
	string* getBlockHashPtr() { return &blockHash; }

	Header *getHeader() { return header; }
	[[nodiscard]] Header *getHeader() const { return header; }

	list<Transaction> getTransactions() { return transactions; }
	[[nodiscard]] list<Transaction> getTransactions() const { return transactions; }
};


#endif //BLOCKCHAIN_BLOCK_H
