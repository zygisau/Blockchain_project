//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "../../main.h"
#include "../Transaction/Transaction.h"
#include "../Header/Header.h"

class Block : public Header {
private:
	string blockHash;
	vector<Transaction> transactions;

public:
	Block(int& prevBlock, int version, int nonce, int difficultyTarget, vector<Transaction>& transactions) {
		string merkleTreeHash = merkelize(transactions);
		Header(prevBlock, version, nonce, difficultyTarget, merkleTreeHash);
		this->transactions = transactions;

		string blockHash = "Implementation needed";
	}

	string static merkelize(vector<Transaction>& transactions) {
		return "Implementation needed";
	}

	string getBlockHash() {
		return blockHash;
	}
};


#endif //BLOCKCHAIN_BLOCK_H
