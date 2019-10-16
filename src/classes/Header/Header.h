//
// Created by zygisau on 2019-10-11.
//

#ifndef BLOCKCHAIN_HEADER_H
#define BLOCKCHAIN_HEADER_H

#include "../../main.h"
#include "../Block/Block.h"

class Header {
private:
	int* prevBlock;
	string timestamp;
	int version;
	int nonce;
	int difficultyTarget;
	string merkleTreeHash;

public:
	Header(int& prevBlock, int version, int nonce, int difficultyTarget) {
		this->prevBlock = &prevBlock;
		this->version = version;
		this->nonce = nonce;
		this->difficultyTarget = difficultyTarget;
	}
};


#endif //BLOCKCHAIN_HEADER_H
