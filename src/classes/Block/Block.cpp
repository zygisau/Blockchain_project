//
// Created by zygisau on 2019-10-06.
//

#include "Block.h"

Block& Block::operator=(const Block &newBlock) {
	// Savęs priskyrimo aptikimas
	if (&newBlock == this) return *this;

	// Atlaisviname seną atmintį (jei buvo)
	transactions.clear();

	// Nukopijuojame naujus elementus
	blockHash = newBlock.getBlockHash();
	header = newBlock.getHeader();
	transactions = newBlock.getTransactions();

	return *this;
}

Block& Block::operator=(Block&& newBlock) noexcept {
	// Savęs priskyrimo aptikimas
	if(&newBlock == this)
		return *this;

	this->transactions.clear();
	this->transactions = std::move(newBlock.transactions);
	delete this->header;
	this->header = newBlock.header;

	return *this;
}