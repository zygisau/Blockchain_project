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

public:
	Transaction(User* sender, User* receiver, double& amount) : sender(sender), receiver(receiver), amount(amount) {
		id = HASH_FUNC(getSenderId() + getReceiverId() + std::to_string(getAmount()));
	}

	string getSenderId() {
		return this->sender->getId();
	}
	string getReceiverId() {
		return this->receiver->getId();
	}
	double getAmount() { return amount; }

	User* getSender() {
		return sender;
	}
	User* getReceiver() {
		return receiver;
	}

	string toString() {
		return getSenderId() + " " + getReceiverId() + " " + std::to_string(getAmount());
	}

	bool validateId (const string& inputHash) {
		return inputHash == id;
	}
};


#endif //BLOCKCHAIN_TRANSACTION_H
