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
		std::stringstream stringStream;
		stringStream << this->sender->getId() << " " << this->sender->getName() << " " << this->sender->getDebit();
		return stringStream.str();
	}
	string getReceiverStr() {
		std::stringstream stringStream;
		stringStream << this->receiver->getId() << " " << this->receiver->getName() << " " << this->receiver->getDebit();
		return stringStream.str();
	}
	double getAmount() { return amount; }

	string toString() {
		return getSenderStr() + " " + getReceiverStr() + " " + std::to_string(getAmount());
	}
};


#endif //BLOCKCHAIN_TRANSACTION_H
