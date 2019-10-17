//
// Created by zygisau on 2019-10-11.
//

#ifndef BLOCKCHAIN_HEADER_H
#define BLOCKCHAIN_HEADER_H

#include "../../main.h"

class Header {
private:
	string *prevBlock;
	string timestamp;
	int version;
	int nonce;
	int difficultyTarget;
	string merkleTreeHash;

public:
	Header(string *prevBlock, int &version, int &nonce, int &difficultyTarget, string &merkleTreeHash) {
		this->prevBlock = prevBlock;
		this->version = version;
		this->nonce = nonce;
		this->difficultyTarget = difficultyTarget;
		this->merkleTreeHash = merkleTreeHash;
		this->timestamp = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()).count());
	}

	string *getPrevBlock() {
		return prevBlock;
	}
	string getTimestamp() {
		return timestamp;
	}
	int getVersion() {
		return version;
	}
	int getNonce() {
		return nonce;
	}
	int getDifficultyTarget() {
		return difficultyTarget;
	}
	string getMerkleRoot() {
		return merkleTreeHash;
	}
};


#endif //BLOCKCHAIN_HEADER_H
