//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H


#include "../User/User.h"

class Transaction {
private:
	string id;
	User* sender;
	User* receiver;
	double amount;
	long long nonce;

public:
	Transaction(User* sender, User* receiver, double& amount, long long& nonce) : sender(sender), receiver(receiver), amount(amount), nonce(nonce) {
		id = HASH_FUNC(getSenderId() + getReceiverId() + std::to_string(getAmount()) + std::to_string(nonce));
	}

	string getTransactionId() {
		return id;
	}
	string getSenderId() {
		return this->sender->getId();
	}
	string getReceiverId() {
		return this->receiver->getId();
	}
	double getAmount() { return amount; }
	long long getNonce() { return nonce; }
	[[nodiscard]] long long getNonce() const { return nonce; }

	string toString() {
		return getTransactionId() + " " + getSenderId() + " " + getReceiverId() + " " + std::to_string(getAmount());
	}

	bool validateId (const string& inputHash) {
		return inputHash == id;
	}

	User* getSender() {
		return sender;
	}
	User* getReceiver() {
		return receiver;
	}

	bool operator==(const Transaction& transCandidate) {
		return transCandidate.id == this->id;
	}
};


#endif //BLOCKCHAIN_TRANSACTION_H
