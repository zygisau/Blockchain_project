//
// Created by zygisau on 2019-10-11.
//

#include "functions.h"

string generateRandomString(size_t len) {
	char *s = new char[len];
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<> random(1, 10);

	for (size_t i = 0; i < len; ++i) {
		int randomChar = random(rng) % (26 + 26 + 10);
		if (randomChar < 26)
			s[i] = (char) ('a' + randomChar);
		else if (randomChar < 26 + 26)
			s[i] = (char) ('A' + randomChar - 26);
		else
			s[i] = (char) ('0' + randomChar - 26 - 26);
	}
	s[len] = 0;
	return string(s);
}

int generateRandomInteger(const int& from, const unsigned int& to) {
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static std::mt19937 rng(seed);
	std::uniform_int_distribution<> random(from, to);
	return random(rng);
}
double generateRandomDouble(const double& from, const double& to) {
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static std::mt19937 rng(seed);
	std::uniform_real_distribution<double> random(from, to);
	return random(rng);
}

void notifyAboutProgress(int& size, unsigned int progress, string&& message) {
	if(progress % (size/4) == 0) {
		cout << progress * 100 / size << "% " << message << " created" << endl;
	}
}

void generateUsers(vector<User>& users) {
	cout << "Generating users..." << endl;
	ifstream nameStream("../assets/names.json");

	bool streamConnected = nameStream.is_open();
	string name;
	if (streamConnected) {
		nameStream >> name;
	}
	int size = 1000;
	for (int i = 1; i <= size; i++) {
		if (streamConnected) {
			nameStream >> name;
			name = name.substr(1, name.length() - 3);
		} else {
			name = generateRandomString(8);
		}

		User user(std::to_string(i), name, generateRandomDouble(1, 100));
//		User user(std::to_string(i), generateRandomString(5), generateRandomDouble(1, 1000)); // Or just use this
		users.push_back(user);

		notifyAboutProgress(size, i, "users");
	}

	nameStream.close();
	cout << "All users have been generated succesfully" <<  endl;
}

int generateNextUserIndex(int& i, unsigned int size) {
	int index = generateRandomInteger(0, size - 1);
	while (i == index) {
		index = generateRandomInteger(0, size - 1);
	}
	return index;

}

void applyTransaction(User* sender, User* receiver, double amount) {
	sender->setDebit(sender->getDebit() - amount);
	receiver->setDebit(receiver->getDebit() + amount);
}

void generateTransactions(list<Transaction>& transactions, vector<User>& users) {
	cout << "Generating transactions..." << endl;
	int size = 10000;
	User* user1;
	User* user2;

	double amount;
	int i;
	long long nonceForTrans = 0;
	while (transactions.size() != size) {
		i = generateRandomInteger(0, users.size() - 1);
		user1 = &users[i];
		i = generateNextUserIndex(i, users.size() - 1);
		user2 = &users[i];
		amount = generateRandomDouble(100.00, 1000.00);

		transactions.emplace_back(user1, user2, amount, nonceForTrans);
		nonceForTrans++;

		notifyAboutProgress(size, transactions.size(), "transactions");
	}
	cout << "All transactions have been generated succesfully" << endl;
}

string hashBlock(Block &block) {
	Header *blockHeader = block.getHeader();
	string header;
	if (blockHeader->getPrevBlock() != nullptr) {
		header = *(blockHeader->getPrevBlock());
	}
	string input = header + blockHeader->getTimestamp() + std::to_string(blockHeader->getVersion()) +
			std::to_string(blockHeader->getNonce()) + std::to_string(blockHeader->getDifficultyTarget()) +
			blockHeader->getMerkleRoot();
	return HASH_FUNC(input);
}

bool isHashValid(string& hash, int& difficulty) {
	for(int i = 0; i < difficulty; i++) {
		if (hash[i] != '0') {
			return false;
		}
	}
	return true;
}

// TODO: Make template functions
//template<typename RandomGenerator, template <class...> class T, class C>
//typename T<C>::iterator select_randomly(typename T<C>::iterator start, typename T<C>::iterator end, RandomGenerator& g) {
//	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
//	std::advance(start, dis(g));
//	return start;
//}
//
//template<template <class...> class T, class C>
//typename T<C>::iterator select_randomly(typename T<C>::iterator  start, typename T<C>::iterator  end) {
//	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
//	static std::mt19937 gen(seed);
//	return select_randomly(start, end, gen);
//}

template<typename RandomGenerator>
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end) {
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static std::mt19937 gen(seed);
	return select_randomly(start, end, gen);
}

template<typename RandomGenerator>
vector<Transaction>::iterator select_randomly(vector<Transaction>::iterator start, vector<Transaction>::iterator end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}
vector<Transaction>::iterator select_randomly(vector<Transaction>::iterator start, vector<Transaction>::iterator end) {
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static std::mt19937 gen(seed);
	return select_randomly(start, end, gen);
}

template<typename RandomGenerator>
vector<Block>::iterator select_randomly(vector<Block>::iterator start, vector<Block>::iterator end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}
vector<Block>::iterator select_randomly(vector<Block>::iterator start, vector<Block>::iterator end) {
	long unsigned int seed = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	static std::mt19937 gen(seed);
	return select_randomly(start, end, gen);
}

void validateTransactions(list<Transaction>& transactions) {
	cout << transactions.size() << endl << endl;
	transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
			[](Transaction &t) {
				bool isValid = t.getSender()->getDebit() < t.getAmount()
							   && t.validateId(HASH_FUNC(t.getSenderId() + t.getReceiverId() + std::to_string(t.getAmount()) + std::to_string(t.getNonce())));
				if (isValid) {
					applyTransaction(t.getSender(), t.getReceiver(), t.getAmount());
				}
				return !isValid;
									  }
	), transactions.end());
}

bool compareTransactionsIterators(const list<Transaction>::iterator lhs, const list<Transaction>::iterator rhs) {
	return lhs->getNonce() > rhs->getNonce();
}

bool compareTransactions(const Transaction& lhs, const Transaction& rhs) {
	return lhs.getNonce() > rhs.getNonce();
}

list<Transaction>::iterator findUniqueIt(unordered_map<string, list<Transaction>::iterator>& transactionHTable, list<Transaction>& transactions) {
	auto randomTransIt = select_randomly(transactions.begin(), transactions.end());
	while(transactionHTable.find(randomTransIt->getTransactionId()) != transactionHTable.end()) {
		randomTransIt = select_randomly(transactions.begin(), transactions.end());
	}
	return randomTransIt;
}

vector<list<Transaction>> generateFiveTransactionPacks(list<Transaction>& transPool, int numberOfTransInList) {
	list<list<Transaction>::iterator> pickedTransactions;
//	list<list<Transaction>::iterator>::iterator it;

	unordered_map<string, list<Transaction>::iterator> transactionsHash1{};
	unordered_map<string, list<Transaction>::iterator> transactionsHash2{};
	unordered_map<string, list<Transaction>::iterator> transactionsHash3{};
	unordered_map<string, list<Transaction>::iterator> transactionsHash4{};
	unordered_map<string, list<Transaction>::iterator> transactionsHash5{};
	list<Transaction> transPack1{};
	list<Transaction> transPack2{};
	list<Transaction> transPack3{};
	list<Transaction> transPack4{};
	list<Transaction> transPack5{};
//	for (int i = 0; i < numberOfTransInList && !transPool.empty(); i++) {
//		pickedTransactions.push_back(select_randomly(transPool.begin(), transPool.end()));
//		pickedTransactions.push_back(select_randomly(transPool.begin(), transPool.end()));
//		pickedTransactions.push_back(select_randomly(transPool.begin(), transPool.end()));
//		pickedTransactions.push_back(select_randomly(transPool.begin(), transPool.end()));
//		pickedTransactions.push_back(select_randomly(transPool.begin(), transPool.end()));
//		it = pickedTransactions.begin();
//
//		transPack1.push_back(**it);
//		transPack2.push_back(**(++it));
//		transPack3.push_back(**(++it));
//		transPack4.push_back(**(++it));
//		transPack5.push_back(**(++it));
//
//		pickedTransactions.sort(compareTransactionsIterators);
//		pickedTransactions.unique();
//		for (auto & iter : pickedTransactions) {
//			cout << (*iter).toString() << endl;
//			transPool.erase(iter);
//		}
//		pickedTransactions.clear();
//	}

	list<Transaction>::iterator randomTrans;
	string key;
	for (int i = 0; i < numberOfTransInList && i < transPool.size(); i++) {
		randomTrans = findUniqueIt(transactionsHash1, transPool);
		transactionsHash1.insert(make_pair(randomTrans->getTransactionId(), randomTrans));
		transPack1.push_back(*randomTrans);
		pickedTransactions.push_back(randomTrans);

		randomTrans = findUniqueIt(transactionsHash2, transPool);
		transactionsHash2.insert(make_pair(randomTrans->getTransactionId(), randomTrans));
		transPack2.push_back(*randomTrans);
		pickedTransactions.push_back(randomTrans);

		randomTrans = findUniqueIt(transactionsHash3, transPool);
		transactionsHash3.insert(make_pair(randomTrans->getTransactionId(), randomTrans));
		transPack3.push_back(*randomTrans);
		pickedTransactions.push_back(randomTrans);

		randomTrans = findUniqueIt(transactionsHash4, transPool);
		transactionsHash4.insert(make_pair(randomTrans->getTransactionId(), randomTrans));
		transPack4.push_back(*randomTrans);
		pickedTransactions.push_back(randomTrans);

		randomTrans = findUniqueIt(transactionsHash5, transPool);
		transactionsHash5.insert(make_pair(randomTrans->getTransactionId(), randomTrans));
		transPack5.push_back(*randomTrans);
		pickedTransactions.push_back(randomTrans);
	}

	pickedTransactions.sort(compareTransactionsIterators);
	pickedTransactions.unique();
	for (auto & iter : pickedTransactions) {
		transPool.erase(iter);
	}

	cout << "\t" << transPool.size() << endl << endl;
	return vector<list<Transaction>> {transPack1, transPack2, transPack3, transPack4, transPack5};
}

vector<Block>::iterator selectRemainingBlock(vector<vector<Block>::iterator>& usedBlocks, vector<Block>& blockPool) {
	auto blockIt = select_randomly(blockPool.begin(), blockPool.end());
	while(std::find(usedBlocks.begin(), usedBlocks.end(), blockIt) != usedBlocks.end()) {
		blockIt = select_randomly(blockPool.begin(), blockPool.end());
	}
	return blockIt;
}

void moveUnusedTransToPool(vector<Block>::iterator blockIt, vector<Block>& blockPool, list<Transaction>& transPool) {
	list<Transaction> remainingTrans{};
	list<Transaction> tempTrans;
	list<Transaction> usedTransactionList = blockIt->getTransactions();
	for (auto it = blockPool.begin(); it != blockPool.end(); it++) {
		if (it != blockIt) {
			tempTrans = it->getTransactions();

//			tempTrans.remove_if([&](auto transaction) {
//				return std::find(usedTransactionList.begin(), usedTransactionList.end(), transaction) != usedTransactionList.end();
//			});
//
			tempTrans.erase(std::remove_if(tempTrans.begin(), tempTrans.end(), [&](auto transaction) {
				return std::find(usedTransactionList.begin(), usedTransactionList.end(), transaction) != usedTransactionList.end();
			}), tempTrans.end());

			remainingTrans.insert(remainingTrans.end(), tempTrans.begin(), tempTrans.end());
		}
	}

//	for(auto& trans: remainingTrans) {
//		cout << trans.toString() << endl;
//	}
//	cout << endl;
	remainingTrans.sort(compareTransactions);
	remainingTrans.unique();
//	for(auto& trans: remainingTrans) {
//		cout << trans.toString() << endl;
//	}
	transPool.insert(transPool.end(), remainingTrans.begin(), remainingTrans.end());
}

vector<Block> generateBlockPool(list<Transaction>& transPool, int& nextVersion, int& difficulty, int& sizeOfTransactionsInBlock, Block& lastBlock) {
	vector<list<Transaction>> transVector = generateFiveTransactionPacks(transPool, sizeOfTransactionsInBlock);
	auto transIt = transVector.begin();
	int nonce = 0;

	cout << "Creating blocks" << endl;
	vector<Block> blockPool;
	blockPool.emplace_back(lastBlock.getBlockHashPtr(), nextVersion, nonce, difficulty, *transIt++);
	blockPool.emplace_back(lastBlock.getBlockHashPtr(), nextVersion, nonce, difficulty, *transIt++);
	blockPool.emplace_back(lastBlock.getBlockHashPtr(), nextVersion, nonce, difficulty, *transIt++);
	blockPool.emplace_back(lastBlock.getBlockHashPtr(), nextVersion, nonce, difficulty, *transIt++);
	blockPool.emplace_back(lastBlock.getBlockHashPtr(), nextVersion, nonce, difficulty, *transIt++);
	return blockPool;
}
