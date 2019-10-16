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

	string getSender() {
		std::stringstream strstream;
		strstream << this->sender->getId() << " " << this->sender->getName() << " " << this->sender->getDebit();
		return strstream.str();
	}
	string getReceiver() {
		std::stringstream strstream;
		strstream << this->receiver->getId() << " " << this->receiver->getName() << " " << this->receiver->getDebit();
		return strstream.str();
	}
	double getAmount() { return amount; }
};


#endif //BLOCKCHAIN_TRANSACTION_H
