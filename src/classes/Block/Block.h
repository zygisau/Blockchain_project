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

public:
	Block(string *prevBlock, int version, int nonce, int difficultyTarget, list<Transaction> &transactions) {
		string merkleTreeHash = merkelize(transactions);
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

	string static merkelize(list<Transaction> &transactions) {
		string init;
		return std::accumulate(transactions.begin(), transactions.end(), init, [](string &acc, Transaction tran) {
			return HASH_FUNC(acc + tran.toString());
		});
	}

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
