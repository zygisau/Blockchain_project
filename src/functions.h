//
// Created by zygim on 2019-10-11.
//

#ifndef BLOCKCHAIN_FUNCTIONS_H
#define BLOCKCHAIN_FUNCTIONS_H

#include "main.h"
#include "classes/User/User.h"
#include "classes/Transaction/Transaction.h"

void generateUsers(vector<User>& users);
void generateTransactions(vector<Transaction>& transactions, vector<User>& users);

#endif //BLOCKCHAIN_FUNCTIONS_H
