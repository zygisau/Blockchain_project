//
// Created by zygisau on 2019-10-11.
//

#include "functions.h"

string generateRandomString(size_t len) {
	char *s = new char[len];
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
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
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<> random(from, to);
	return random(rng);
}
double generateRandomDouble(const int& from, const int& to) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 rng(seed);
	std::uniform_real_distribution<> random(from, to);
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

		User user(std::to_string(i), name, generateRandomDouble(1, 1000));
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
//		cout << index << endl;
		index = generateRandomInteger(0, size - 1);
	};
//	cout << index << endl;
	return index;

}

void applyTransaction(User* sender, User* receiver, double& amount) {
	sender->setDebit(sender->getDebit() - amount);
	receiver->setDebit(receiver->getDebit() + amount);
}

void generateTransactions(list<Transaction>& transactions, vector<User>& users) {
	cout << "Generating transactions..." << endl;
	int size = 10000;
	User* user1;
	User* user2;

	double amount;
	bool repeat;
	int times = 0;
	int i = generateRandomInteger(0, users.size() - 1);
	while (transactions.size() != size) {
		i = generateNextUserIndex(i, users.size() - 1);
		user1 = &users[i];
		i = generateNextUserIndex(i, users.size() - 1);
		user2 = &users[i];
		amount = generateRandomDouble(10, 50);
		repeat = true;
		times = 0;
		do {
			if (user1->getDebit() >= amount) {
				applyTransaction(user1, user2, amount);
				transactions.emplace_back(user1, user2, amount);
				repeat = false;
			} else if (user2->getDebit() >= amount) {
				applyTransaction(user2, user1, amount);
				transactions.emplace_back(user2, user1, amount);
				repeat = false;
			} else {
				amount = generateRandomDouble((int)amount, 50);
				times++;
			}
		} while(repeat && times < 3);

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

template<typename RandomGenerator>
list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

list<Transaction>::iterator select_randomly(list<Transaction>::iterator start, list<Transaction>::iterator end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}