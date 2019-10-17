//
// Created by zygisau on 2019-10-06.
//

#ifndef BLOCKCHAIN_USER_H
#define BLOCKCHAIN_USER_H

#include "../../main.h"

class User {
private:
	string id;
	string name;
	double debit;

public:
	User(string& id, string& name, double& debit) : id(id), name(name), debit(debit) {}
	User(string&& givenId, string& givenName, double&& givenDebit) : id(givenId), name(givenName), debit(givenDebit) {}

	void setDebit(const double newDebit) { debit = newDebit; }

	string getId() {
		return id;
	}
	string getName() {
		return name;
	}
	double getDebit() {
		return debit;
	}
};


#endif //BLOCKCHAIN_USER_H
