//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H


#include "../User/User.h"

class Transaction {
private:
	User* sender;
	User* receiver;
	double amount;
public:
	Transaction(User* sender, User* receiver, double& amount) : sender(sender), receiver(receiver), amount(amount) {}

	string getSenderStr() {
		return this->sender->getId();
	}
	string getReceiverStr() {
		return this->receiver->getId();
	}
	double getAmount() { return amount; }

	string toString() {
		return getSenderStr() + " " + getReceiverStr() + " " + std::to_string(getAmount());
	}
};


#endif //BLOCKCHAIN_TRANSACTION_H
